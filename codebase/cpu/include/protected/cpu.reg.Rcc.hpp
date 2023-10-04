/**
 * @file      cpu.reg.Rcc.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2023, Sergey Baigudin, Baigudin Software
 */
#ifndef CPU_REG_RCC_HPP_
#define CPU_REG_RCC_HPP_

#include "Types.hpp"

namespace eoos
{
namespace cpu
{
namespace reg
{

/**
 * @struct Rcc
 * @brief HK32F103xCxDxE Reset and clock control (RCC).
 */
struct Rcc
{

public:
  
    /**
     * @brief RCC address.
     */    
    static const uint32_t ADDRESS = 0x40021000;
        
    /** 
     * @brief Constructor.
     */  
    Rcc() 
        : cr()
        , cfgr()
        , cir()
        , apb2rstr()
        , apb1rstr()
        , ahbenr()
        , apb2enr()
        , apb1enr()
        , bdcr()
        , csr()
        , cfgr2()  
        , cfgr3()  
        , cr2()    
        , hsectl() 
        , pllctl() 
        , cfgr4()  
        , cfgr5()  
        , cfgr6()  
        , ahbrst2()
        , ahbrst3()
        , lsictl() {
    }
  
    /** 
     * @brief Destructor.
     */  
    ~Rcc(){}
   
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
     * @brief Clock control register (RCC_CR).
     */
    union Cr
    {
        Cr(){}
        Cr(uint32_t v){value = v;}
       ~Cr(){}    
      
        uint32_t value;
        struct 
        {
            uint32_t hsion    : 1;
            uint32_t hsirdy   : 1;
            uint32_t          : 1;
            uint32_t hsitrim  : 5;
            uint32_t hsical   : 8;
            uint32_t hseon    : 1;
            uint32_t hserdy   : 1;
            uint32_t hsebyp   : 1;
            uint32_t csson    : 1;
            uint32_t          : 4;
            uint32_t pllon    : 1;
            uint32_t pllrdy   : 1;
            uint32_t          : 6;
        } bit;
    };
    
    /**
     * @brief Clock configuration register (RCC_CFGR).
     */
    union Cfgr
    {
        Cfgr(){}
        Cfgr(uint32_t v){value = v;}
       ~Cfgr(){}    
      
        uint32_t value;
        struct 
        {
            uint32_t sw       : 2;
            uint32_t sws      : 2;
            uint32_t hpre     : 4;
            uint32_t ppre1    : 3;
            uint32_t ppre2    : 3;
            uint32_t adcpre   : 2;
            uint32_t pllsrc   : 1;
            uint32_t pllxtpre : 1;
            uint32_t pllmul   : 4;
            uint32_t usbpre   : 1;
            uint32_t          : 1;
            uint32_t mco      : 3;
            uint32_t          : 5;

        } bit;
    };
    
    /**
     * @brief Clock interrupt register (RCC_CIR).
     */
    union Cir
    {
        Cir(){}
        Cir(uint32_t v){value = v;}
       ~Cir(){}    
      
        uint32_t value;
        struct 
        {
            uint32_t lsirdyf  : 1;          
            uint32_t lserdyf  : 1;
            uint32_t hsirdyf  : 1;
            uint32_t hserdyf  : 1;
            uint32_t pllrdyf  : 1;
            uint32_t          : 2;
            uint32_t cssf     : 1;
            uint32_t lsirdyie : 1;
            uint32_t lserdyie : 1;
            uint32_t hsirdyie : 1;
            uint32_t hserdyie : 1;
            uint32_t pllrdyie : 1;
            uint32_t          : 3;
            uint32_t lsirdyc  : 1;
            uint32_t lserdyc  : 1;
            uint32_t hsirdyc  : 1;
            uint32_t hserdyc  : 1;
            uint32_t pllrdyc  : 1;
            uint32_t          : 2;
            uint32_t cssc     : 1;
            uint32_t          : 8;           
        } bit;
    };
        
    /**
     * @brief APB2 peripheral reset register (RCC_APB2RSTR).
     */
    union Apb2rstr
    {
        Apb2rstr(){}
        Apb2rstr(uint32_t v){value = v;}
       ~Apb2rstr(){}    
      
