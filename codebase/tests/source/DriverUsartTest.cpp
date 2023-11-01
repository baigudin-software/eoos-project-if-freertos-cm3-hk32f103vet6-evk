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
    drv::Usart::SerialLineConfig config = {
        .number      = drv::Usart::NUMBER_USART1,
        .mode        = drv::Usart::MODE_TX,
        .baud        = drv::Usart::BAUD_115200,
        .dataBits    = drv::Usart::DATABITS_8,
        .stopBits    = drv::Usart::STOPBITS_1,
        .parity      = drv::Usart::PARITY_NONE,
        .flowControl = drv::Usart::FLOWCONTROL_NONE
    };
    drv::Usart* uart( drv::Usart::create(config) );
    *uart << "Hello, World!" << "\r\n";
    delete uart;
}

} // namespace eoos
