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
#include "lib.BaseString.hpp"

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
     * @param data Global data for all resource objects.     
     * @param config Configuration of USART or UART.
     */
    UsartResource(Data& data, SerialLineConfig const& config);
    
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
     * @brief Configuration of USART.
     */
    SerialLineConfig config_;    
    
    /**
     * @brief USART or UART registers.
     */
    cpu::reg::Usart* reg_;

    /**
     * @brief This resource mutex.
     */
    lib::Mutex<A> mutex_;
    
};

template <class A>
UsartResource<A>::UsartResource(Data& data, SerialLineConfig const& config)
    : lib::NonCopyable<A>()
    , data_( data )
    , config_( config )
    , reg_( data_.reg.usart[config_.number] )
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
    if( isConstructed() )
    {
        while( *source != '\0' )
        {
            lib::Guard<A> const guard(mutex_);
            volatile uint32_t txe( 0 );
            do 
            {
                txe = reg_->sr.bit.txe;
            } while( txe == 0 );
            reg_->dr.bit.dr = *source;
            source++;
        }
    }
    return *this;
}

template <class A>
api::OutStream<char_t>& UsartResource<A>::operator<<(int32_t value)
{
    lib::BaseString<char_t,16,lib::CharTrait<char_t>,A> str(value);
    return this->operator<<( str.getChar() );
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
    return ( NUMBER_USART1 <= config_.number && config_.number <= NUMBER_UART5 );
}

