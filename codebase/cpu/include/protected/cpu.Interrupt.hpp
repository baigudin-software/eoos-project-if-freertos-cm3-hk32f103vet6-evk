/**
 * @file      cpu.Interrupt.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2014-2023, Sergey Baigudin, Baigudin Software
 */
#ifndef CPU_INTERRUPT_HPP_
#define CPU_INTERRUPT_HPP_

#include "cpu.NonCopyable.hpp"
#include "api.CpuInterrupt.hpp"
#include "api.Task.hpp"
#include "api.Guard.hpp"
#include "cpu.Registers.hpp"
#include "lib.Guard.hpp"

namespace eoos
{
namespace cpu
{

/**
 * @class Interrupt
 * @brief CPU HW interrupt resource.
 * 
 * @tparam A Heap memory allocator class.
 */
template <class A>
class Interrupt : public NonCopyable<A>, public api::CpuInterrupt
{
    typedef NonCopyable<A> Parent;

public:

    /**
     * @enum Exception
     * @brief Exception numbers.
     */
    enum Exception
    {
        // Cortex-M3 exceptions
        EXCEPTION_NMI = 2, 
        EXCEPTION_HARDFAULT,
        EXCEPTION_MEMMANAGE,
        EXCEPTION_BUSFAULT,
        EXCEPTION_USAGEFAULT,
        EXCEPTION_SVCALL = 11,           
        EXCEPTION_DEBUGMON,
        EXCEPTION_PENDSV = 14,     
        EXCEPTION_SYSTICK,
        // HK32F103xCxDxE interrupts
        EXCEPTION_WWDG,
        EXCEPTION_PVD,          
        EXCEPTION_TAMPER,         
        EXCEPTION_RTC,        
        EXCEPTION_FLASH,          
        EXCEPTION_RCC,         
        EXCEPTION_EXTI0,          
        EXCEPTION_EXTI1,          
        EXCEPTION_EXTI2,          
        EXCEPTION_EXTI3,          
        EXCEPTION_EXTI4,          
        EXCEPTION_DMA1_CHANNEL1,
        EXCEPTION_DMA1_CHANNEL2,
        EXCEPTION_DMA1_CHANNEL3,
        EXCEPTION_DMA1_CHANNEL4,
        EXCEPTION_DMA1_CHANNEL5,
        EXCEPTION_DMA1_CHANNEL6,
        EXCEPTION_DMA1_CHANNEL7,
        EXCEPTION_ADC1_2,  
        EXCEPTION_USB_HP_CAN_TX,
        EXCEPTION_USB_LP_CAN_RX0, 
        EXCEPTION_CAN_RX1,
        EXCEPTION_CAN_SCE,       
        EXCEPTION_EXTI9_5,       
        EXCEPTION_TIM1_BRK,       
        EXCEPTION_TIM1_UP,      
        EXCEPTION_TIM1_TRG_COM,
        EXCEPTION_TIM1_CC,        
        EXCEPTION_TIM2,         
        EXCEPTION_TIM3,     
        EXCEPTION_TIM4,           
        EXCEPTION_I2C1_EV,        
        EXCEPTION_I2C1_ER,        
        EXCEPTION_I2C2_EV,        
        EXCEPTION_I2C2_ER,        
        EXCEPTION_SPI1,           
        EXCEPTION_SPI2,           
        EXCEPTION_USART1,
        EXCEPTION_USART2,         
        EXCEPTION_USART3,         
        EXCEPTION_EXTI15_10,      
        EXCEPTION_RTCALARM,      
        EXCEPTION_USBWAKEUP,      
        EXCEPTION_TIM8_BRK,       
        EXCEPTION_TIM8_UP,        
        EXCEPTION_TIM8_TRG_COM,   
        EXCEPTION_TIM8_CC,        
        EXCEPTION_ADC3,           
        EXCEPTION_FSMC,           
        EXCEPTION_SDIO,           
        EXCEPTION_TIM5,           
        EXCEPTION_SPI3,           
        EXCEPTION_UART4,          
        EXCEPTION_UART5,          
        EXCEPTION_TIM6,           
        EXCEPTION_TIM7,           
        EXCEPTION_DMA2_CHANNEL1,  
        EXCEPTION_DMA2_CHANNEL2,  
        EXCEPTION_DMA2_CHANNEL3,  
        EXCEPTION_DMA2_CHANNEL4_5,
        EXCEPTION_LAST
    };
    
