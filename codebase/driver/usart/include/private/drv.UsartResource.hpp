/**
 * @file      drv.UsartResource.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2023, Sergey Baigudin, Baigudin Software
 */
#ifndef DRV_USARTRESOURCE_HPP_
#define DRV_USARTRESOURCE_HPP_

#include "api.Supervisor.hpp"
#include "lib.NonCopyable.hpp"
#include "drv.Usart.hpp"
#include "cpu.Registers.hpp"
#include "lib.NoAllocator.hpp"
#include "lib.Mutex.hpp"
#include "lib.Guard.hpp"

namespace eoos
{
namespace drv
{

/**
 * @class UsartResource
 * @brief Universal Synchronous Asynchronous Transceiver (USART) resource.
 * 
 * @tparam A Heap memory allocator class.
 */
template <class A>
class UsartResource : public lib::NonCopyable<A>, public Usart
{
    typedef lib::NonCopyable<A> Parent;

public:

    /**
     * @struct Data
     * @brief Global data for all these resources;
     */
    struct Data
    {
        /**
         * @brief Constructor.
         *
         * @param reg Target CPU register model.  
         * @param svc Supervisor call to the system.
         */
        Data(cpu::Registers& areg, api::Supervisor& asvc);
        
        /**
         * @brief Target CPU register model.
         */
        cpu::Registers& reg;

        /**
         * @brief Supervisor call to the system.
         */        
        api::Supervisor& svc;

        /**
         * @brief All the resource guard.
         */        
        lib::Mutex<lib::NoAllocator> mutex;

    };

    /**
     * @brief Constructor.
     *
     * @param data Global data for all theses objects.     
     * @param number Number of USART or UART.
     */
    UsartResource(Data& data, int32_t number);
    
    /** 
     * @brief Destructor.
     */                               
    virtual ~UsartResource();
    
    /**
     * @copydoc eoos::api::Object::isConstructed()
     */
    virtual bool_t isConstructed() const;  

    /**
     * @copydoc eoos::api::OutStream::operator<<(T const*)
     */
    virtual api::OutStream<char_t>& operator<<(char_t const* source);

    /**
     * @copydoc eoos::api::OutStream::operator<<(int32_t)
     */
    virtual api::OutStream<char_t>& operator<<(int32_t value);    

    /**
     * @copydoc eoos::api::OutStream::flush()
     */    
    virtual api::OutStream<char_t>& flush();    
        
protected:

    using Parent::setConstructed;
    
private:

    /**
     * Constructs this object.
     *
     * @return true if object has been constructed successfully.
     */
    bool_t construct();
    
    /**
     * @brief Tests if given number of USART is correct.
     *
     * @return True if correct.
     */
    bool_t isNumberValid();
    
    /**
     * @brief Initializes the hardware.
     *
     * @return True if initialized.
     */
    bool_t initialize();

    /**
     * @brief Initializes the hardware.
     */
    void deinitialize();
    
    /**
     * @brief Configures USART port (pins).
     */
    void configurePort();
    
    /**
     * @brief Enables or disables USART clock peripheral.
     *
     * @param enable True to enable and false to disable.
     */
    void enableClock(bool_t enable);    

    /**
     * @brief Enables port.
     *
     * @param enable True to enable and false to disable.
     */    
    void enablePort(bool_t enable);
    
    /**
     * @brief Sets port clocks.
     */    
    void setClock();
    
    /**
     * @brief Sets tx/rx mode.
     */    
    void setMode();
    
    /**
     * @brief Sets speed in baud.
     */    
    void setBaudSpeed();
    
    /**
     * @brief Sets number of data bits.
     */    
    void setDataBits();
    
    /**
     * @brief Sets number of stop bits.
     */    
    void setStopBits();
    
    /**
     * @brief Sets parity.
     */    
    void setParity();

    /**
     * @brief Sets flow control.
     */    
    void setFlowControl();

    /**
     * @brief Global data for all these objects;
     */
    Data& data_;
    
    /**
     * @brief Number of USART or UART.
     */
    int32_t number_;
    
    /**
     * @brief USART or UART registers.
     */
    cpu::reg::Usart* usart_;

