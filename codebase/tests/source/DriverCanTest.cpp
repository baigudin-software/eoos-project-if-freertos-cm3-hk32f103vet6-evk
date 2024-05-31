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
#include "lib.Thread.hpp"

namespace eoos
{
    
namespace
{

void testTxLine(drv::Can& can)
{
    drv::Can::Message message = {
        .id  = {
            .exid = 0b101010101010101010,
            .stid = 0b0101010101
        },
        .rtr = false,
        .ide = true,
        .dlc = 0,
        .data = {
            .v64 = {
                0x0000000000000000
            }
        }
    };
    while(true)
    {
        bool_t res( can.transmit(message) );
        if( res == false )
        {
            while(true){}
        }
        message.dlc = (message.dlc == 8) ? 0 : message.dlc + 1;
        message.data.v64[0]++;
    }
}

void testRxLine(drv::Can& can)
{
    bool_t res( false );    
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
    drv::Can::Message exMessage = {
        .id  = {
            .exid = 0b000000000000000011,
            .stid = 0b0000000001
        },
        .rtr = false,
        .ide = true,
        .dlc = 8,
        .data = {
            .v64 = {
                0x0807060504030201
            }
        }
    };    
    while(true)
    {
        drv::Can::Message rxMessage = { 0 };
        res = can.receive(&rxMessage, drv::Can::RXFIFO_1);
        if( res == false )
        {
            while(true);
        }
        if( exMessage != rxMessage )
        {
            while(true);
        }
    }    
}

void testTxRxLoop(drv::Can& can)
{
    bool_t res( false );
    
    {
        drv::Can::RxFilter filter = {
            .fifo = drv::Can::RxFilter::FIFO_1,
            .index = 1,
            .mode = drv::Can::RxFilter::MODE_IDLIST,
            .scale = drv::Can::RxFilter::SCALE_32BIT,
            .filters = { 
                .group32 = {
                    .idList = {
                        .id = { 
                            {
                                .bit = {
                                    .rtr = 0,
                                    .ide = 1,
                                    .exid = 0b000000000000001111,
                                    .stid = 0b0000000111
                                }
                            },
                            {
                                .bit = {
                                    .rtr = 0,
                                    .ide = 1,
                                    .exid = 0b000000000000011111,
                                    .stid = 0b0000001111
                                }
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

}

} // namespace

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
                .dbf  = 0  ///< CAN RX and TX frozen during debug (reset value is 1)
            },
            .btr = {
                .lbkm = 0, ///< Loop back mode for debug (reset value is 0)
                .silm = 0  ///< Silent mode for debug (reset value is 0)
            }
        }
    };
    lib::UniquePointer<drv::Can> can( drv::Can::create(config) );
    testTxLine(*can);
    testRxLine(*can);
    testTxRxLoop(*can);
    while(true);
}

} // namespace eoos
