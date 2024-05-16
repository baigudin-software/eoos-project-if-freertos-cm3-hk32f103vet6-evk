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

void testTx(drv::Can& can)
{
    drv::Can::Message message = {
        .id  = {
            .exid = 0x00035555,
            .stid = 0x000007AA
        },
        .rtr = false,        
        .ide = true,
        .dlc = 8,
        .data = {
            .v64 = {
                0x1234567890ABCDEF                
            }
        }
    };

    while(true)
    {
        bool_t res( can.transmit(message) );
        if( res == false )
        {
            message.data.v64[0]--;
        }
        message.data.v64[0]++;
    }
}

void testTxRx(drv::Can& can)
{
    bool_t res( false );    
    
    //{
    //    drv::Can::RxFilter filter = {
    //        .fifo = drv::Can::RxFilter::FIFO_1,
    //        .index = 0,
    //        .mode = drv::Can::RxFilter::MODE_IDLIST,
    //        .scale = drv::Can::RxFilter::SCALE_32BIT,
    //        .filters = { 
    //            .group32 = {
    //                .idList = {
    //                    .id = { 
    //                        {
    //                            .bit = {
    //                                .rtr = 0,
    //                                .ide = 1,
    //                                .exid = 0b000000000000000011,
    //                                .stid = 0b0000000001
    //                            }
    //                        },
    //                        {
    //                            .bit = {
    //                                .rtr = 0,
    //                                .ide = 1,
    //                                .exid = 0b000000000000000111,
    //                                .stid = 0b0000000011
    //                            }
    //                        }
    //                    }
    //                }
    //            }
    //        }
    //    };
    //    res = can.setReceiveFilter(filter);
    //    if( res == false )
    //    {
    //        while(true);
    //    }
    //}
    //
    //{
    //    drv::Can::RxFilter filter = {
    //        .fifo = drv::Can::RxFilter::FIFO_1,
    //        .index = 1,
    //        .mode = drv::Can::RxFilter::MODE_IDLIST,
    //        .scale = drv::Can::RxFilter::SCALE_32BIT,
    //        .filters = { 
    //            .group32 = {
    //                .idList = {
    //                    .id = { 
    //                        {
    //                            .bit = {
    //                                .rtr = 0,
    //                                .ide = 1,
    //                                .exid = 0b000000000000001111,
    //                                .stid = 0b0000000111
    //                            }
    //                        },
    //                        {
    //                            .bit = {
    //                                .rtr = 0,
    //                                .ide = 1,
    //                                .exid = 0b000000000000011111,
    //                                .stid = 0b0000001111
    //                            }
    //                        }
    //                    }
    //                }
    //            }
    //        }
    //    };
    //    res = can.setReceiveFilter(filter);
    //    if( res == false )
    //    {
    //        while(true);
    //    }
    //}
    {
        drv::Can::RxFilter filter = {
            .fifo = drv::Can::RxFilter::FIFO_1,
            .index = 2,
            .mode = drv::Can::RxFilter::MODE_IDMASK,
            .scale = drv::Can::RxFilter::SCALE_32BIT,
            .filters = { 
                .group32 = {
                    .idMask = {
                        .id = {
                            .bit = {
                                .rtr = 0,
                                .ide = 1,
                                .exid = 0b000000000000000011,
                                .stid = 0b0000000001
                            }
                        },
                        .mask = {
                            .bit = {
                                .rtr = 0,
                                .ide = 1,
                                .exid = 0b000000000000000011,
                                .stid = 0b0000000001
                            }
                        }
                    }
                }
            }
        };
        res = can.setReceiveFilter(filter);
        if( res == false )
        {
            while(true);
        }
    }
    // Send 1
    {
        drv::Can::Message txMessage = {
            .id  = {
                .exid = 0b000000000000000011,
                .stid = 0b0000000001
            },
            .rtr = false,        
            .ide = true,
            .dlc = 8,
            .data = {
                .v64 = {
                    0x123456E1789ACDE1
                }
            }
        };
        res = can.transmit(txMessage);
        if( res == false )
        {
            while(true);
        }
    }
    for(int32_t i=0; i<0x00FFFFFF; i++){}    
    // Send 2
    {
        drv::Can::Message txMessage = {
            .id  = {
                .exid = 0b000000000000000111,
                .stid = 0b0000000011
            },
            .rtr = false,        
            .ide = true,
            .dlc = 8,
            .data = {
                .v64 = {
                    0x123456E2789ACDE2
                }
            }
        };    
        res = can.transmit(txMessage);
        if( res == false )
        {
            while(true);
        }
    }
    for(int32_t i=0; i<0x00FFFFFF; i++){}    
    // Send 3
    {
        drv::Can::Message txMessage = {
            .id  = {
                .exid = 0b000000000000001111,
                .stid = 0b0000000111
            },
            .rtr = false,        
            .ide = true,
            .dlc = 8,
            .data = {
                .v64 = {
                    0x123456E3789ACDE3
                }
            }
        };
        res = can.transmit(txMessage);
        if( res == false )
        {
            while(true);
        }
    }
    for(int32_t i=0; i<0x00FFFFFF; i++){}        
    // Send 4
    {
        drv::Can::Message txMessage = {
            .id  = {
                .exid = 0b000000000000011111,
                .stid = 0b0000001111
            },
            .rtr = false,        
            .ide = true,
            .dlc = 8,
            .data = {
                .v64 = {
                    0x123456E4789ACDE4
                }
            }
        };    
        res = can.transmit(txMessage);
        if( res == false )
        {
            while(true);
        }    
    }
    for(int32_t i=0; i<0x00FFFFFF; i++){}
    // Send 5
    {
        drv::Can::Message txMessage = {
            .id  = {
                .exid = 0b000000000000111111,
                .stid = 0b0000011111
            },
            .rtr = false,        
            .ide = true,
            .dlc = 8,
            .data = {
                .v64 = {
                    0x123456E4789ACDE4
                }
            }
        };    
        res = can.transmit(txMessage);
        if( res == false )
        {
            while(true);
        }    
    }
    for(int32_t i=0; i<0x00FFFFFF; i++){}
    // Send 6
    {
        drv::Can::Message txMessage = {
            .id  = {
                .exid = 0b000000000001111111,
                .stid = 0b0000111111
            },
            .rtr = false,        
            .ide = true,
            .dlc = 8,
            .data = {
                .v64 = {
                    0x123456E4789ACDE4
                }
            }
        };    
        res = can.transmit(txMessage);
        if( res == false )
        {
            while(true);
        }    
    }
    for(int32_t i=0; i<0x00FFFFFF; i++){}

    
    while(true)
    {
        drv::Can::Message rxMessage = { 0 };
        res = can.receive(&rxMessage, drv::Can::RXFIFO_1);
        if( res == false )
        {
            while(true);
        }
    }

    //if( txMessage == rxMessage )
    //{
    //    while(true);
    //}
    //else
    //{
    //    while(true);
    //}

}

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
    testTxRx(*can);    
    testTx(*can);
    while(true);
}

} // namespace eoos