    /**
     * @brief This resource mutex.
     */
    lib::Mutex<A> mutex_;
    
};

template <class A>
UsartResource<A>::UsartResource(Data& data, int32_t number)
    : lib::NonCopyable<A>()
    , data_( data )
    , number_( number )
    , usart_( data_.reg.usart[number_] )
    , mutex_() {
    bool_t const isConstructed( construct() );
    setConstructed( isConstructed );
}    

template <class A>
UsartResource<A>::~UsartResource()
{
    deinitialize();
}

template <class A>
bool_t UsartResource<A>::isConstructed() const
{
    return Parent::isConstructed();
}

template <class A>
api::OutStream<char_t>& UsartResource<A>::operator<<(char_t const* source)
{
    while( *source != '\0' )
    {
        lib::Guard<A> const guard(mutex_);
        volatile uint32_t txe( 0 );
        do 
        {
            txe = usart_->sr.bit.txe;
        } while( txe == 0 );
        usart_->dr.bit.dr = *source;
        source++;
    }
    return *this;
}

template <class A>
api::OutStream<char_t>& UsartResource<A>::operator<<(int32_t value)
{
    return *this;    
}

template <class A>
api::OutStream<char_t>& UsartResource<A>::flush()
{
    return *this;    
}

template <class A>
bool_t UsartResource<A>::construct()
{
    bool_t res( false );
    do 
    {
        if( !isConstructed() )
        {
            break;
        }
        if( !isNumberValid() )
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

template<class A>
bool_t UsartResource<A>::isNumberValid()
{
    return ( NUMBER_USART1 <= number_ && number_ <= NUMBER_UART5 );
}

template <class A>
bool_t UsartResource<A>::initialize()
{
    bool_t res( false );
    do 
    {
        lib::Guard<A> const guard(data_.mutex);
        // Test USART does not enable
        if( usart_->cr1.bit.ue == 1 )
        {
            break;
        }
        configurePort();
        enableClock(true);
        enablePort(false);
        setClock();
        setMode();
        setBaudSpeed();
        setDataBits();
        setStopBits();
        setParity();
        setFlowControl();
        enablePort(true);
        res = true;
    } while(false);
    return res;
}

template <class A>
void UsartResource<A>::configurePort()
{
    switch( number_ )
    {
        case NUMBER_USART1:
        {
            data_.reg.rcc->apb2enr.bit.iopaen = 1; // IO port A clock enabled          
            int32_t const index( cpu::Registers::INDEX_GPIOA );            
            cpu::reg::Gpio::Crh crh( data_.reg.gpio[index]->crh.value );
            // USART1_TX port PA9
            crh.bit.cnf9 = 2;       // Multiplexed function push-pull output mode
            crh.bit.mode9 = 2;      // Output mode, maximum speed 2 MHz
            // USART1_RX port PA10
            crh.bit.cnf10 = 1;      // 01: Floating input mode (state after reset)
            crh.bit.mode10 = 0;     // Input mode (state after reset)
            data_.reg.gpio[index]->crh.value = crh.value;
            break;
        }
        case NUMBER_USART2:
        {
            break;
        }
        case NUMBER_USART3:
        {
            break;
        }
        case NUMBER_UART4:
        {
            break;
        }
        case NUMBER_UART5:
        {
            break;
        }
        default:
        {
            break;
        }
    }
}

template <class A>
void UsartResource<A>::enableClock(bool_t enable)
{
    uint32_t en = (enable) ? 1 : 0;
    switch( number_ )
    {
        case NUMBER_USART1:
        {
            data_.reg.rcc->apb2enr.bit.usart1en = en;
            break;
        }
        case NUMBER_USART2:
        {
            data_.reg.rcc->apb1enr.bit.usart2en = en;
            break;
        }
        case NUMBER_USART3:
        {
            data_.reg.rcc->apb1enr.bit.usart3en = en;
            break;
        }
        case NUMBER_UART4:
        {
            data_.reg.rcc->apb1enr.bit.uart4en = en;
            break;
        }
        case NUMBER_UART5:
        {
            data_.reg.rcc->apb1enr.bit.uart5en = en;
            break;
        }
        default:
        {
            break;
        }
    }
}

template <class A>
void UsartResource<A>::enablePort(bool_t enable)
{
    uint32_t ue = (enable) ? 1 : 0;
    usart_->cr1.bit.ue = ue; // Set USART enable
}


template <class A>
void UsartResource<A>::setClock()
{
    usart_->cr2.bit.clken = 0; // Set Clock enable to CK pin disabled
    usart_->cr2.bit.cpol = 0;  // Set Clock polarity to held low on the CK pin when the bus is idle
    usart_->cr2.bit.cpha = 0;  // Set Clock phase to Data capture at the first edge of the clock
    usart_->cr2.bit.lbcl = 0;  // Set Last bit clock pulse Clock pulse for the last bit of data is not output from CK
}

template <class A>
void UsartResource<A>::setMode()
{
    usart_->cr1.bit.te = 1; // Set Transmitter enable
    usart_->cr1.bit.re = 1; // Set Receiver enable
}

template <class A>
void UsartResource<A>::setBaudSpeed()
{
    // Rely on the CLKs are:
    // SYSCLK    = 72 MHz
    // HCLK AHB  = 72 MHz
    // HCLK APB1 = 36 MHz
    // HCLK APB2 = 72 MHz        
    uint32_t const sysclk( static_cast<uint32_t>(data_.svc.getProcessor().getPllController().getCpuClock()) );
    if(sysclk != 72000000)
    {
        return;
    }
    // @todo Check divs to calculate the frequencies
    uint32_t pclk( (number_ == NUMBER_USART1) ? sysclk : sysclk / 2 );
    // Determine the integer part
    uint32_t baudrate( 9600 );
    uint32_t integerdivider( (25 * pclk) / (4 * baudrate) );
    uint32_t value( (integerdivider / 100) << 4 );        
    // Determine the fractional part
    uint32_t fractionaldivider( integerdivider - (100 * (value >> 4)) );        
    // Implement the fractional part in the register
    value |= (((fractionaldivider * 16) + 50) / 100) & 0x0000000F;
    // Write to BRR register
    usart_->brr.value = value;
}

template <class A>
void UsartResource<A>::setDataBits()
{
    usart_->cr1.bit.m = 0; // Set 8 bit word length
}

template <class A>
void UsartResource<A>::setStopBits()
{
    usart_->cr2.bit.stop = 0; // Set 1 stop bit    
}

template <class A>
void UsartResource<A>::setParity()
{
    usart_->cr1.bit.pce = 0; // Set Parity control enable to Disable checksum control
    usart_->cr1.bit.ps = 0;  // Set Parity selection to Even check [no action with PCE equals to 0]
}

template <class A>
void UsartResource<A>::setFlowControl()
{
    usart_->cr3.bit.rtse = 0;  // Set RTS enable to Disable RTS hardware flow control
    usart_->cr3.bit.ctse = 0;  // Set CTS enable to Disable CTS hardware flow control        
}

template <class A>
void UsartResource<A>::deinitialize()
{
    lib::Guard<A> const guard(data_.mutex);
    switch( number_ )
    {
        case NUMBER_USART1:
        {
            data_.reg.rcc->apb2rstr.bit.usart1rst = 1;
            data_.reg.rcc->apb2rstr.bit.usart1rst = 0;
            break;
        }
        case NUMBER_USART2:
        {
            data_.reg.rcc->apb1rstr.bit.usart2rst = 1;
            data_.reg.rcc->apb1rstr.bit.usart2rst = 0;
            break;
        }
        case NUMBER_USART3:
        {
            data_.reg.rcc->apb1rstr.bit.usart3rst = 1;
            data_.reg.rcc->apb1rstr.bit.usart3rst = 0;
            break;
        }
        case NUMBER_UART4:
        {
            data_.reg.rcc->apb1rstr.bit.uart4rst = 1;
            data_.reg.rcc->apb1rstr.bit.uart4rst = 0;            
            break;
        }
        case NUMBER_UART5:
        {
            data_.reg.rcc->apb1rstr.bit.uart5rst = 1;
            data_.reg.rcc->apb1rstr.bit.uart5rst = 0;            
            break;
        }
        default:
        {
            break;
        }        
    }
    enableClock(false);
}

template <class A>
UsartResource<A>::Data::Data(cpu::Registers& areg, api::Supervisor& asvc)
    : reg( areg )
    , svc( asvc )
    , mutex() {
}

} // namespace drv
} // namespace eoos
#endif // DRV_USARTRESOURCE_HPP_
