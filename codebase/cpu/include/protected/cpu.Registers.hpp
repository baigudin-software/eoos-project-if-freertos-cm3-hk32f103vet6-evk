/**
 * @file      cpu.Registers.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2023, Sergey Baigudin, Baigudin Software
 */ 
#ifndef CPU_REGISTERS_HPP_
#define CPU_REGISTERS_HPP_

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
     * Constructor.
     */    
    Registers();

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
     * @brief System Control Space
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
