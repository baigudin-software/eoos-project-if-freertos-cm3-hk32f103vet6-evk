/**
 * @file      cpu.reg.SysTick.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2023, Sergey Baigudin, Baigudin Software
 */
#ifndef CPU_REG_SYSTICK_HPP_
#define CPU_REG_SYSTICK_HPP_

#include "Types.hpp"

namespace eoos
{
namespace cpu
{
namespace reg
{

/**
 * @struct SysTick
 * @brief System tick of System Control Space.
 */
struct SysTick
{

public:
  
    /**
     * @brief System Control address.
     */    
    static const uint32_t ADDRESS = 0xE000E010;
        
    /** 
     * @brief Constructor.
     */  
    SysTick()
        : csr()      
        , rvr()      
        , cvr()      
        , cr() {
    }

    /** 
     * @brief Destructor.
     */  
    ~SysTick(){}
   
    /**
     * @brief Operator new.
     *
     * @param size Unused.
     * @param ptr  Address of memory.
     * @return The address of memory.
     */
    void* operator new(size_t, uint32_t ptr)
    {
        return reinterpret_cast<void*>(ptr);
    }

    /**
     * @brief SysTick Control and Status Register.
     */
    union Csr
    {
        Csr(){}
        Csr(uint32_t v){value = v;}
       ~Csr(){}    
      
        uint32_t value;
        struct 
        {
            uint32_t enable    : 1;
            uint32_t tickint   : 1;
            uint32_t clksource : 1;
            uint32_t           : 13;
            uint32_t countflag : 1;
            uint32_t           : 15;
        } bit;
    };

    /**
     * @brief SysTick Reload Value Register.
     */
    union Rvr
    {
        Rvr(){}
        Rvr(uint32_t v){value = v;}
       ~Rvr(){}    
      
        uint32_t value;
        struct 
        {
            uint32_t reload : 24;
            uint32_t        : 8;
        } bit;
    };

    /**
     * @brief SysTick Current Value Register.
     */
    union Cvr
    {
        Cvr(){}
        Cvr(uint32_t v){value = v;}
       ~Cvr(){}    
      
        uint32_t value;
        struct 
        {
            uint32_t current : 32;
        } bit;
    };

    /**
     * @brief SysTick Calibration Value Register.
     */
    union Cr
    {
        Cr(){}
        Cr(uint32_t v){value = v;}
       ~Cr(){}    
      
        uint32_t value;
        struct 
        {
            uint32_t tenms : 24;
            uint32_t       : 6;
            uint32_t skew  : 1;
            uint32_t noref : 1;
        } bit;
    };
    
    /**
     * @brief Register map.
     */
public:
    Csr csr;   // 0xE000E010
    Rvr rvr;   // 0xE000E014
    Cvr cvr;   // 0xE000E018
    Cr  cr;    // 0xE000E01C
};

} // namespace reg
} // namespace cpu
} // namespace eoos
#endif // CPU_REG_SYSTICK_HPP_