template <class A>
bool_t UsartResource<A>::initialize()
{
    bool_t res( false );
    do 
    {
        lib::Guard<A> const guard(data_.mutex);
        // Test USART does not enable
        if( reg_->cr1.bit.ue == 1 )
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
void UsartResource<A>::deinitialize()
{
    lib::Guard<A> const guard(data_.mutex);
    switch( config_.number )
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
void UsartResource<A>::configurePort()
{
    switch( config_.number )
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
            crh.bit.cnf10 = 1;      // Floating input mode (state after reset)
            crh.bit.mode10 = 0;     // Input mode (state after reset)
            data_.reg.gpio[index]->crh.value = crh.value;
            break;
        }
        case NUMBER_USART2:
        {
            data_.reg.rcc->apb2enr.bit.iopaen = 1; // IO port A clock enabled
            int32_t const index( cpu::Registers::INDEX_GPIOA );            
            cpu::reg::Gpio::Crl crl( data_.reg.gpio[index]->crl.value );
            // USART1_TX port PA0
            crl.bit.cnf0 = 2;       // Multiplexed function push-pull output mode
            crl.bit.mode0 = 2;      // Output mode, maximum speed 2 MHz
            // USART1_RX port PA1
            crl.bit.cnf1 = 1;       // Floating input mode (state after reset)
            crl.bit.mode1 = 0;      // Input mode (state after reset)
            data_.reg.gpio[index]->crl.value = crl.value;
            break;
        }
        case NUMBER_USART3:
        {
            data_.reg.rcc->apb2enr.bit.iopben = 1; // IO port B clock enabled
            int32_t const index( cpu::Registers::INDEX_GPIOB );            
            cpu::reg::Gpio::Crh crh( data_.reg.gpio[index]->crh.value );
            // USART1_TX port PB10
            crh.bit.cnf10 = 2;       // Multiplexed function push-pull output mode
            crh.bit.mode10 = 2;      // Output mode, maximum speed 2 MHz
            // USART1_RX port PB11
            crh.bit.cnf11 = 1;       // Floating input mode (state after reset)
            crh.bit.mode11 = 0;      // Input mode (state after reset)
            data_.reg.gpio[index]->crh.value = crh.value;            
            break;
        }
        case NUMBER_UART4:
        {
            data_.reg.rcc->apb2enr.bit.iopcen = 1; // IO port B clock enabled
            int32_t const index( cpu::Registers::INDEX_GPIOC );            
            cpu::reg::Gpio::Crh crh( data_.reg.gpio[index]->crh.value );
            // USART1_TX port PC10
            crh.bit.cnf10 = 2;       // Multiplexed function push-pull output mode
            crh.bit.mode10 = 2;      // Output mode, maximum speed 2 MHz
            // USART1_RX port PC11
            crh.bit.cnf11 = 1;       // Floating input mode (state after reset)
            crh.bit.mode11 = 0;      // Input mode (state after reset)
            data_.reg.gpio[index]->crh.value = crh.value;            
            break;
        }
        case NUMBER_UART5:
        {
            data_.reg.rcc->apb2enr.bit.iopcen = 1; // IO port B clock enabled
            int32_t index( cpu::Registers::INDEX_GPIOC );   
            cpu::reg::Gpio::Crh crh( data_.reg.gpio[index]->crh.value );
            // USART1_TX port PC12
            crh.bit.cnf12 = 2;       // Multiplexed function push-pull output mode
            crh.bit.mode12 = 2;      // Output mode, maximum speed 2 MHz
            data_.reg.gpio[index]->crh.value = crh.value;
            
            data_.reg.rcc->apb2enr.bit.iopden = 1; // IO port B clock enabled
            index = cpu::Registers::INDEX_GPIOD;
            cpu::reg::Gpio::Crl crl( data_.reg.gpio[index]->crl.value );
            // USART1_RX port PD2
            crl.bit.cnf2 = 1;       // Floating input mode (state after reset)
            crl.bit.mode2 = 0;      // Input mode (state after reset)
            data_.reg.gpio[index]->crl.value = crl.value;

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
    switch( config_.number )
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
    reg_->cr1.bit.ue = ue; // Set USART enable
}

template <class A>
void UsartResource<A>::setClock()
{
    reg_->cr2.bit.clken = 0; // Set Clock enable to CK pin disabled
    reg_->cr2.bit.cpol = 0;  // Set Clock polarity to held low on the CK pin when the bus is idle
    reg_->cr2.bit.cpha = 0;  // Set Clock phase to Data capture at the first edge of the clock
    reg_->cr2.bit.lbcl = 0;  // Set Last bit clock pulse Clock pulse for the last bit of data is not output from CK
}

template <class A>
void UsartResource<A>::setMode()
{
    switch( config_.mode )
    {
        case MODE_TX:
        {
            reg_->cr1.bit.te = 1; // Set Transmitter enable
            break;
        }
        case MODE_RX:
        {
            reg_->cr1.bit.re = 1; // Set Receiver enable            
            break;
        }
        case MODE_TXRX:
        {
            reg_->cr1.bit.te = 1; // Set Transmitter enable
            reg_->cr1.bit.re = 1; // Set Receiver enable
            break;
        }
        default:
        {
            break;
        }
    }
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
    uint32_t pclk( (config_.number == NUMBER_USART1) ? sysclk : sysclk / 2 );
    // Determine the integer part
    uint32_t baudrate( config_.baud );
    uint32_t integerdivider( (25 * pclk) / (4 * baudrate) );
    uint32_t value( (integerdivider / 100) << 4 );        
    // Determine the fractional part
    uint32_t fractionaldivider( integerdivider - (100 * (value >> 4)) );        
    // Implement the fractional part in the register
    value |= (((fractionaldivider * 16) + 50) / 100) & 0x0000000F;
    // Write to BRR register
    reg_->brr.value = value;
}

template <class A>
void UsartResource<A>::setDataBits()
{
    switch( config_.dataBits )
    {
        case DATABITS_8:
        {
            reg_->cr1.bit.m = 0; // Set 8 bit word length
            break;
        }
        case DATABITS_9:
        {
            reg_->cr1.bit.m = 1; // Set 9 bit word length
            break;
        }
        default:
        {
            break;
        }
    }
}

template <class A>
void UsartResource<A>::setStopBits()
{
    switch( config_.stopBits )
    {
        case STOPBITS_1:
        {
            reg_->cr2.bit.stop = 0; // Set 1 stop bit
            break;
        }
        case STOPBITS_2:
        {
            reg_->cr2.bit.stop = 2; // Set 2 stop bit
            break;
        }
        default:
        {
            break;
        }
    }
}

template <class A>
void UsartResource<A>::setParity()
{
    switch( config_.parity )
    {
        case PARITY_NONE:
        {
            reg_->cr1.bit.pce = 0; // Set Parity control enable to Disable checksum control
            break;
        }
        case PARITY_ODD:
        {
            reg_->cr1.bit.pce = 1; // Set Parity control enable to Enable checksum control
            reg_->cr1.bit.ps = 1;  // Set Parity selection to Odd check
            break;
        }
        case PARITY_EVEN:
        {
            reg_->cr1.bit.pce = 1; // Set Parity control enable to Enable checksum control
            reg_->cr1.bit.ps = 0;  // Set Parity selection to Even check
            break;
        }
        default:
        {
            break;
        }
    }    
}

template <class A>
void UsartResource<A>::setFlowControl()
{
    if( config_.flowControl == FLOWCONTROL_NONE )
    {
        reg_->cr3.bit.rtse = 0;  // Set RTS enable to Disable RTS hardware flow control
        reg_->cr3.bit.ctse = 0;  // Set CTS enable to Disable CTS hardware flow control
    }
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