        uint32_t value;
        struct 
        {
            uint32_t afiorst   : 1;           
            uint32_t           : 1;
            uint32_t ioparst   : 1;
            uint32_t iopbrst   : 1;
            uint32_t iopcrst   : 1;
            uint32_t iopdrst   : 1;
            uint32_t ioperst   : 1;
            uint32_t           : 1; // iopfrst
            uint32_t iopgrst   : 1;
            uint32_t adc1rst   : 1;
            uint32_t adc2rst   : 1;
            uint32_t tim1rst   : 1;
            uint32_t spi1rst   : 1;
            uint32_t tim8rst   : 1;
            uint32_t usart1rst : 1;
            uint32_t adc3rst   : 1;
            uint32_t           : 3;
            uint32_t           : 1; // tim9rst 
            uint32_t           : 1; // tim10rst
            uint32_t           : 1; // tim11rst
            uint32_t           : 10;
        } bit;
    };

    /**
     * @brief APB1 peripheral reset register (RCC_APB1RSTR).
     */
    union Apb1rstr
    {
        Apb1rstr(){}
        Apb1rstr(uint32_t v){value = v;}
       ~Apb1rstr(){}    
      
        uint32_t value;
        struct 
        {
            uint32_t tim2rst   : 1;
            uint32_t tim3rst   : 1;
            uint32_t tim4rst   : 1;
            uint32_t tm5rst    : 1;
            uint32_t tm6rst    : 1;
            uint32_t tm7rst    : 1;
            uint32_t           : 1; // tim12rst
            uint32_t           : 1; // tim13rst
            uint32_t           : 1; // tim14rst
            uint32_t           : 2;
            uint32_t wwdgrst   : 1;
            uint32_t           : 2;
            uint32_t spi2rst   : 1;
            uint32_t spi3rst   : 1;
            uint32_t           : 1;
            uint32_t usart2rst : 1;
            uint32_t usart3rst : 1;
            uint32_t uart4rst  : 1;
            uint32_t uart5rst  : 1;
            uint32_t i2c1rst   : 1;
            uint32_t i2c2rst   : 1;
            uint32_t usbrst    : 1;
            uint32_t           : 1;
            uint32_t canrst    : 1;
            uint32_t           : 1;
            uint32_t bkprst    : 1;
            uint32_t pwrrst    : 1;
            uint32_t dacrst    : 1;
            uint32_t           : 2;
        } bit;
    };

    /**
     * @brief AHB peripheral clock enable register (RCC_AHBENR).
     */
    union Ahbenr
    {
        Ahbenr(){}
        Ahbenr(uint32_t v){value = v;}
       ~Ahbenr(){}    
      
        uint32_t value;
        struct 
        {
            uint32_t dma1en   : 1;
            uint32_t dma2en   : 1;
            uint32_t sramen   : 1;
            uint32_t          : 1;
            uint32_t flitfen  : 1;
            uint32_t          : 1;
            uint32_t crcen    : 1;
            uint32_t          : 1;
            uint32_t fsmcen   : 1;
            uint32_t          : 1;
            uint32_t sdioen   : 1;
            uint32_t          : 21;
        } bit;
    };
    
    /**
     * @brief APB2 peripheral clock enable register (RCC_APB2ENR).
     */
    union Apb2enr
    {
        Apb2enr(){}
        Apb2enr(uint32_t v){value = v;}
       ~Apb2enr(){}    
      
        uint32_t value;
        struct 
        {
            uint32_t afioen   : 1;
            uint32_t          : 1;
            uint32_t iopaen   : 1;
            uint32_t iopben   : 1;
            uint32_t iopcen   : 1;
            uint32_t iopden   : 1;
            uint32_t iopeen   : 1;
            uint32_t          : 1; // iopfen
            uint32_t          : 1; // iopgen
            uint32_t adc1en   : 1;
            uint32_t adc2en   : 1;
            uint32_t tim1en   : 1;
            uint32_t spi1en   : 1;
            uint32_t tim8en   : 1;
            uint32_t usart1en : 1;
            uint32_t adc3en   : 1;
            uint32_t          : 3;
            uint32_t          : 1; // tim9en 
            uint32_t          : 1; // tim10en
            uint32_t          : 1; // tim11en
            uint32_t          : 10;
        } bit;
    };
    
    /**
     * @brief APB1 peripheral clock enable register (RCC_APB1ENR).
     */
    union Apb1enr
    {
        Apb1enr(){}
        Apb1enr(uint32_t v){value = v;}
       ~Apb1enr(){}    
      
