/**
 * @file      pcb.Board.cpp
 * @brief     EOOS printed circuit board
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2023, Sergey Baigudin, Baigudin Software
 */
#include "pcb.Board.hpp"
#include "sys.Call.hpp"

namespace eoos
{
namespace pcb
{
    
Board::Board()
    : lib::NonCopyable<lib::NoAllocator>()
    , usart_() {     
    bool_t const isConstructed( construct() );
    setConstructed( isConstructed );
}

Board::~Board()
{
    deinitializeUsart();
}

bool_t Board::construct()
{
    bool_t res( false );
    do 
    {
        if( !isConstructed() )
        {
            break;
        }
        if( !initializeUsart() )
        {
            break;
        }
        res = true;
    } while(false);
    return res;
}

bool_t Board::initializeUsart()
{
    bool_t res( false );
    drv::Usart::SerialLineConfig config = {
        .number      = drv::Usart::NUMBER_USART1,
        .mode        = drv::Usart::MODE_TX,
        .baud        = drv::Usart::BAUD_115200,
        .dataBits    = drv::Usart::DATABITS_8,
        .stopBits    = drv::Usart::STOPBITS_1,
        .parity      = drv::Usart::PARITY_NONE,
        .flowControl = drv::Usart::FLOWCONTROL_NONE
    };
    usart_.reset( drv::Usart::create(config) );
    if( usart_ )
    {
        api::StreamManager& stream( sys::Call::get().getStreamManager() );
        res = true;
        res &= stream.setCout( *usart_ );
        res &= stream.setCerr( *usart_ );
    }
    return res;
}

void Board::deinitializeUsart()
{
    api::StreamManager& stream( sys::Call::get().getStreamManager() );    
    stream.resetCout();
    stream.resetCerr();
}

} // namespace pcb
} // namespace eoos
