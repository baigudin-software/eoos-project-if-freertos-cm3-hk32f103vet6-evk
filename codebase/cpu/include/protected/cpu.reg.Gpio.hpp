/**
 * @file      cpu.reg.Gpio.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2023, Sergey Baigudin, Baigudin Software
 */
#ifndef CPU_REG_GPIO_HPP_
#define CPU_REG_GPIO_HPP_

#include "Types.hpp"

namespace eoos
{
namespace cpu
{
namespace reg
{

/**
 * @struct Gpio
 * @brief General-purpose Input Output (GPIO).
 */
struct Gpio
{

public:
  
    /**
     * @brief Addresses.
     */    
    static const uint32_t ADDRESS_GPIOA = 0x40010800;
    static const uint32_t ADDRESS_GPIOB = 0x40010C00;
    static const uint32_t ADDRESS_GPIOC = 0x40011000;
    static const uint32_t ADDRESS_GPIOD = 0x40011400;
    static const uint32_t ADDRESS_GPIOE = 0x40011800;

    /** 
     * @brief Constructor.
     */  
    Gpio()
        : crl() 
        , crh() 
        , idr()
        , odr()
        , bsrr()
        , brr()
        , lckr()
        , iosen() {    
    }

    /** 
     * @brief Destructor.
     */  
    ~Gpio(){}
   
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
     * @brief Port x Configuration Low Register (GPIOx_CRL).
     */     
    union Crl
    {
        Crl(){}
        Crl(uint32_t v){value = v;}
       ~Crl(){}    
      
        uint32_t value;
        struct 
        {
            uint32_t mode0 : 2;
            uint32_t cnf0  : 2;
            uint32_t mode1 : 2;
            uint32_t cnf1  : 2;
            uint32_t mode2 : 2;
            uint32_t cnf2  : 2;
            uint32_t mode3 : 2;
            uint32_t cnf3  : 2;
            uint32_t mode4 : 2;
            uint32_t cnf4  : 2;
            uint32_t mode5 : 2;
            uint32_t cnf5  : 2;
            uint32_t mode6 : 2;
            uint32_t cnf6  : 2;
            uint32_t mode7 : 2;
            uint32_t cnf7  : 2;
        } bit;
    };

    /**
     * @brief Port x Configuration High Register (GPIOx_CRH).
     */     
    union Crh
    {
        Crh(){}
        Crh(uint32_t v){value = v;}
       ~Crh(){}    
      
        uint32_t value;
        struct 
        {
            uint32_t mode8  : 2;
            uint32_t cnf8   : 2;
            uint32_t mode9  : 2;
            uint32_t cnf9   : 2;
            uint32_t mode10 : 2;
            uint32_t cnf10  : 2;
            uint32_t mode11 : 2;
            uint32_t cnf11  : 2;
            uint32_t mode12 : 2;
            uint32_t cnf12  : 2;
            uint32_t mode13 : 2;
            uint32_t cnf13  : 2;
            uint32_t mode14 : 2;
            uint32_t cnf14  : 2;
            uint32_t mode15 : 2;
            uint32_t cnf15  : 2;
        } bit;
    };

    /**
     * @brief Port x Input Data Register (GPIOx_IDR).
     */     
    union Idr
    {
        Idr(){}
        Idr(uint32_t v){value = v;}
       ~Idr(){}    
      
        uint32_t value;
        struct 
        {
            uint32_t idr0  : 1;
            uint32_t idr1  : 1;
            uint32_t idr2  : 1;
            uint32_t idr3  : 1;
            uint32_t idr4  : 1;
            uint32_t idr5  : 1;
            uint32_t idr6  : 1;
            uint32_t idr7  : 1;
            uint32_t idr8  : 1;
            uint32_t idr9  : 1;
            uint32_t idr10 : 1;
            uint32_t idr11 : 1;
            uint32_t idr12 : 1;
            uint32_t idr13 : 1;
            uint32_t idr14 : 1;
            uint32_t idr15 : 1;
            uint32_t       : 15;
        } bit;
    };

    /**
     * @brief Port x Output Data Register (GPIOx_ODR).
     */     
    union Odr
    {
        Odr(){}
        Odr(uint32_t v){value = v;}
       ~Odr(){}    
      
        uint32_t value;
        struct 
        {
            uint32_t odr0  : 1;
            uint32_t odr1  : 1;
            uint32_t odr2  : 1;
            uint32_t odr3  : 1;
            uint32_t odr4  : 1;
            uint32_t odr5  : 1;
            uint32_t odr6  : 1;
            uint32_t odr7  : 1;
            uint32_t odr8  : 1;
            uint32_t odr9  : 1;
            uint32_t odr10 : 1;
            uint32_t odr11 : 1;
            uint32_t odr12 : 1;
            uint32_t odr13 : 1;
            uint32_t odr14 : 1;
            uint32_t odr15 : 1;
            uint32_t       : 15;
        } bit;
    };