    /**
     * @struct Data
     * @brief Global data for all these objects;
     */
    struct Data
    {
        /**
         * @brief Constructor.
         *
         * @param reg Target CPU register model.     
         * @param gie Global interrupt enable controller.     
         */
        Data(Registers& areg, api::Guard& agie);
        
        /**
         * @brief Target CPU register model.
         */
        Registers& reg;

        /**
         * @brief Global interrupt enable controller.
         */
        api::Guard& gie;
        
        /**
         * @brief Interrupt handlers.
         */        
        api::Task* handlers[EXCEPTION_LAST];
    };

    /**
     * @brief Constructor.
     *
     * @param data Global data for all theses objects
     * @param handler User class which implements an interrupt handler interface.
     * @param exception Exception number.
     */
    Interrupt(Data& data, api::Task& handler, int32_t exception);
    
    /** 
     * @brief Destructor.
     */                               
    virtual ~Interrupt();
    
    /**
     * @copydoc eoos::api::Object::isConstructed()
     */
    virtual bool_t isConstructed() const;    

    /**
     * @copydoc eoos::api::CpuInterrupt::disable()
     */
    virtual void disable();

    /**
     * @copydoc eoos::api::CpuInterrupt::enable()
     */
    virtual void enable();
    
    /**
     * @brief Test if exception number is valid.
     *
     * @param exception Exception number.
     * @return True is is valid.
     */
    static bool_t isException(int32_t exception);

protected:

    using Parent::setConstructed;
    
private:

    /**
     * @brief Constructs this object.
     *
     * @return true if object has been constructed successfully.
     */
    bool_t construct();

    /**
     * @brief Destructs this object.
     */
    void destruct();
    
    /**
     * @brief Disables IRQ exception.
     */
    void disableIrq();

    /**
     * @brief Enables IRQ exception.
     */
    void enableIrq();
    
    /**
     * @brief Sets exception handler.
     *
     * @param handler A user class interface that implements an interrupt handler interface.
     * @param exception An exception number.
     * @return True if handler is set successfully.
     */      
    bool_t setHandler(api::Task& handler, int32_t exception);    
    
    /**
     * @brief First IRQ exception.
     */    
    static const int32_t EXCEPTION_FIRST_IRQ = 16;
    
    /**
     * @brief User class which implements an interrupt handler interface.
     */
    api::Task& handler_;    

    /**
     * @brief This resource exception number.
     */
    int32_t exception_;

