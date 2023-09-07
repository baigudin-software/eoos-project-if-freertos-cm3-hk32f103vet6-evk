/**
 * @file      Prorgam.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2023, Sergey Baigudin, Baigudin Software
 *
 * @brief Tests of `Program`.
 */
#include "Program.hpp"

namespace eoos
{

static const int32_t PROGRAM_OK             (0); ///< Correct program exit code.
static const int32_t PROGRAM_WRONG_ARGS     (1); ///< Wrong program exit code.

/**
 * @copydoc eoos::Program::start(int32_t argc, char_t* argv[])
 */
int32_t Program::start(int32_t argc, char_t* argv[])
{
    volatile bool_t isRun( true );
    uint32_t countUp(0x00000000);
    uint32_t countDw(0xFFFFFFFF);    
    while(isRun)
    {
        countUp++;
        countDw--;
    }
    return static_cast<int32_t>(countUp) - static_cast<int32_t>(countDw);
}

} // namespace eoos
