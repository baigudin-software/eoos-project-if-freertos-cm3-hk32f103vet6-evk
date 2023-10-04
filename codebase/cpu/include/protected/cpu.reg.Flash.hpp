/**
 * @file      cpu.reg.Flash.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2023, Sergey Baigudin, Baigudin Software
 */
#ifndef CPU_REG_FLASH_HPP_
#define CPU_REG_FLASH_HPP_

#include "Types.hpp"

namespace eoos
{
namespace cpu
{
namespace reg
{

/**
 * @struct Flash
 * @brief HK32F103xCxDxE Embedded Flash (FLASH).
 */
struct Flash
{

public:
  
    /**
     * @brief Flash address.
     */    
    static const uint32_t ADDRESS = 0x40022000;
        
    /** 
     * @brief Constructor.
     */  
    Flash()
        : acr()        
        , keyr()       
        , optkeyr()    
        , sr()         
        , cr()         
        , ar()         
        , obr()        
        , wrpr()       
        , latencyex()  
        , ecr()        
        , encryctl()   
        , decryctl()   
        , ukeyl()      
        , ukeyh()      
        , pw0()        
        , pw1()            
        , pw2()          
        , pw3() {
    }

    /** 
     * @brief Destructor.
     */  
    ~Flash(){}
   
    /**
     * @brief Operator new.
     *
     * @param size Unused.
     * @param ptr  Address of memory.
     * @return The address of memory.
     */
    static void* operator new(size_t, uint32_t ptr)
    {
        return reinterpret_cast<void*>(ptr);
    }
            
    /**
     * @brief Flash Access Control Register (FLASH_ACR).
     */
    union Acr
    {
        Acr(){}
        Acr(uint32_t v){value = v;}
       ~Acr(){}    
      
        uint32_t value;
        struct 
        {
            uint32_t latency : 3;
            uint32_t hlfcya  : 1;
            uint32_t prftbe  : 1;
            uint32_t prftbs  : 1;
            uint32_t         : 26;
        } bit;
    };
  
    /**
     * @brief Flash Keyword Register (FLASH_KEYR).
     */
    union Keyr
    {
        Keyr(){}
        Keyr(uint32_t v){value = v;}
       ~Keyr(){}    
      
        uint32_t value;
        struct 
        {
            uint32_t fkeyr : 32;   
        } bit;
    };
    
    /**
     * @brief Flash Option Keyword Register (FLASH_OPTKEYR).
     */
    union Optkeyr
    {
        Optkeyr(){}
        Optkeyr(uint32_t v){value = v;}
       ~Optkeyr(){}    
      
        uint32_t value;
        struct 
        {
            uint32_t optkey : 32;
        } bit;
    };
             
    /**
     * @brief Flash Status Register (FLASH_SR).
     */
    union Sr
    {
        Sr(){}
        Sr(uint32_t v){value = v;}
       ~Sr(){}    
      
        uint32_t value;
        struct 
        {
            uint32_t bsy      : 1;
            uint32_t          : 1;
            uint32_t pgerr    : 1;
            uint32_t          : 1;
            uint32_t wrprterr : 1;
            uint32_t eop      : 1;
            uint32_t          : 26;
        } bit;
    };

    /**
     * @brief Flash Control Register (FLASH_CR).
     */
    union Cr
    {
        Cr(){}
        Cr(uint32_t v){value = v;}
       ~Cr(){}    
      
        uint32_t value;
        struct 
        {
            uint32_t pg     : 1;
            uint32_t per    : 1;
            uint32_t mer    : 1;
            uint32_t        : 1;
            uint32_t optpg  : 1;
            uint32_t opter  : 1;
            uint32_t strt   : 1;
            uint32_t lock   : 1;
            uint32_t        : 1;
            uint32_t optwre : 1;
            uint32_t errie  : 1;
            uint32_t        : 1;
            uint32_t eopie  : 1;
            uint32_t        : 19;
        } bit;
    };

    /**
     * @brief Flash Address Register (FLASH_AR).
     */
    union Ar
    {
        Ar(){}
        Ar(uint32_t v){value = v;}
       ~Ar(){}    
      
        uint32_t value;
        struct 
        {
            uint32_t far : 32;
        } bit;
    };

    /**
     * @brief Flash Option Byte Register (FLASH_OBR).
     */
    union Obr
    {
        Obr(){}
        Obr(uint32_t v){value = v;}
       ~Obr(){}    
      
        uint32_t value;
        struct 
        {
            uint32_t opterr    : 1;
            uint32_t rdprt     : 1;
            uint32_t wdgsw     : 1;
            uint32_t nrststop  : 1;
            uint32_t nrststdby : 1;
            uint32_t           : 5;
            uint32_t data0     : 8;
            uint32_t data1     : 8;
            uint32_t           : 6;
        } bit;
    };

    /**
     * @brief Flash Write Protect Register (FLASH_WRPR).
     */
    union Wrpr
    {
        Wrpr(){}
        Wrpr(uint32_t v){value = v;}
       ~Wrpr(){}    
      
