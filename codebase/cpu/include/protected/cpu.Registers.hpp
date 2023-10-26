/**
 * @file      cpu.Registers.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2023, Sergey Baigudin, Baigudin Software
 */ 
#ifndef CPU_REGISTERS_HPP_
#define CPU_REGISTERS_HPP_

#include "cpu.reg.Usart.hpp"
#include "cpu.reg.Gpio.hpp"
#include "cpu.reg.Rcc.hpp"
#include "cpu.reg.Flash.hpp"
#include "cpu.reg.Auxiliary.hpp"
#include "cpu.reg.SysTick.hpp"
#include "cpu.reg.Nvic.hpp"
#include "cpu.reg.Scb.hpp"

namespace eoos
{
namespace cpu
{
    
/**
 * @struct Registers
 * @brief HK32F103xCxDxE HW register model.
 */    
struct Registers
{
    /**
     * @brief Constructor.
     */    
    Registers();
    
    /**
     * @brief Index USART.
     */    
    static const int32_t INDEX_USART1 = 0;
    static const int32_t INDEX_USART2 = 1;
    static const int32_t INDEX_USART3 = 2;
    static const int32_t INDEX_UART4  = 3;
    static const int32_t INDEX_UART5  = 4;
    
    /**
     * @brief Index GPIO.
     */    
    static const int32_t INDEX_GPIOA = 0;
    static const int32_t INDEX_GPIOB = 1;
    static const int32_t INDEX_GPIOC = 2;
    static const int32_t INDEX_GPIOD = 3;
    static const int32_t INDEX_GPIOE = 4;    

    /**
     * @brief Universal Synchronous Asynchronous Transceiver (USART).
     *
     * USART1: 0x40013800 - 0x40013BFF;
     * USART2: 0x40004400 - 0x400047FF;
     * USART3: 0x40004800 - 0x40004BFF;
     * UART4 : 0x40004C00 - 0x40004FFF;
     * UART5 : 0x40005000 - 0x400053FF;
     */
    reg::Usart* usart[5];
    
    /**
     * @brief General-purpose Input Output (GPIO).
     *
     * GPIOA: 0x40010800 - 0x40010BFF;
     * GPIOB: 0x40010C00 - 0X40010FFF;
     * GPIOC: 0x40011000 - 0x400113FF;
     * GPIOD: 0x40011400 - 0x400117FF;
     * GPIOE: 0x40011800 - 0x40011BFF;
     */
    reg::Gpio* gpio[5];

    /**
     * @brief Reset and Clock Control.
     * 0x40021000 - 0x400213FF
     */    
    reg::Rcc* rcc;    
    
    /**
     * @brief Flash Memory Interface/Cache.
     * 0x40022000 - 0x400223FF
     */
    reg::Flash* flash;

    /**
     * @brief System Control Space.
     * 0xE000E000 - 0xE000EFFF
     */
    struct Scs
    {
        /**
         * Constructor.
         */    
        Scs();
        
        /**
         * @brief Auxiliary Control Register of System Control Space.
         * 0xE000E000 - 0xE000E00F
         */
        reg::Auxiliary* aux;
        
        /**
         * @brief SysTick Control and Status Register of System Control Space.
         * 0xE000E010 - 0xE000E0FF
         */    
        reg::SysTick* tick;    
        
        /**
         * @brief Nested Vectored Interrupt Controller.
         * 0xE000E100 - 0xE000ECFF
         */    
        reg::Nvic* nvic;
            
        /**
         * @brief System Control Block.
         * 0xE000ED00 - 0xE000ED8F
         */    
        reg::Scb* scb;
        
    } scs;
    
};    
    
} // namespace cpu
} // namespace eoos
#endif // CPU_REGISTERS_HPP_
