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
#include "lib.AbstractThreadTask.hpp"

namespace eoos
{
    
namespace
{
    
class ThreadWaitTx : public lib::AbstractThreadTask<>
{
    
public:

    ThreadWaitTx(drv::Can&  can)
        : lib::AbstractThreadTask<>()
        , can_( can ) {
    }
        
private:

    virtual void start()
    {
        drv::Can::TxMessage message = {
            .id  = 0x12345678,
            .ide = true,
            .rtr = false,
            .dlc = 8,
            .data = {
                .v64 = {
                    0x0000000000000000
                }
            }
        };
        while(true)
        {
            bool_t res( can_.transmit(message) );
            if( res == false )
            {
                message.data.v64[0]--;
            }
            message.data.v64[0]++;
        }
    }

    drv::Can&  can_;
};

}

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
                .ttcm = 0, ///< Time triggered communication mode (reset value is 0)
                .dbf  = 1  ///< CAN reception and transmission frozen during debug (reset value is 1)
            },
            .btr = {
                .lbkm = 1, ///< Loop back mode for debug (reset value is 0)
                .silm = 1  ///< Silent mode for debug (reset value is 0)
            }
        }
    };
    lib::UniquePointer<drv::Can> can( drv::Can::create(config) );    
    ThreadWaitTx thread(*can);
    thread.setPriority(api::Thread::PRIORITY_MAX);
    thread.execute();
    while(true);
}

} // namespace eoos
