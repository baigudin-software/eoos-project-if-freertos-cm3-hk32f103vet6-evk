/**
 * @file      ProrgamTest.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2023, Sergey Baigudin, Baigudin Software
 *
 * @brief Tests of `Program`.
 */
#include "Program.hpp"
#include "ContexSwitchTest.hpp"
#include "ThreadYieldTest.hpp"
#include "MutexTest.hpp"
#include "SemaphoreTest.hpp"
#include "DriverUsartTest.hpp"
#include "DriverNullTest.hpp"
#include "DriverGpioTest.hpp"
#include "DriverCanTest.hpp"
#include "lib.Stream.hpp"
#include "sys.System.hpp"

namespace eoos
{
    
/**
 * @brief Prints EOOS global configuration.
 */
static void printConfiguration()
{
    lib::Stream::cout() << "WELCOME TO EOOS FreeRTOS TESTS\r\n";
    // Output of C++ Language.
    #if   EOOS_CPP_STANDARD == 1998
        lib::Stream::cout() << "LANGUAGE: C++98\r\n";
    #elif EOOS_CPP_STANDARD == 2011
        lib::Stream::cout() << "LANGUAGE: C++11\r\n";
    #elif EOOS_CPP_STANDARD == 2014
        lib::Stream::cout() << "LANGUAGE: C++14\r\n";
    #elif EOOS_CPP_STANDARD == 2017
        lib::Stream::cout() << "LANGUAGE: C++17\r\n";
    #elif EOOS_CPP_STANDARD == 2020
        lib::Stream::cout() << "LANGUAGE: C++20\r\n";
    #else        
        lib::Stream::cout() << "LANGUAGE: unknown\r\n";
    #endif
    
    // Output of Data Model of a hardware system.  
    #if defined (EOOS_GLOBAL_TYPE_STDLIB)
        lib::Stream::cout() << "DATA MODEL: C++ Standard Library types\r\n";
    #elif defined (EOOS_TYPE_WIDTH_LP32)
        lib::Stream::cout() << "DATA MODEL: LP32 or 2/4/4 (int is 16-bit, long and pointer are 32-bit)\r\n";
    #elif defined (EOOS_TYPE_WIDTH_ILP32)
        lib::Stream::cout() << "DATA MODEL: ILP32 or 4/4/4 (int, long, and pointer are 32-bit)\r\n";
    #elif defined (EOOS_TYPE_WIDTH_LLP64)
        lib::Stream::cout() << "DATA MODEL: LLP64 or 4/4/8 (int and long are 32-bit, pointer is 64-bit)\r\n";
    #elif defined (EOOS_TYPE_WIDTH_LP64)
        lib::Stream::cout() << "DATA MODEL: LP64 or 4/8/8 (int is 32-bit, long and pointer are 64-bit)\r\n";
    #else
        lib::Stream::cout() << "DATA MODEL: C++ standard\r\n";
    #endif

    // Dynamic heap memory allocation.
    #if defined (EOOS_GLOBAL_ENABLE_NO_HEAP)
        lib::Stream::cout() << "DISABLE: Dynamic heap memory allocation\r\n";
    #else
        lib::Stream::cout() << "ENABLE: Dynamic heap memory allocation\r\n";
    #endif

    #if EOOS_GLOBAL_SYS_NUMBER_OF_MUTEXS == 0
        lib::Stream::cout() << "MEMORY MODE: Mutex in heap memory.\r\n";
    #else
        lib::Stream::cout() << "MEMORY MODE: Mutex in pool memory of " << EOOS_GLOBAL_SYS_NUMBER_OF_MUTEXS << ".\r\n";
    #endif

    #if EOOS_GLOBAL_SYS_NUMBER_OF_SEMAPHORES == 0
        lib::Stream::cout() << "MEMORY MODE: Semaphore in heap memory.\r\n";
    #else
        lib::Stream::cout() << "MEMORY MODE: Semaphore in pool memory of " << EOOS_GLOBAL_SYS_NUMBER_OF_SEMAPHORES << ".\r\n";
    #endif

    #if EOOS_GLOBAL_SYS_NUMBER_OF_THREADS == 0
        lib::Stream::cout() << "MEMORY MODE: Thread in heap memory.\r\n";
    #else
        lib::Stream::cout() << "MEMORY MODE: Thread in pool memory of " << EOOS_GLOBAL_SYS_NUMBER_OF_THREADS << ".\r\n";
    #endif
 
    #if EOOS_GLOBAL_CPU_NUMBER_OF_INTERRUPTS == 0
        lib::Stream::cout() << "MEMORY MODE: Interrupts in heap memory.\r\n";
    #else
        lib::Stream::cout() << "MEMORY MODE: Interrupts in pool memory of " << EOOS_GLOBAL_CPU_NUMBER_OF_INTERRUPTS << ".\r\n";
    #endif
  
    #if EOOS_GLOBAL_CPU_NUMBER_OF_SYSTEM_TIMERS == 0
        lib::Stream::cout() << "MEMORY MODE: System timer in heap memory.\r\n";
    #else
        lib::Stream::cout() << "MEMORY MODE: System timer in pool memory of " << EOOS_GLOBAL_CPU_NUMBER_OF_SYSTEM_TIMERS << ".\r\n";
    #endif

    #if EOOS_GLOBAL_DRV_NUMBER_OF_USARTS == 0
        lib::Stream::cout() << "MEMORY MODE: USART driver in heap memory.\r\n";
    #else
        lib::Stream::cout() << "MEMORY MODE: USART driver in pool memory of " << EOOS_GLOBAL_DRV_NUMBER_OF_USARTS << ".\r\n";
    #endif

    // EOOS state:
    lib::Stream::cout() << "EOOS: Size of system " << static_cast<int32_t>(sizeof(sys::System)) << " Bytes\r\n";
}

/**
 * @copydoc eoos::Program::start(int32_t argc, char_t* argv[])
 */
int32_t Program::start(int32_t argc, char_t* argv[])
{
    printConfiguration();
        
    // Comment to lock or uncomment to execute
    // testContexSwitch();
    
    // Comment to lock or uncomment to execute
    // testThreadYield();

    // Comment to lock or uncomment to execute    
    // testMutex();

    // Comment to lock or uncomment to execute    
    // testSemaphore();

    // Comment to lock or uncomment to execute    
    // testDriverUsart();

    // Comment to lock or uncomment to execute    
    // testDriverNull(); 

    // Comment to lock or uncomment to execute    
    testDriverCan();

    // Comment to lock or uncomment to execute    
    testDriverGpio();
    
    return 0;
}

} // namespace eoos
