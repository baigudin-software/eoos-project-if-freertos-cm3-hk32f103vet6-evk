/**
 * @file      cpu.reg.Scb.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2023, Sergey Baigudin, Baigudin Software
 */
#ifndef CPU_REG_SCB_HPP_
#define CPU_REG_SCB_HPP_

#include "Types.hpp"

namespace eoos
{
namespace cpu
{
namespace reg
{

/**
 * @struct Scb
 * @brief System Control Block.
 */
struct Scb
{

public:
  
    /**
     * @brief System Control address.
     */    
    static const uint32_t ADDRESS = 0xE000ED00;
        
    /** 
     * @brief Constructor.
     */  
    Scb()
        : cpuid()      
        , icsr()       
        , vtor()       
        , aircr()      
        , scr()        
        , ccr()        
        , shcsr()      
        , cfsr()       
        , hfsr()       
        , dfsr()       
        , mmfar()      
        , bfar()       
        , afsr()       
        , idpfr0()     
        , idpfr1()     
        , iddfr0()     
        , idafr0()     
        , idmmfr0()    
        , idmmfr1()    
        , idmmfr2()    
        , idmmfr3()    
        , idisar0()    
        , idisar1()    
        , idisar2()    
        , idisar3()    
        , idisar4()    
        , cpacr() {
    }

    /** 
     * @brief Destructor.
     */  
    ~Scb(){}
   
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
     * @brief CPUID Base Register.
     */
    union Cpuid
    {
        Cpuid(){}
        Cpuid(uint32_t v){value = v;}
       ~Cpuid(){}    
      
        uint32_t value;
        struct 
        {
            uint32_t revision    : 4;
            uint32_t partno      : 12;
            uint32_t             : 4;
            uint32_t variant     : 4;
            uint32_t implementer : 8;
        } bit;
    };

    /**
     * @brief Interrupt Control and State Register.
     */
    union Icsr
    {
        Icsr(){}
        Icsr(uint32_t v){value = v;}
       ~Icsr(){}    
      
        uint32_t value;
        struct 
        {
            uint32_t vectactive  : 9;
            uint32_t             : 2;
            uint32_t rettobase   : 1;
            uint32_t vectpending : 9;
            uint32_t             : 1;
            uint32_t isrpending  : 1;
            uint32_t isrpreempt  : 1;
            uint32_t             : 1;
            uint32_t pendstclr   : 1;
            uint32_t pendstset   : 1;
            uint32_t pendsvclr   : 1;
            uint32_t pendsvset   : 1;
            uint32_t             : 2;
            uint32_t nmipendset  : 1;
        } bit;
    };

    /**
     * @brief Vector Table Offset Register.
     */
    union Vtor
    {
        Vtor(){}
        Vtor(uint32_t v){value = v;}
       ~Vtor(){}    
      
        uint32_t value;
        struct 
        {
            uint32_t        : 7;
            uint32_t tbloff : 25;
        } bit;
    };

    /**
     * @brief Application Interrupt and Reset Control Register.
     */
    union Aircr
    {
        Aircr(){}
        Aircr(uint32_t v){value = v;}
       ~Aircr(){}    
      
        uint32_t value;
        struct 
        {
            uint32_t vectreset     : 1; 
            uint32_t vectclractive : 1; 
            uint32_t sysresetreq   : 1; 
            uint32_t               : 5;
            uint32_t prigroup      : 3; 
            uint32_t               : 4;
            uint32_t endianess     : 1; 
            uint32_t vectkey       : 16;
        } bit;
    };

    /**
     * @brief System Control Register.
     */
    union Scr
    {
        Scr(){}
        Scr(uint32_t v){value = v;}
       ~Scr(){}    
      
        uint32_t value;
        struct 
        {
            uint32_t             : 1;
            uint32_t sleeponexit : 1;
            uint32_t sleepdeep   : 1;
            uint32_t             : 1;
            uint32_t sevonpend   : 1;
            uint32_t             : 27;
        } bit;
    };

    /**
     * @brief Configuration and Control Register.
     */
    union Ccr
    {
        Ccr(){}
        Ccr(uint32_t v){value = v;}
       ~Ccr(){}    
      
        uint32_t value;
        struct 
        {
            uint32_t nonbasethrdena : 1;
            uint32_t usersetmpend   : 1;
            uint32_t                : 1;
            uint32_t unalign_trp    : 1;
            uint32_t div0trp        : 1;
            uint32_t                : 3;
            uint32_t bfhfnmign      : 1;
            uint32_t stkalign       : 1;
            uint32_t                : 6;
            uint32_t dc             : 1;
            uint32_t ic             : 1;
            uint32_t bp             : 1;
            uint32_t                : 13;            
        } bit;
    };

    /**
     * @brief System Handler Priority Register 1-3.
     */
    union ShprN
    {
        ShprN(){}
        ShprN(uint32_t v){value = v;}
       ~ShprN(){}    
      
