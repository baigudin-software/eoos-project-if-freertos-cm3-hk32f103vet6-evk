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

namespace eoos
{

/**
 * @copydoc eoos::Program::start(int32_t argc, char_t* argv[])
 */
int32_t Program::start(int32_t argc, char_t* argv[])
{
    // Comment to lock or uncomment to execute
    // testContexSwitch();
    
    // Comment to lock or uncomment to execute
    // testThreadYield();

    // Comment to lock or uncomment to execute    
    testMutex();
    
    // This is the Primary Task of FreeRTOS, and as soon as 
    // the RTOS does not support task exiting, do infinity loop.
    uint32_t countUp(0x00000000);
    uint32_t countDw(0xFFFFFFFF);    
    while(true)
    {
        countUp++;
        countDw--;
    }
    return -1;
}

} // namespace eoos
