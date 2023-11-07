/**
 * @file      port.Kernel.cpp
 * @brief     Universal EOOS port of FreeRTOS Kernel V10.5.1 (V202212.01)
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2023, Sergey Baigudin, Baigudin Software
 */
#include "port.Kernel.hpp"
#include "FreeRTOS.h"
#include "task.h"

namespace eoos
{
namespace port
{

/**
 * @brief The target processor.
 */
static api::CpuProcessor* pxProcessor_( NULLPTR );

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
    while(true){}
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
    if( pxProcessor_ != NULLPTR )
    {
        // Start the first task.
        pxProcessor_->bootPrimaryThread();
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
    if( pxProcessor_ != NULLPTR )
    {
        api::CpuInterruptController& ic( pxProcessor_->getInterruptController() );
        int32_t const source( ic.getNumberSupervisor() );
        ic.jump(source);
    }
}

/**
 * @file portmacro.h
 * @brief Disable interrupts globaly.
 */
extern "C" void vPortDisableInterrupts()
{
    if( pxProcessor_ != NULLPTR )
    {
        static_cast<void>( pxProcessor_->getInterruptController().getGlobal().lock() );
    }
}

/**
 * @file portmacro.h
 * @brief Enables interrupts globaly.
 */
extern "C" void vPortEnableInterrupts()
{
    if( pxProcessor_ != NULLPTR )
    {
        pxProcessor_->getInterruptController().getGlobal().unlock();
    }
}

/**
 * @file portmacro.h
 * @brief Enters critical section execution.
 */
extern "C" void vPortEnterCritical(void)
{
    if( pxProcessor_ != NULLPTR )
    {
        bool_t wasEnabled( pxProcessor_->getInterruptController().getGlobal().lock() );
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
    if( pxProcessor_ != NULLPTR )
    {
        configASSERT( uxPortCriticalNesting_ );
        uxPortCriticalNesting_--;
        if( uxPortCriticalNesting_ == 0 && wasEnabledOnZero_ )
        {
            wasEnabledOnZero_ = false;
            pxProcessor_->getInterruptController().getGlobal().unlock();
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
    if( pxProcessor_ != NULLPTR )
    {
        prior = static_cast<UBaseType_t>( pxProcessor_->getInterruptController().getGlobal().lock() );
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
    if( pxProcessor_ != NULLPTR && prior == 1 )
    {
        pxProcessor_->getInterruptController().getGlobal().unlock();
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
    if( pxProcessor_ != NULLPTR )
    {
        void* const entry( reinterpret_cast<void*>(pxCode) );
        void* const exit( reinterpret_cast<void*>(prvTaskExitError) );
        int32_t const argument( reinterpret_cast<int32_t>(pvParameters) );
        stack = pxProcessor_->getRegistersController().initializeStack(stack, entry, exit, argument);
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

Kernel::Kernel(api::CpuProcessor& cpu)
    : lib::NonCopyable<lib::NoAllocator>() {     
    bool_t const isConstructed( construct(cpu) );
    setConstructed( isConstructed );
}

Kernel::~Kernel()
{
    pxProcessor_ = NULLPTR;
}

void Kernel::execute()
{
    if( isConstructed() )
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

bool_t Kernel::construct(api::CpuProcessor& cpu)
{
    bool_t res( false );
    do 
    {
        if( !isConstructed() )
        {
            break;
        }
        if( !cpu.isConstructed() )
        {
            break;
        }
        if( pxProcessor_ != NULLPTR )
        {
            break;
        }
        pxProcessor_ = &cpu;
        res = true;
    } while(false);
    return res;
}

} // namespace port
} // namespace eoos
