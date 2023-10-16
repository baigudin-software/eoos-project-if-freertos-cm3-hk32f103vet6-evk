/**
 * @file      cpu.reg.Usart.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2023, Sergey Baigudin, Baigudin Software
 */
#ifndef CPU_REG_USART_HPP_
#define CPU_REG_USART_HPP_

#include "Types.hpp"

namespace eoos
{
namespace cpu
{
namespace reg
{

/**
 * @struct Usart
 * @brief Universal Synchronous Asynchronous Transceiver (USART).
 */
struct Usart
{

public:
  
    /**
     * @brief Addresses.
     */    
    static const uint32_t ADDRESS_USART1 = 0x40013800;
    static const uint32_t ADDRESS_USART2 = 0x40004400;
    static const uint32_t ADDRESS_USART3 = 0x40004800;
    static const uint32_t ADDRESS_UART4  = 0x40004C00;
    static const uint32_t ADDRESS_UART5  = 0x40005000;

    /** 
     * @brief Constructor.
     */  
    Usart()
        : sr()
        , dr()
        , brr()
        , cr1()
        , cr2()
        , cr3()
        , gtpr() {
    }

    /** 
     * @brief Destructor.
     */  
    ~Usart(){}
   
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
     * @brief Status register (USARTx_SR).
     */     
    union Sr
    {
        Sr(){}
        Sr(uint32_t v){value = v;}
       ~Sr(){}    
      
        uint32_t value;
        struct 
        {
            uint32_t pe   : 1;
            uint32_t fe   : 1;
            uint32_t ne   : 1;
            uint32_t ore  : 1;
            uint32_t idle : 1;
            uint32_t rxne : 1;
            uint32_t tc   : 1;
            uint32_t txe  : 1;
            uint32_t lbd  : 1;
            uint32_t cts  : 1;
            uint32_t      : 22;
        } bit;
    };

    /**
     * @brief Data register (USARTx_DR).
     */     
    union Dr
    {
        Dr(){}
        Dr(uint32_t v){value = v;}
       ~Dr(){}    
      
        uint32_t value;
        struct 
        {
            uint32_t dr : 9;
            uint32_t    : 23;            
        } bit;
    };

    /**
     * @brief Baud Rate Register (USARTx_BRR).
     */
    union Brr
    {
        Brr(){}
        Brr(uint32_t v){value = v;}
       ~Brr(){}    
      
        uint32_t value;
        struct 
        {
            uint32_t divfraction : 4;
            uint32_t divmantissa : 12;
            uint32_t             : 16;
        } bit;
    };

    /**
     * @brief Control register 1 (USARTx_CR1).
     */
    union Cr1
    {
        Cr1(){}
        Cr1(uint32_t v){value = v;}
       ~Cr1(){}    
      
        uint32_t value;
        struct 
        {
            uint32_t sbk    : 1;
            uint32_t rwu    : 1;
            uint32_t re     : 1;
            uint32_t te     : 1;
            uint32_t idleie : 1;
            uint32_t rxneie : 1;
            uint32_t tcie   : 1;
            uint32_t txeie  : 1;
            uint32_t peie   : 1;
            uint32_t ps     : 1;
            uint32_t pce    : 1;
            uint32_t wake   : 1;
            uint32_t m      : 1;
            uint32_t ue     : 1;
            uint32_t        : 18;
        } bit;
    };

    /**
     * @brief Control register 2 (USARTx_CR2).
     */
    union Cr2
    {
        Cr2(){}
        Cr2(uint32_t v){value = v;}
       ~Cr2(){}    
      
        uint32_t value;
        struct 
        {
            uint32_t add   : 4;
            uint32_t       : 1;
            uint32_t lbdl  : 1;
            uint32_t lbdie : 1;
            uint32_t       : 1;
            uint32_t lbcl  : 1;
            uint32_t cpha  : 1;
            uint32_t cpol  : 1;
            uint32_t clken : 1;
            uint32_t stop  : 2;
            uint32_t linen : 1;
            uint32_t       : 17;
        } bit;
    };

    /**
     * @brief Control register 3 (USARTx_CR3).
     */
    union Cr3
    {
        Cr3(){}
        Cr3(uint32_t v){value = v;}
       ~Cr3(){}    
      
        uint32_t value;
        struct 
        {
            uint32_t eie   : 1;
            uint32_t iren  : 1;
            uint32_t irlp  : 1;
            uint32_t hdsel : 1;
            uint32_t nack  : 1;
            uint32_t scen  : 1;
            uint32_t dmar  : 1;
            uint32_t dmat  : 1;
            uint32_t rtse  : 1;
            uint32_t ctse  : 1;
            uint32_t ctsie : 1;
            uint32_t       : 21;
        } bit;
    };

    /**
     * @brief Protection Time and Prescaler Register (USARTx_GTPR).
     */
    union Gtpr
    {
        Gtpr(){}
        Gtpr(uint32_t v){value = v;}
       ~Gtpr(){}    
      
        uint32_t value;
        struct 
        {
            uint32_t psc : 1;
            uint32_t gt  : 1;
            uint32_t     : 1;
        } bit;
    };
    
    /**
     * @brief Register map.
     */
public:
    Sr   sr;   // 0x00
    Dr   dr;   // 0x04
    Brr  brr;  // 0x08
    Cr1  cr1;  // 0x0C
    Cr2  cr2;  // 0x10
    Cr3  cr3;  // 0x14
    Gtpr gtpr; // 0x18
    
};

} // namespace reg
} // namespace cpu
} // namespace eoos
#endif // CPU_REG_SYSTICK_HPP_
