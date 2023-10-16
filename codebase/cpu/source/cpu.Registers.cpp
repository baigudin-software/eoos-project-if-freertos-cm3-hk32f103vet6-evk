/**
 * @file      cpu.Registers.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2023, Sergey Baigudin, Baigudin Software
 */ 
#include "cpu.Registers.hpp"

namespace eoos
{
namespace cpu
{
    
Registers::Registers()
    : rcc   ( new (reg::Rcc::ADDRESS)   reg::Rcc   )
    , flash ( new (reg::Flash::ADDRESS) reg::Flash ) 
    , scs() {
    usart[0] = new (reg::Usart::ADDRESS_USART1) reg::Usart;
    usart[1] = new (reg::Usart::ADDRESS_USART2) reg::Usart;
    usart[2] = new (reg::Usart::ADDRESS_USART3) reg::Usart;
    usart[3] = new (reg::Usart::ADDRESS_UART4)  reg::Usart;
    usart[4] = new (reg::Usart::ADDRESS_UART5)  reg::Usart;    
}
   
Registers::Scs::Scs()
    : aux  ( new (reg::Auxiliary::ADDRESS) reg::Auxiliary )
    , tick ( new (reg::SysTick::ADDRESS)   reg::SysTick   ) 
    , nvic ( new (reg::Nvic::ADDRESS)      reg::Nvic      ) 
    , scb  ( new (reg::Scb::ADDRESS)       reg::Scb       ) {
}  
    
} // namespace cpu
} // namespace eoos
