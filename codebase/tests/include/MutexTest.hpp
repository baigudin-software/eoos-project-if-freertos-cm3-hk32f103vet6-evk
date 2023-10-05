/**
 * @file      MutexTest.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2023, Sergey Baigudin, Baigudin Software
 *
 * @brief Tests of thread yield.
 */
#ifndef TST_MUTEXTEST_HPP_
#define TST_MUTEXTEST_HPP_
 
#include "Types.hpp"

namespace eoos
{

/**
 * @brief Tests thread yield switch correctly.
 *
 * This function won't return and will break all CPU registers and C/C++ ABI.
 * This test must be checked visually on the appropriate break points.
 */
void testMutex();

} // namespace eoos

#endif // TST_MUTEXTEST_HPP_