        uint32_t value;
        struct 
        {                       // | Register 1  | Register 2  | Register 3     |
            uint32_t priN0 : 8; // | MPU Fault   |             | Debug Monitor  |
            uint32_t priN1 : 8; // | Bus Fault   |             |                |
            uint32_t priN2 : 8; // | Usage Fault |             | PendSV         |
            uint32_t priN3 : 8; // |             | SVCall      | SysTick        |
        } bit;
    };

    /**
     * @brief System Handler Control and State Register.
     */
    union Shcsr
    {
        Shcsr(){}
        Shcsr(uint32_t v){value = v;}
       ~Shcsr(){}    
      
        uint32_t value;
        struct 
        {
            uint32_t memfaultact    : 1;
            uint32_t busfaultact    : 1;
            uint32_t                : 1;
            uint32_t usgfaultact    : 1;
            uint32_t                : 3;
            uint32_t svcallact      : 1;
            uint32_t monitoract     : 1;
            uint32_t                : 1;
            uint32_t pendsvact      : 1;
            uint32_t systickact     : 1;
            uint32_t usgfaultpended : 1;
            uint32_t memfaultpended : 1;
            uint32_t busfaultpended : 1;
            uint32_t svcallpended   : 1;
            uint32_t memfaultena    : 1;
            uint32_t busfaultena    : 1;
            uint32_t usgfaultena    : 1;
            uint32_t                : 13;
        } bit;
    };

    /**
     * @brief Configurable Fault Status Registers.
     */
    union Cfsr
    {
        Cfsr(){}
        Cfsr(uint32_t v){value = v;}
       ~Cfsr(){}    
      
        uint32_t value;
        struct 
        {
            uint32_t mmfsrIaccviol   : 1;
            uint32_t mmfsrDaccviol   : 1;
            uint32_t                 : 1;
            uint32_t mmfsrMunstkerr  : 1;
            uint32_t mmfsrMstkerr    : 1;
            uint32_t mmfsrMlsperr    : 1;
            uint32_t                 : 1;
            uint32_t mmfsrMmarvalid  : 1;
            uint32_t bfsrIbuserr     : 1;
            uint32_t bfsrPreciserr   : 1;
            uint32_t bfsrImpreciserr : 1;
            uint32_t bfsrUnstkerr    : 1;
            uint32_t bfsrStkerr      : 1;
            uint32_t bfsrLsperr      : 1;
            uint32_t                 : 1;
            uint32_t bfsrBfarvalid   : 1;
            uint32_t ufsrUndefinstr  : 1;
            uint32_t ufsrInvstate    : 1;
            uint32_t ufsrInvpc       : 1;
            uint32_t ufsrNocp        : 1;
            uint32_t                 : 4;
            uint32_t ufsrUnaligned   : 1;
            uint32_t ufsrDivbyzero   : 1;
            uint32_t                 : 6;
        } bit;
    };

    /**
     * @brief HardFault Status Register.
     */
    union Hfsr
    {
        Hfsr(){}
        Hfsr(uint32_t v){value = v;}
       ~Hfsr(){}    
      
        uint32_t value;
        struct 
        {
            uint32_t          : 1;
            uint32_t vecttbl  : 1;
            uint32_t          : 28;
            uint32_t forced   : 1;
            uint32_t debugevt : 1;
        } bit;
    };

    /**
     * @brief Debug Fault Status Register.
     */
    union Dfsr
    {
        Dfsr(){}
        Dfsr(uint32_t v){value = v;}
       ~Dfsr(){}    
      
        uint32_t value;
        struct 
        {
            uint32_t halted   : 1;
            uint32_t bkpt     : 1;
            uint32_t dwttrap  : 1;
            uint32_t vcatch   : 1;
            uint32_t external : 1;
            uint32_t          : 27;
        } bit;
    };

    /**
     * @brief MemManage Address Register.
     */
    union Mmfar
    {
        Mmfar(){}
        Mmfar(uint32_t v){value = v;}
       ~Mmfar(){}    
      
        uint32_t value;
        struct 
        {
            uint32_t address : 32;
        } bit;
    };

    /**
     * @brief BusFault Address Register.
     */
    union Bfar
    {
        Bfar(){}
        Bfar(uint32_t v){value = v;}
       ~Bfar(){}    
      
        uint32_t value;
        struct 
        {
            uint32_t address : 32;
        } bit;
    };

    /**
     * @brief Auxiliary Fault Status Register.
     */
    union Afsr
    {
        Afsr(){}
        Afsr(uint32_t v){value = v;}
       ~Afsr(){}    
      
        uint32_t value;
        struct 
        {
            uint32_t auxfault : 32;
        } bit;
    };

    /**
     * @brief Processor Feature Register 0.
     */
    union IdPfr0
    {
        IdPfr0(){}
        IdPfr0(uint32_t v){value = v;}
       ~IdPfr0(){}    
      
        uint32_t value;
    };

    /**
     * @brief Processor Feature Register 1.
     */
    union IdPfr1
    {
        IdPfr1(){}
        IdPfr1(uint32_t v){value = v;}
       ~IdPfr1(){}    
      
