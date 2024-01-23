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
        .bitRate = drv::Can::BITRATE_250,
        .samplePoint = drv::Can::SAMPLEPOINT_CANOPEN,
        .reg = {
            .mcr = {
                .txfp = 0, ///< Transmit FIFO priority (reset value is 0)
                .rflm = 0, ///< Receive FIFO locked mode (reset value is 0)
                .nart = 0, ///< No automatic retransmission (reset value is 0)
                .awum = 0, ///< Automatic wake-up mode (reset value is 0)
                .abom = 0, ///< Automatic bus-off management (reset value is 0)
                .ttcm = 0  ///< Time triggered communication mode (reset value is 0)
            },
            .btr = {
                .lbkm = 1, ///< Loop back mode for debug (reset value is 0)
                .silm = 1  ///< Silent mode for debug (reset value is 0)
            }
        }
    };
    lib::UniquePointer<drv::Can> can( drv::Can::create(config) );
    
    drv::Can::TxHandler* handler(NULLPTR);
    drv::Can::TxMessage message = {
        .id  = 0x12345678,
        .ide = true,
        .rtr = false,
        .dlc = 3,
        .data = {
            .v8 = {
                0x18,
                0x01,
                0x24
            }
        }
    };
    handler = can->transmit(message);
    if( handler !=NULLPTR )
    {
        bool_t res( handler->isTransmited() );
        if( !res )
        {

        }
    }
    while(true);
}

} // namespace eoos
