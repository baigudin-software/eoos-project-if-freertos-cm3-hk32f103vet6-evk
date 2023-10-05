/**
 * @file      port.cpp
 * @brief     Universal EOOS port of FreeRTOS Kernel V10.5.1 (V202212.01)
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2023, Sergey Baigudin, Baigudin Software
 */
#include "port.hpp"
#include "FreeRTOS.h"
#include "task.h"

#include "lib.Guard.hpp"

namespace eoos
{

/**
 * @brief The target processor.
 */
static api::SystemPort* pxPortEoos_( NULLPTR );

/**
 * @brief Each task maintains its own interrupt status in the critical nesting variable. 
 */
static UBaseType_t uxPortCriticalNesting_( 0xAAAAAAAA );

/**
 * @brief Each task maintains its own interrupt status in the critical nesting variable. 
 */
static bool_t wasEnabledOnZero_( false );

/**
 * @brief Stops execution on a critial error.
 */
static void prvPortStopExecution()
{
    portDISABLE_INTERRUPTS();
    while(1){}
}

/**
 * @brief Implements error task exit behavior.
 *
 * A function that implements a task must not exit or attempt to return to
 * its caller as there is nothing to return to.  If a task wants to exit it
 * should instead call vTaskDelete( NULL ).
 */
static void prvTaskExitError()
{
    prvPortStopExecution();
}

/**
 * @file portable.h
 * @brief Starts scheduling.
 *
 * @return No exit.
 */
extern "C" BaseType_t xPortStartScheduler( void )
{
    // Initialise the critical nesting count ready for the first task.
    uxPortCriticalNesting_ = 0;
    if( pxPortEoos_ != NULLPTR )
    {
        // Start the first task.
        pxPortEoos_->getProcessor().bootPrimaryThread();
    }
    // Should never get here as the tasks will now be executing.
    prvTaskExitError();
    return 0;
}

/**
 * @file portable.h
 * @brief Yields to the next task.
 */
extern "C" void vPortYield(void)
{
    if( pxPortEoos_ != NULLPTR )
    {
        int32_t source( pxPortEoos_->getTimer().getInterrupSource() );
        pxPortEoos_->getProcessor().getInterruptController().jump(source);
    }
}

/**
 * @file portmacro.h
 * @brief Disable interrupts globaly.
 */
extern "C" void vPortDisableInterrupts()
{
    if( pxPortEoos_ != NULLPTR )
    {
        static_cast<void>( pxPortEoos_->getProcessor().getInterruptController().getGlobal().lock() );
    }
}

/**
 * @file portmacro.h
 * @brief Enables interrupts globaly.
 */
extern "C" void vPortEnableInterrupts()
{
    if( pxPortEoos_ != NULLPTR )
    {
        pxPortEoos_->getProcessor().getInterruptController().getGlobal().unlock();
    }
}

/**
 * @file portmacro.h
 * @brief Enters critical section execution.
 */
extern "C" void vPortEnterCritical(void)
{
    if( pxPortEoos_ != NULLPTR )
    {
        bool_t wasEnabled( pxPortEoos_->getProcessor().getInterruptController().getGlobal().lock() );
        if(uxPortCriticalNesting_ == 0)
        {
            wasEnabledOnZero_ = wasEnabled;
        }
        uxPortCriticalNesting_++;
    }
}

/**
 * @file portmacro.h
 * @brief Exits critical section execution.
 */
extern "C" void vPortExitCritical()
{
    if( pxPortEoos_ != NULLPTR )
    {
        configASSERT( uxPortCriticalNesting_ );
        uxPortCriticalNesting_--;
        if( uxPortCriticalNesting_ == 0 && wasEnabledOnZero_ )
        {
            wasEnabledOnZero_ = false;
            pxPortEoos_->getProcessor().getInterruptController().getGlobal().unlock();
        }
    }
}

/**
 * @file portmacro.h
 * @brief Enters critical section execution in ISR.
 *
 * @return The prior value.
 */
extern "C" UBaseType_t uxPortEnterCriticalFromISR()
{
    UBaseType_t prior( 0 );
    if( pxPortEoos_ != NULLPTR )
    {
        prior = static_cast<UBaseType_t>( pxPortEoos_->getProcessor().getInterruptController().getGlobal().lock() );
    }
    return prior;
}

/**
 * @file portmacro.h
 * @brief Exits critical section execution in ISR.
 *
 * @param prior The prior value. 
 */
extern "C" void vPortExitCriticalFromISR(UBaseType_t prior)
{
    if( pxPortEoos_ != NULLPTR && prior == 1 )
    {
        pxPortEoos_->getProcessor().getInterruptController().getGlobal().unlock();
    }
}

/**
 * @file portable.h
 * @brief Initializes stack of a new task.
 *
 * Setup the stack of a new task so it is ready to be placed under the
 * scheduler control.  The registers have to be placed on the stack in
 * the order that the port expects to find them. 
 *
 * @param pxTopOfStack A created top of stack.
 * @param pxCode A task entry point.
 * @param pvParameters A pointer to the task arguments.
 * @return Top of stack after the initialization.
 */
extern "C" StackType_t* pxPortInitialiseStack(StackType_t* pxTopOfStack, TaskFunction_t pxCode, void* pvParameters)
{
    void* stack( pxTopOfStack );
    if( pxPortEoos_ != NULLPTR )
    {
        void* const entry( reinterpret_cast<void*>(pxCode) );
        void* const exit( reinterpret_cast<void*>(prvTaskExitError) );
        int32_t const argument( reinterpret_cast<int32_t>(pvParameters) );
        stack = pxPortEoos_->getProcessor().getRegistersController().initializeStack(stack, entry, exit, argument);
    }
    return reinterpret_cast<StackType_t*>(stack);
}

/**
 * @file portable.h
 * @brief Ends scheduler execution.
 *
 * Undo any hardware/ISR setup that was performed by xPortStartScheduler() so
 * the hardware is left in its original condition after the scheduler stops
 * executing.
 */
extern "C" void vPortEndScheduler(void)
{
    prvPortStopExecution();
}
    
/**
 * @file task.h
 * @brief Provides a statically allocated block of memory to FreeRTOS.
 *
 * This function is used to provide a statically allocated block of memory to FreeRTOS to hold the Idle Task TCB.  
 * This function is required when configSUPPORT_STATIC_ALLOCATION is set.
 *
 * @param ppxIdleTaskTCBBuffer A handle to a statically allocated TCB buffer
 * @param ppxIdleTaskStackBuffer A handle to a statically allocated Stack buffer for the idle task
 * @param pulIdleTaskStackSize A pointer to the number of elements that will fit in the allocated stack buffer
 */
extern "C" void vApplicationGetIdleTaskMemory(StaticTask_t** ppxIdleTaskTCBBuffer, StackType_t** ppxIdleTaskStackBuffer, uint32_t* pulIdleTaskStackSize )
{    
    static StaticTask_t xIdleTaskTCB;
    static StackType_t uxIdleTaskStack[ configMINIMAL_STACK_SIZE ];
    *ppxIdleTaskTCBBuffer = &xIdleTaskTCB;
    *ppxIdleTaskStackBuffer = uxIdleTaskStack;
    *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
}

/**
 * @file task.h
 * @brief Hooks stack overflow event.
 */
extern "C" void vApplicationStackOverflowHook(TaskHandle_t pxTask, char *pcTaskName)
{
    prvPortStopExecution();
}

void Kernel::initialize(api::SystemPort& port)
{
    pxPortEoos_ = &port;
}

void Kernel::execute()
{
    if( pxPortEoos_ != NULLPTR )
    {
        vTaskStartScheduler();
    }
	// If all is well, the scheduler will now be running, and the following
	// line will never be reached. If the following line does execute, then
	// there was insufficient FreeRTOS heap memory available for the idle and/or
	// timer tasks	to be created. See the memory management section on the
	// FreeRTOS web site for more details.
    prvPortStopExecution();
}

} // namespace eoos
