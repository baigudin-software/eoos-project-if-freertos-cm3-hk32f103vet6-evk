/**
 * @file      cpu.PllController.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2017-2023, Sergey Baigudin, Baigudin Software
 */ 
#include "cpu.PllController.hpp"

namespace eoos
{
namespace cpu
{
    
PllController::PllController(Registers& reg, api::Guard& gie)
    : NonCopyable<NoAllocator>()
    , api::CpuPllController()
    , reg_(reg)     
    , gie_(gie) {    
    bool_t const isConstructed( construct() );
    setConstructed( isConstructed );
}

PllController::~PllController()
{
}

bool_t PllController::isConstructed() const
{
    return Parent::isConstructed();
}

int64_t PllController::getSourceClock()
{
    return 8000000;
}
 
int64_t PllController::getCpuClock()
{
    return 72000000;
}

bool_t PllController::construct()
{
    bool_t res( false );
    do 
    {
        if( !isConstructed() )
        {
            break;
        }
        if( !initialize() )
        {
            break;
        }
        res = true;
    } while(false);
    return res;
}

bool_t PllController::initialize()
{
    {
        reg::Rcc::Cr cr(reg_.rcc->cr.value);
        cr.bit.hsion = 1;       // Set Internal high-speed clock (HSI) to 56 MHz / 7 = 8 MHz
        reg_.rcc->cr.value = cr.value;
    }
    {
        reg::Rcc::Cfgr cfgr(reg_.rcc->cfgr.value);
        cfgr.bit.sw = 0;        // Reset System clock Switch to HSI selected as system clock
        cfgr.bit.hpre = 0;      // Reset AHB prescaler to SYSCLK not divided
        cfgr.bit.ppre1 = 0;     // Reset APB Low-speed prescaler (APB1) to HCLK not divided
        cfgr.bit.ppre2 = 0;     // Reset APB high-speed prescaler (APB2) to HCLK not divided
        cfgr.bit.adcpre = 0;    // Reset ADC prescaler to PCLK2 divided by 2
        cfgr.bit.mco = 4;       // Reset Microcontroller clock output (MCO) to SYSCLK output
        reg_.rcc->cfgr.value = cfgr.value;
    }
    {
        reg::Rcc::Cfgr5 cfgr5(reg_.rcc->cfgr5.value);
        cfgr5.bit.esss = 0;     // Reset System clock switching supplementary to CFGR path
        cfgr5.bit.mco3 = 0;     // Reset Microcontroller clock output bit 3 (MCO) to SYSCLK output
        reg_.rcc->cfgr5.value = cfgr5.value;
    }    
    {
        reg::Rcc::Cr cr(reg_.rcc->cr.value);
        cr.bit.hseon = 0;       // Reset HSE clock enable to HSE oscillator OFF
        cr.bit.csson = 0;       // Reset Clock security system enable to Clock detector OFF
        cr.bit.pllon = 0;       // Reset PLL enable to PLL OFF
        reg_.rcc->cr.value = cr.value;
    }    
    {
        reg::Rcc::Cr cr(reg_.rcc->cr.value);
        cr.bit.hsebyp = 0;      // Reset External high-speed clock bypass to not bypassed
        reg_.rcc->cr.value = cr.value;
    }    
    {
        reg::Rcc::Cfgr cfgr(reg_.rcc->cfgr.value);
        cfgr.bit.pllsrc = 0;    // Reset PLL input clock source to HSI/2 clock as PLL input clock
        cfgr.bit.pllxtpre = 0;  // Reset HSE divider for PLL input clock
        cfgr.bit.pllmul = 0;    // Reset PLL multiplication factor to PLL 2-fold output
        cfgr.bit.usbpre = 0;    // Reset USB prescaler to PLL clock 1.5 times divided as USB clock (PLL output is 72 MHz)
        reg_.rcc->cfgr.value = cfgr.value;
    }
    {
        reg::Rcc::Cfgr3 cfgr3(reg_.rcc->cfgr3.value);
        cfgr3.bit.usbsw = 0;    // Reset USB clock frequency to determined by RCC_CFGR.USBPRE configuration
        reg_.rcc->cfgr3.value = cfgr3.value;
    }
    {
        reg::Rcc::Cfgr4 cfgr4(reg_.rcc->cfgr4.value);
        cfgr4.bit.pllmulh = 0;  // Reset PLL pre-scaler clock source selection to HSE clock input to PLL prescaler
        cfgr4.bit.ppss = 0;     // Set PLL pre-scaler clock source selection to HSE clock input to PLL prescaler
        reg_.rcc->cfgr4.value = cfgr4.value;
    }
    {
        reg::Rcc::Cir cir(0);
        cir.bit.lsirdyc = 1;    // Clear LSI flag
        cir.bit.lserdyc = 1;    // Clear LSE flag
        cir.bit.hsirdyc = 1;    // Clear HSI flag
        cir.bit.hserdyc = 1;    // Clear HSE flag
        cir.bit.pllrdyc = 1;    // Clear PLL flag
        cir.bit.cssc = 1;       // Clear CSS flag
        cir.bit.lsirdyie = 0;   // Disable LSI interrupt source
        cir.bit.lserdyie = 0;   // Disable LSE interrupt source
        cir.bit.hsirdyie = 0;   // Disable HSI interrupt source
        cir.bit.hserdyie = 0;   // Disable HSE interrupt source
        cir.bit.pllrdyie = 0;   // Disable PLL interrupt source
        reg_.rcc->cir.value = cir.value;
    }
    return setSysClkTo72();
}

bool_t PllController::setSysClkTo72()
{
    if( 8000000 != getSourceClock() )
    {
        return false;
    }    
    if( 72000000 != getCpuClock() )
    {
        return false;
    }

    bool_t res( false );
    bool_t isHserdy( false );
    reg_.rcc->cr.bit.hseon = 1; // Set HSE clock enable to HSE oscillator ON
    for(int32_t i=0; i<REG_RCC_HSERDY_TIMEOUT; i++)
    {
        if(reg_.rcc->cr.bit.hserdy == 1)
        {
            isHserdy = true;
            break;
        }
    }
    if( isHserdy )
    {
        {
            reg_.flash->acr.bit.prftbe = 1;           // Set Prefetch buffer status to Prefetch buffer is enabled
            reg_.flash->acr.bit.latency = 0;          // Reset Flash Latency
            reg_.flash->latencyex.bit.latency43 = 0;  // Reset Flash Latency
            reg_.flash->acr.bit.latency = 2;          // Set Flash Latency to 00010 wait period for 48 MHz < HCLK <= 72 MHz
        }
        {
            reg::Rcc::Cfgr4 cfgr4(reg_.rcc->cfgr4.value);
            cfgr4.bit.pllmulh = 0;  // Set PLL pre-scaler clock source selection to HSE clock input to PLL prescaler
            cfgr4.bit.ppss = 0;     // Set PLL pre-scaler clock source selection to HSE clock input to PLL prescaler
            reg_.rcc->cfgr4.value = cfgr4.value;
        }
        {
            reg::Rcc::Cfgr cfgr(reg_.rcc->cfgr.value);
            cfgr.bit.hpre = 0;      // Set AHB prescaler to SYSCLK not divided
            cfgr.bit.ppre1 = 1;     // Set APB Low-speed prescaler (APB1) to HCLK divided 2
            cfgr.bit.ppre2 = 0;     // Reset APB high-speed prescaler (APB2) to HCLK not divided
            cfgr.bit.pllsrc = 1;    // Reset PLL input clock source to HSE clock as PLL input clock
            cfgr.bit.pllxtpre = 0;  // Reset HSE divider for PLL input clock
            cfgr.bit.pllmul = 7;    // Reset PLL multiplication factor to PLL 9x output
            reg_.rcc->cfgr.value = cfgr.value;
        }
        {
            reg::Rcc::Cr cr(reg_.rcc->cr.value);
            cr.bit.pllon = 1;       // Reset PLL enable to PLL ON
            reg_.rcc->cr.value = cr.value;
            // Wait till PLL is ready
            while(true)
            {   
                if(reg_.rcc->cr.bit.pllrdy == 1)
                {
                    break;
                }
            }
        }    
        {
            reg::Rcc::Cfgr cfgr(reg_.rcc->cfgr.value);
            cfgr.bit.sw = 2;        // Reset System clock Switch to PLL output as system clock
            reg_.rcc->cfgr.value = cfgr.value;
            // Wait till PLL is used as system clock source
            while(true)
            {
                if(reg_.rcc->cfgr.bit.sws == 2)
                {
                    break;
                }
            }        
        }
        res = true;
    }
    return res;
}
    
} // namespace cpu
} // namespace eoos
