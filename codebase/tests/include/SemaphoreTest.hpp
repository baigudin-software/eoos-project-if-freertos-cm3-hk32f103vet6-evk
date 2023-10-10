/**
 * @file      SemaphoreTest.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2023, Sergey Baigudin, Baigudin Software
 *
 * @brief Tests of semaphore.
 */
#ifndef TST_SEMAPHORETEST_HPP_
#define TST_SEMAPHORETEST_HPP_
 
#include "Types.hpp"

namespace eoos
{

/**
 * @brief Tests Semaphore.
 *
 * This function won't return and will break all CPU registers and C/C++ ABI.
 * This test must be checked visually on the appropriate break points.
 */
void testSemaphore();

} // namespace eoos

#endif // TST_SEMAPHORETEST_HPP_

