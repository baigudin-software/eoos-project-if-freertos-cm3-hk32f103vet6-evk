/**
 * @file      DriverGpioTest.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2023, Sergey Baigudin, Baigudin Software
 *
 * @brief Tests of GPIO driver.
 */
#include "DriverGpioTest.hpp"
#include "drv.Gpio.hpp"
#include "lib.Thread.hpp"

namespace eoos
{

void testDriverGpio()
{
    drv::Gpio::Config config = {
        .mode = drv::Gpio::MODE_OUTPUT_50MHZ,
        .direction = { 
            .output = drv::Gpio::MODEOUTPUT_PUSH_PULL
        },
        .port = drv::Gpio::PORTNUMBER_B,
        .gpio = drv::Gpio::GPIONUMBER_1
    };
    drv::Gpio* gpio( drv::Gpio::create(config) );

    while(true)
    {
        gpio->pullUp();
        if( !gpio->isPullUp() )
        {
            break;
        }
        lib::Thread<>::sleep(1000);
        gpio->pullDown();
        if( !gpio->isPullDown() )
        {
            break;
        }        
        lib::Thread<>::sleep(1000);        
    }

    delete gpio;
}

} // namespace eoos