    /**
     * @brief Global data for all these objects;
     */
    Data& data_;

};

template <class A>
Interrupt<A>::Interrupt(Data& data, api::Task& handler, int32_t exception)
    : NonCopyable<A>()
    , api::CpuInterrupt()
    , handler_( handler )
    , exception_( exception )
    , data_( data ) {
    bool_t const isConstructed( construct() );
    setConstructed( isConstructed );
}    

template <class A>
Interrupt<A>::~Interrupt()
{
    destruct();
}

template <class A>
bool_t Interrupt<A>::isConstructed() const
{
    return Parent::isConstructed();
}

template <class A>
void Interrupt<A>::disable()
{
    if( isConstructed() )
    {
        switch(exception_)
        {
            case EXCEPTION_SYSTICK:
            {
                lib::Guard<A> guard(data_.gie);
                // Disable SysTick exception
                data_.reg.scs.tick->csr.bit.tickint = 0;
                break;
            }
            default:
            {
                if(EXCEPTION_FIRST_IRQ <= exception_ && exception_ < EXCEPTION_LAST)
                {
                    disableIrq();
                }
                break;
            }            
        }
    }    
}

template <class A>
void Interrupt<A>::enable()
{
    if( isConstructed() )
    {
        switch(exception_)
        {
            case EXCEPTION_SYSTICK:
            {
                lib::Guard<A> guard(data_.gie);
                // Enable SysTick exception to set count to 0 changes the SysTick exception status to pending
                data_.reg.scs.tick->csr.bit.tickint = 1;
                break;
            }
            default:
            {
                if(EXCEPTION_FIRST_IRQ <= exception_ && exception_ < EXCEPTION_LAST)
                {
                    enableIrq();
                }
                break;
            }
        }
    }
}

template <class A>
bool_t Interrupt<A>::isException(int32_t exception)
{
    if(EXCEPTION_NMI <= exception && exception < EXCEPTION_USAGEFAULT)
    {
        return true;
    }
    if(EXCEPTION_SVCALL <= exception && exception <= EXCEPTION_DEBUGMON)
    {
        return true;
    }    
    if(EXCEPTION_PENDSV <= exception && exception <= EXCEPTION_DMA2_CHANNEL4_5)
    {
        return true;
    }
    return false;
}

template <class A>
void Interrupt<A>::disableIrq()
{
    int32_t const irq = exception_ - EXCEPTION_FIRST_IRQ;
    uint32_t bitValue( 0x00000001 );
    uint32_t const bitNumber( irq % 32 );    
    for(uint32_t i(0U); i<bitNumber; i++)
    {
        bitValue <<= 1;
    }
    int32_t const index( irq / 32 );
    {
        lib::Guard<A> guard(data_.gie);
        uint32_t regValue( data_.reg.scs.nvic->icer[index].value );
        regValue |= bitValue;
        data_.reg.scs.nvic->icer[index].value = regValue;
    }    
}

template <class A>
void Interrupt<A>::enableIrq()
{
    int32_t const irq = exception_ - EXCEPTION_FIRST_IRQ;
    uint32_t bitValue( 0x00000001 );
    uint32_t const bitNumber( irq % 32 );    
    for(uint32_t i(0U); i<bitNumber; i++)
    {
        bitValue <<= 1;
    }
    int32_t const index( irq / 32 );
    {
        lib::Guard<A> guard(data_.gie);
        uint32_t regValue( data_.reg.scs.nvic->iser[index].value );
        regValue |= bitValue;
        data_.reg.scs.nvic->iser[index].value = regValue;
    }    
}

template <class A>
bool_t Interrupt<A>::construct()
{
    bool_t res( false );
    do 
    {
        if( !isConstructed() )
        {
            break;
        }
        if( !isException(exception_) )
        {
            break;
        }
        if( !setHandler(handler_, exception_) )
        {
            break;
        }
        res = true;
    } while(false);
    return res;    
}

template <class A>
void Interrupt<A>::destruct()
{
    Interrupt<A>::disable();
    lib::Guard<A> guard(data_.gie);
    data_.handlers[exception_] = NULLPTR;
}

template <class A>
bool_t Interrupt<A>::setHandler(api::Task& handler, int32_t exception)
{
    lib::Guard<A> guard(data_.gie);
    if(exception >= EXCEPTION_LAST)
    {
        return false;
    }
    if( data_.handlers[exception] != NULLPTR )
    {
        return false;
    }
    data_.handlers[exception] = &handler;
    return true;
}

template <class A>
Interrupt<A>::Data::Data(Registers& areg, api::Guard& agie)
    : reg(areg)
    , gie(agie) {
    for(int32_t i(0); i<EXCEPTION_LAST; i++)
    {
        handlers[i] = NULLPTR;
    }
    handlers[EXCEPTION_LAST] = reinterpret_cast<api::Task*>(0xFFFFFFFF);
}

} // namespace cpu
} // namespace eoos
#endif // CPU_INTERRUPT_HPP_
