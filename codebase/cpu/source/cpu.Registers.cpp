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

    usart[INDEX_USART1] = new (reg::Usart::ADDRESS_USART1) reg::Usart;
    usart[INDEX_USART2] = new (reg::Usart::ADDRESS_USART2) reg::Usart;
    usart[INDEX_USART3] = new (reg::Usart::ADDRESS_USART3) reg::Usart;
    usart[INDEX_UART4]  = new (reg::Usart::ADDRESS_UART4)  reg::Usart;
    usart[INDEX_UART5]  = new (reg::Usart::ADDRESS_UART5)  reg::Usart;
    
    gpio[INDEX_GPIOA] = new (reg::Gpio::ADDRESS_GPIOA) reg::Gpio;
    gpio[INDEX_GPIOB] = new (reg::Gpio::ADDRESS_GPIOB) reg::Gpio;
    gpio[INDEX_GPIOC] = new (reg::Gpio::ADDRESS_GPIOC) reg::Gpio;
    gpio[INDEX_GPIOD] = new (reg::Gpio::ADDRESS_GPIOD) reg::Gpio;
    gpio[INDEX_GPIOE] = new (reg::Gpio::ADDRESS_GPIOE) reg::Gpio;
}
   
Registers::Scs::Scs()
    : aux  ( new (reg::Auxiliary::ADDRESS) reg::Auxiliary )
    , tick ( new (reg::SysTick::ADDRESS)   reg::SysTick   ) 
    , nvic ( new (reg::Nvic::ADDRESS)      reg::Nvic      ) 
    , scb  ( new (reg::Scb::ADDRESS)       reg::Scb       ) {
}  
    
} // namespace cpu
} // namespace eoos