        uint32_t value;
        struct 
        {
            uint32_t tim2en   : 1;
            uint32_t tim3en   : 1;
            uint32_t tim4en   : 1;
            uint32_t tim5en   : 1;
            uint32_t tim6en   : 1;
            uint32_t tim7en   : 1;
            uint32_t          : 1; // tim12en
            uint32_t          : 1; // tim13en
            uint32_t          : 1; // tim14en
            uint32_t          : 2;
            uint32_t wwdgen   : 1;
            uint32_t          : 2;
            uint32_t spi2en   : 1;
            uint32_t spi3en   : 1;
            uint32_t          : 1;
            uint32_t usart2en : 1;
            uint32_t usart3en : 1;
            uint32_t uart4en  : 1;
            uint32_t uart5en  : 1;
            uint32_t i2c1en   : 1;
            uint32_t i2c2en   : 1;
            uint32_t usben    : 1;
            uint32_t          : 1;
            uint32_t canen    : 1;
            uint32_t          : 1;
            uint32_t bkpen    : 1;
            uint32_t pwren    : 1;
            uint32_t dacen    : 1;
            uint32_t          : 2;
        } bit;
    };

    /**
     * @brief Backup domain control register (RCC_BDCR).
     */
    union Bdcr
    {
        Bdcr(){}
        Bdcr(uint32_t v){value = v;}
       ~Bdcr(){}    
      
        uint32_t value;
        struct 
        {
            uint32_t lseon    : 1;
            uint32_t lserdy   : 1;
            uint32_t lsebyp   : 1;
            uint32_t          : 5;
            uint32_t rtcsel   : 2;
            uint32_t          : 5;
            uint32_t rtcen    : 1;
            uint32_t bdrst    : 1;
            uint32_t          : 15;
        } bit;
    };

    /**
     * @brief Control/status register (RCC_CSR).
     */
    union Csr
    {
        Csr(){}
        Csr(uint32_t v){value = v;}
       ~Csr(){}    
      
        uint32_t value;
        struct 
        {
            uint32_t lsion    : 1;
            uint32_t lsirdy   : 1;
            uint32_t          : 22;
            uint32_t rmvf     : 1;
            uint32_t          : 1;
            uint32_t pinrstf  : 1;
            uint32_t porrstf  : 1;
            uint32_t sftrstf  : 1;
            uint32_t iwdgrstf : 1;
            uint32_t wwdgrstf : 1;
            uint32_t lpwrstf  : 1;
        } bit;
    };
    
    /**
     * @brief Clock Configuration Register 2 (RCC_CFGR2).
     */
    union Cfgr2
    {
        Cfgr2(){}
        Cfgr2(uint32_t v){value = v;}
       ~Cfgr2(){}    
      
        uint32_t value;
        struct 
        {
            uint32_t prediv : 4;
            uint32_t        : 28;
        } bit;
    };    
    
    /**
     * @brief Clock Configuration Register 3 (RCC_CFGR3).
     */
    union Cfgr3
    {
        Cfgr3(){}
        Cfgr3(uint32_t v){value = v;}
       ~Cfgr3(){}    
      
        uint32_t value;
        struct 
        {
            uint32_t          : 8;
            uint32_t usbsw    : 3;
            uint32_t usbclken : 1;
            uint32_t usbifsw  : 2;
            uint32_t          : 6;
            uint32_t adc1sw   : 3;
            uint32_t adc2sw   : 3;
            uint32_t adc3sw   : 3;
            uint32_t          : 3;
        } bit;
    };

    /**
     * @brief Clock Control Register 2 (RCC_CR2).
     */
    union Cr2
    {
        Cr2(){}
        Cr2(uint32_t v){value = v;}
       ~Cr2(){}    
      
        uint32_t value;
        struct 
        {
            uint32_t          : 16;
            uint32_t hsi56on  : 1;
            uint32_t hsi56rdy : 1;
            uint32_t hsi28on  : 1;
            uint32_t hsi28rdy : 1;
            uint32_t          : 12;
        } bit;
    };

    /**
     * @brief HSE control register (RCC_HSECTL).
     */
    union Hsectl
    {
        Hsectl(){}
        Hsectl(uint32_t v){value = v;}
       ~Hsectl(){}    
      
        uint32_t value;
        struct 
        {
            uint32_t hsewt        : 12;
            uint32_t hsestopkeep  : 1;
            uint32_t              : 3;
            uint32_t xtal32m      : 8;
            uint32_t hsenfbyp     : 1;
            uint32_t cssthreshold : 7;
        } bit;
    };

    /**
     * @brief PLL Control Register (RCC_PLLCTL).
     */
    union Pllctl
    {
        Pllctl(){}
        Pllctl(uint32_t v){value = v;}
       ~Pllctl(){}    
      
        uint32_t value;
        struct 
        {
            uint32_t       : 25;
            uint32_t pllwt : 5;
            uint32_t       : 2;
        } bit;
    };

    /**
     * @brief Clock Configuration Register 4 (RCC_CFGR4).
     */
    union Cfgr4
    {
        Cfgr4(){}
        Cfgr4(uint32_t v){value = v;}
       ~Cfgr4(){}    
      