        uint32_t value;
    };

    /**
     * @brief Debug Features Register 0.
     */
    union IdDfr0
    {
        IdDfr0(){}
        IdDfr0(uint32_t v){value = v;}
       ~IdDfr0(){}    
      
        uint32_t value;
    };

    /**
     * @brief Auxiliary Features Register 0.
     */
    union IdAfr0
    {
        IdAfr0(){}
        IdAfr0(uint32_t v){value = v;}
       ~IdAfr0(){}    
      
        uint32_t value;
    };

    /**
     * @brief Memory Model Feature Register 0.
     */
    union IdMmfr0
    {
        IdMmfr0(){}
        IdMmfr0(uint32_t v){value = v;}
       ~IdMmfr0(){}    
      
        uint32_t value;
    };

    /**
     * @brief Memory Model Feature Register 1.
     */
    union IdMmfr1
    {
        IdMmfr1(){}
        IdMmfr1(uint32_t v){value = v;}
       ~IdMmfr1(){}    
      
        uint32_t value;
    };

    /**
     * @brief Memory Model Feature Register 2.
     */
    union IdMmfr2
    {
        IdMmfr2(){}
        IdMmfr2(uint32_t v){value = v;}
       ~IdMmfr2(){}    
      
        uint32_t value;
    };

    /**
     * @brief Memory Model Feature Register 3.
     */
    union IdMmfr3
    {
        IdMmfr3(){}
        IdMmfr3(uint32_t v){value = v;}
       ~IdMmfr3(){}    
      
        uint32_t value;
    };

    /**
     * @brief Instruction Set Attributes Register 0.
     */
    union IdIsar0
    {
        IdIsar0(){}
        IdIsar0(uint32_t v){value = v;}
       ~IdIsar0(){}    
      
        uint32_t value;
    };

    /**
     * @brief Instruction Set Attributes Register 1.
     */
    union IdIsar1
    {
        IdIsar1(){}
        IdIsar1(uint32_t v){value = v;}
       ~IdIsar1(){}    
      
        uint32_t value;
    };

    /**
     * @brief Instruction Set Attributes Register 2.
     */
    union IdIsar2
    {
        IdIsar2(){}
        IdIsar2(uint32_t v){value = v;}
       ~IdIsar2(){}    
      
        uint32_t value;
    };

    /**
     * @brief Instruction Set Attributes Register 3.
     */
    union IdIsar3
    {
        IdIsar3(){}
        IdIsar3(uint32_t v){value = v;}
       ~IdIsar3(){}    
      
        uint32_t value;
    };

    /**
     * @brief Instruction Set Attributes Register 4.
     */
    union IdIsar4
    {
        IdIsar4(){}
        IdIsar4(uint32_t v){value = v;}
       ~IdIsar4(){}    
      
        uint32_t value;
    };

    /**
     * @brief Coprocessor Access Control Register.
     */
    union Cpacr
    {
        Cpacr(){}
        Cpacr(uint32_t v){value = v;}
       ~Cpacr(){}    
      
        uint32_t value;
    };
    
    /**
     * @brief Register map.
     */
public:
    Cpuid       cpuid;   // 0xE000ED00
    Icsr        icsr;    // 0xE000ED04
    Vtor        vtor;    // 0xE000ED08
    Aircr       aircr;   // 0xE000ED0C
    Scr         scr;     // 0xE000ED10
    Ccr         ccr;     // 0xE000ED14
    ShprN       shpr[3]; // 0xE000ED18 - 0xE000ED20
    Shcsr       shcsr;   // 0xE000ED24
    Cfsr        cfsr;    // 0xE000ED28
    Hfsr        hfsr;    // 0xE000ED2C
    Dfsr        dfsr;    // 0xE000ED30
    Mmfar       mmfar;   // 0xE000ED34
    Bfar        bfar;    // 0xE000ED38
    Afsr        afsr;    // 0xE000ED3C
    IdPfr0      idpfr0;  // 0xE000ED40
    IdPfr1      idpfr1;  // 0xE000ED44
    IdDfr0      iddfr0;  // 0xE000ED48
    IdAfr0      idafr0;  // 0xE000ED4C
    IdMmfr0     idmmfr0; // 0xE000ED50
    IdMmfr1     idmmfr1; // 0xE000ED54
    IdMmfr2     idmmfr2; // 0xE000ED58
    IdMmfr3     idmmfr3; // 0xE000ED5C
    IdIsar0     idisar0; // 0xE000ED60
    IdIsar1     idisar1; // 0xE000ED64
    IdIsar2     idisar2; // 0xE000ED68
    IdIsar3     idisar3; // 0xE000ED6C
    IdIsar4     idisar4; // 0xE000ED70
private:
    uint32_t    space2_[0x5D];
public:
    Cpacr       cpacr;   // 0xED88

};

} // namespace reg
} // namespace cpu
} // namespace eoos
#endif // CPU_REG_SCB_HPP_