    /**
     * @brief Port x bit set/clear register (GPIOx_BSRR).
     */     
    union Bsrr
    {
        Bsrr(){}
        Bsrr(uint32_t v){value = v;}
       ~Bsrr(){}    
      
        uint32_t value;
        struct 
        {
            uint32_t bs0  : 1;
            uint32_t bs1  : 1;
            uint32_t bs2  : 1;
            uint32_t bs3  : 1;
            uint32_t bs4  : 1;
            uint32_t bs5  : 1;
            uint32_t bs6  : 1;
            uint32_t bs7  : 1;
            uint32_t bs8  : 1;
            uint32_t bs9  : 1;
            uint32_t bs10 : 1;
            uint32_t bs11 : 1;
            uint32_t bs12 : 1;
            uint32_t bs13 : 1;
            uint32_t bs14 : 1;
            uint32_t bs15 : 1;
            uint32_t br0  : 1;
            uint32_t br1  : 1;
            uint32_t br2  : 1;
            uint32_t br3  : 1;
            uint32_t br4  : 1;
            uint32_t br5  : 1;
            uint32_t br6  : 1;
            uint32_t br7  : 1;
            uint32_t br8  : 1;
            uint32_t br9  : 1;
            uint32_t br10 : 1;
            uint32_t br11 : 1;
            uint32_t br12 : 1;
            uint32_t br13 : 1;
            uint32_t br14 : 1;
            uint32_t br15 : 1;
        } bit;
    };

    /**
     * @brief Port x bit clear register (GPIOx_BRR).
     */     
    union Brr
    {
        Brr(){}
        Brr(uint32_t v){value = v;}
       ~Brr(){}    
      
        uint32_t value;
        struct 
        {
            uint32_t br0  : 1;
            uint32_t br1  : 1;
            uint32_t br2  : 1;
            uint32_t br3  : 1;
            uint32_t br4  : 1;
            uint32_t br5  : 1;
            uint32_t br6  : 1;
            uint32_t br7  : 1;
            uint32_t br8  : 1;
            uint32_t br9  : 1;
            uint32_t br10 : 1;
            uint32_t br11 : 1;
            uint32_t br12 : 1;
            uint32_t br13 : 1;
            uint32_t br14 : 1;
            uint32_t br15 : 1;
            uint32_t      : 15;
        } bit;
    };

    /**
     * @brief Port x Configuration Lock Register (GPIOx_LCKR).
     */     
    union Lckr
    {
        Lckr(){}
        Lckr(uint32_t v){value = v;}
       ~Lckr(){}    
      
        uint32_t value;
        struct 
        {
            uint32_t lck0  : 1;
            uint32_t lck1  : 1;
            uint32_t lck2  : 1;
            uint32_t lck3  : 1;
            uint32_t lck4  : 1;
            uint32_t lck5  : 1;
            uint32_t lck6  : 1;
            uint32_t lck7  : 1;
            uint32_t lck8  : 1;
            uint32_t lck9  : 1;
            uint32_t lck10 : 1;
            uint32_t lck11 : 1;
            uint32_t lck12 : 1;
            uint32_t lck13 : 1;
            uint32_t lck14 : 1;
            uint32_t lck15 : 1;
            uint32_t lckk  : 1;
            uint32_t       : 14;
        } bit;
    };

    /**
     * @brief Port x Schmitt Trigger Configuration Register (GPIOx_IOSEN).
     */     
    union Iosen
    {
        Iosen(){}
        Iosen(uint32_t v){value = v;}
       ~Iosen(){}    
      
        uint32_t value;
        struct 
        {
            uint32_t iosen0  : 1;
            uint32_t iosen1  : 1;
            uint32_t iosen2  : 1;
            uint32_t iosen3  : 1;
            uint32_t iosen4  : 1;
            uint32_t iosen5  : 1;
            uint32_t iosen6  : 1;
            uint32_t iosen7  : 1;
            uint32_t iosen8  : 1;
            uint32_t iosen9  : 1;
            uint32_t iosen10 : 1;
            uint32_t iosen11 : 1;
            uint32_t iosen12 : 1;
            uint32_t iosen13 : 1;
            uint32_t iosen14 : 1;
            uint32_t iosen15 : 1;
            uint32_t         : 15;
        } bit;
    };
    
    /**
     * @brief Register map.
     */
public:
    Crl      crl;   // 0x00
    Crh      crh;   // 0x04
    Idr      idr;   // 0x08
    Odr      odr;   // 0x0C
    Bsrr     bsrr;  // 0x10
    Brr      brr;   // 0x14
    Lckr     lckr;  // 0x18
private:
    uint32_t space0_[5];
public:
    Iosen    iosen; // 0x30
    
};

} // namespace reg
} // namespace cpu
} // namespace eoos
#endif // CPU_REG_GPIO_HPP_