        uint32_t value;
        struct 
        {
            uint32_t pllmulh : 3;
            uint32_t         : 1;
            uint32_t ppss    : 1;
            uint32_t         : 27;
        } bit;
    };

    /**
     * @brief Clock Configuration Register 5 (RCC_CFGR5).
     */
    union Cfgr5
    {
        Cfgr5(){}
        Cfgr5(uint32_t v){value = v;}
       ~Cfgr5(){}    
      
        uint32_t value;
        struct 
        {
            uint32_t esw         : 3;
            uint32_t             : 1;
            uint32_t esws        : 3;
            uint32_t             : 1;
            uint32_t extclksel   : 2;
            uint32_t             : 1;
            uint32_t esss        : 1;
            uint32_t flitfclksel : 2;
            uint32_t flitfclkpre : 5;
            uint32_t             : 8;
            uint32_t mco3        : 1;
            uint32_t mcopre      : 3;
            uint32_t pllnodiv    : 1;
        } bit;
    };

    /**
     * @brief Clock Configuration Register 6 (RCC_CFGR6).
     */
    union Cfgr6
    {
        Cfgr6(){}
        Cfgr6(uint32_t v){value = v;}
       ~Cfgr6(){}    
      
        uint32_t value;
        struct 
        {
            uint32_t saiapre : 3;
            uint32_t saiasw  : 2;
            uint32_t saibpre : 3;
            uint32_t saibsw  : 2;
            uint32_t         : 22;
        } bit;
    };

    /**
     * @brief AHB Peripheral Reset Register 2 (RCC_AHBRST2).
     */
    union Ahbrst2
    {
        Ahbrst2(){}
        Ahbrst2(uint32_t v){value = v;}
       ~Ahbrst2(){}    
      
        uint32_t value;
        struct 
        {
            uint32_t dma1rst : 1;
            uint32_t dma2rst : 1;
            uint32_t         : 4;
            uint32_t crcrst  : 1;
            uint32_t         : 1;
            uint32_t fsmcrst : 1;
            uint32_t         : 1;
            uint32_t sdiorst : 1;
            uint32_t         : 21;
        } bit;
    };

    /**
     * @brief AHB Peripheral Reset Register 3 (RCC_AHBRST3).
     */
    union Ahbrst3
    {
        Ahbrst3(){}
        Ahbrst3(uint32_t v){value = v;}
       ~Ahbrst3(){}    
      
        uint32_t value;
        struct 
        {    
            uint32_t          : 8;
            uint32_t cacherst : 1;
            uint32_t          : 23;
        } bit;
    };

    /**
     * @brief LSI Clock Control Register (RCC_LSICTL).
     */
    union Lsictl
    {
        Lsictl(){}
        Lsictl(uint32_t v){value = v;}
       ~Lsictl(){}    
      
        uint32_t value;
        struct 
        {
            uint32_t         : 2;
            uint32_t lsifreq : 2;
            uint32_t         : 4;
            uint32_t lsitrim : 8;
            uint32_t         : 16;
        } bit;
    };

    /**
     * @brief Register map.
     */
public:     
    Cr        cr;           // 0x40021000
    Cfgr      cfgr;         // 0x40021004
    Cir       cir;          // 0x40021008
    Apb2rstr  apb2rstr;     // 0x4002100C
    Apb1rstr  apb1rstr;     // 0x40021010
    Ahbenr    ahbenr;       // 0x40021014
    Apb2enr   apb2enr;      // 0x40021018
    Apb1enr   apb1enr;      // 0x4002101C
    Bdcr      bdcr;         // 0x40021020
    Csr       csr;          // 0x40021024
private:
    uint32_t  space0_[0x01];
public:
    Cfgr2     cfgr2;        // 0x4002102C
    Cfgr3     cfgr3;        // 0x40021030
    Cr2       cr2;          // 0x40021034
private:
    uint32_t  space1_[0x2A];
public:       
    Hsectl    hsectl;       // 0x400210E0
    Pllctl    pllctl;       // 0x400210E4
    Cfgr4     cfgr4;        // 0x400210E8
    Cfgr5     cfgr5;        // 0x400210EC
    Cfgr6     cfgr6;        // 0x400210F0
private:
    uint32_t  space2_[0x06];
public:                            
    Ahbrst2   ahbrst2;      // 0x4002110C
    Ahbrst3   ahbrst3;      // 0x40021110
private:
    uint32_t  space3_[0x02];
public:    
    Lsictl    lsictl;       // 0x4002111C
};

} // namespace reg
} // namespace cpu
} // namespace eoos
#endif // CPU_REG_RCC_HPP_
