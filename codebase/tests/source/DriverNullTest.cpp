/**
 * @file      DriverNullTest.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2023, Sergey Baigudin, Baigudin Software
 *
 * @brief Tests of Null driver.
 */
#include "DriverNullTest.hpp"
#include "drv.Null.hpp"
#include "lib.UniquePointer.hpp"

namespace eoos
{

void testDriverNull()
{
    drv::Null::Config config = {
        .number      = drv::Null::NUMBER_NULL0,
    };
    lib::UniquePointer<drv::Null> uart( drv::Null::create(config) );
    *uart << "Hello, World!" << "\r\n";
}

} // namespace eoos