        uint32_t value;
        struct 
        {
            uint32_t wrp : 32;
        } bit;
    };
  
    /**
     * @brief Flash wait cycle register (FLASH_LATENCY_EX).
     */
    union Latencyex
    {
        Latencyex(){}
        Latencyex(uint32_t v){value = v;}
       ~Latencyex(){}    
      
        uint32_t value;
        struct 
        {
            uint32_t latency43 : 2;
            uint32_t           : 30;
        } bit;
    };
  
    /**
     * @brief Flash Control Register 2 (FLASH_ECR).
     */
    union Ecr
    {
        Ecr(){}
        Ecr(uint32_t v){value = v;}
       ~Ecr(){}    
      
        uint32_t value;
        struct 
        {
            uint32_t sethper : 1;
            uint32_t setwpg  : 1;
            uint32_t set2wpg : 1;
            uint32_t set4wpg : 1;
            uint32_t infhper : 1;
            uint32_t infhwpg : 1;
            uint32_t infwpg  : 1;
            uint32_t inf2wpg : 1;
            uint32_t inf4wpg : 1;
            uint32_t         : 23;    
        } bit;
    };
    
    /**
     * @brief Encryption Control Register (ENCRY_CFG).
     */
    union Encryctl
    {
        Encryctl(){}
        Encryctl(uint32_t v){value = v;}
       ~Encryctl(){}    
      
        uint32_t value;
        struct 
        {
            uint32_t encryen : 1;
            uint32_t         : 31;   
        } bit;
    };

    /**
     * @brief Decryption Control Register (DECRY_CFG).
     */
    union Decryctl
    {
        Decryctl(){}
        Decryctl(uint32_t v){value = v;}
       ~Decryctl(){}    
      
        uint32_t value;
        struct 
        {
            uint32_t decryen : 1;
            uint32_t         : 31;
        } bit;
    };
      
    /**
     * @brief Key Register 1 (UKEYL).
     */
    union Ukeyl
    {
        Ukeyl(){}
        Ukeyl(uint32_t v){value = v;}
       ~Ukeyl(){}    
      
        uint32_t value;
        struct 
        {
            uint32_t ukey : 32;
        } bit;
    };
      
    /**
     * @brief Key Register 2 (UKEYH).
     */
    union Ukeyh
    {
        Ukeyh(){}
        Ukeyh(uint32_t v){value = v;}
       ~Ukeyh(){}    
      
        uint32_t value;
        struct 
        {
            uint32_t ukey : 32;
        } bit;
    };
        
    /**
     * @brief Programming Data Register 0 (PW0).
     */
    union Pw0
    {
        Pw0(){}
        Pw0(uint32_t v){value = v;}
       ~Pw0(){}    
      
        uint32_t value;
        struct 
        {
            uint32_t pw0 : 32;
        } bit;
    };
      
    /**
     * @brief Programming Data Register 1 (PW1).
     */
    union Pw1
    {
        Pw1(){}
        Pw1(uint32_t v){value = v;}
       ~Pw1(){}    
      
        uint32_t value;
        struct 
        {
            uint32_t pw1 : 32;
        } bit;
    };
    
    /**
     * @brief Programming Data Register 2 (PW2).
     */
    union Pw2
    {
        Pw2(){}
        Pw2(uint32_t v){value = v;}
       ~Pw2(){}    
      
        uint32_t value;
        struct 
        {
            uint32_t pw0 : 32;
        } bit;
    };

    /**
     * @brief Programming Data Register 3 (PW3).
     */
    union Pw3
    {
        Pw3(){}
        Pw3(uint32_t v){value = v;}
       ~Pw3(){}    
      
        uint32_t value;
        struct 
        {
            uint32_t pw0 : 32;
        } bit;
    };
    
    /**
     * @brief Register map.
     */
public:
    Acr       acr;        // 0x40022000
    Keyr      keyr;       // 0x40022004
    Optkeyr   optkeyr;    // 0x40022008
    Sr        sr;         // 0x4002200C
    Cr        cr;         // 0x40022010
    Ar        ar;         // 0x40022014
private:
    uint32_t  space0_[0x01];
public:
    Obr       obr;        // 0x4002201C
    Wrpr      wrpr;       // 0x40022020
private:
    uint32_t  space1_[0x0F];
public:
    Latencyex latencyex;  // 0x40022060
private:
    uint32_t  space2_[0x03];
public:
    Ecr       ecr;        // 0x40022070
private:
    uint32_t  space3_[0x01];
public:
    Encryctl  encryctl;   // 0x40022078
    Decryctl  decryctl;   // 0x4002207C
    Ukeyl     ukeyl;      // 0x40022080
    Ukeyh     ukeyh;      // 0x40022084
private:
    uint32_t  space4_[0x01];
public:
    Pw0       pw0;        // 0x40022090
    Pw1       pw1;        // 0x40022094
    Pw2       pw2;        // 0x40022098
    Pw3       pw3;        // 0x4002209C
};

} // namespace reg
} // namespace cpu
} // namespace eoos
#endif // CPU_REG_FLASH_HPP_
