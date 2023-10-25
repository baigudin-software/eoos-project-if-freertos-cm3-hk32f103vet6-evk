/**
 * @file      DriverUsartTest.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2023, Sergey Baigudin, Baigudin Software
 *
 * @brief Tests of USART driver.
 */
#include "DriverUsartTest.hpp"
#include "drv.Usart.hpp"

namespace eoos
{

void testDriverUsart()
{
    drv::Usart* uart( drv::Usart::create(drv::Usart::NUMBER_USART1) );
    *uart << "Hello, World!" << "\n";
    delete uart;
}

} // namespace eoos
