/**
 * @file      DriverCanTest.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2023-2024, Sergey Baigudin, Baigudin Software
 *
 * @brief Tests of CAN driver.
 */
#include "DriverCanTest.hpp"
#include "drv.Can.hpp"
#include "lib.UniquePointer.hpp"

namespace eoos
{

void testDriverCan()
{
    drv::Can::Config config = {
        .number = drv::Can::NUMBER_CAN1,
        .reg    = {
            .mcr = {
                .txfp = 0, ///< Transmit FIFO priority (reset value is 0)
                .rflm = 0, ///< Receive FIFO locked mode (reset value is 0)
                .nart = 0, ///< No automatic retransmission (reset value is 0)
                .awum = 0, ///< Automatic wake-up mode (reset value is 0)
                .abom = 0, ///< Automatic bus-off management (reset value is 0)
                .ttcm = 0  ///< Time triggered communication mode (reset value is 0)
            },
            .btr = {
                .brp  = 0, ///< Baud rate prescaler (reset value is 0)
                .ts1  = 3, ///< Time segment 1 (reset value is 3)
                .ts2  = 2, ///< Time segment 2 (reset value is 2)
                .sjw  = 0, ///< Resynchronization jump width (reset value is 0)
                .lbkm = 1, ///< Loop back mode for debug (reset value is 0)
                .silm = 1  ///< Silent mode for debug (reset value is 0)
            }
        }
    };
    lib::UniquePointer<drv::Can> can( drv::Can::create(config) );
}

} // namespace eoos
