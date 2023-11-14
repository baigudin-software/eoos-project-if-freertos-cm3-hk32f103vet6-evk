/**
 * @file      drv.GpioResource.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2023, Sergey Baigudin, Baigudin Software
 */
#ifndef DRV_GPIORESOURCE_HPP_
#define DRV_GPIORESOURCE_HPP_

#include "api.Supervisor.hpp"
#include "lib.NonCopyable.hpp"
#include "drv.Gpio.hpp"
#include "cpu.Registers.hpp"
#include "lib.NoAllocator.hpp"
#include "lib.Mutex.hpp"
#include "lib.Guard.hpp"

namespace eoos
{
namespace drv
{

/**
 * @class GpioResource
 * @brief GPIO driver resource.
 * 
 * @tparam A Heap memory allocator class.
 */
template <class A>
class GpioResource : public lib::NonCopyable<A>, public Gpio
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
     * @param config Configuration of the driver resource.     
     */
    GpioResource(Data& data, Config const& config);
    
    /** 
     * @brief Destructor.
     */                               
    virtual ~GpioResource();
    
    /**
     * @copydoc eoos::api::Object::isConstructed()
     */
    virtual bool_t isConstructed() const;  

    /**
     * @copydoc eoos::drv::Gpio::pullUp()
     */                               
    virtual void pullUp();

    /**
     * @copydoc eoos::drv::Gpio::pullDown()
     */                               
    virtual void pullDown();

    /**
     * @copydoc eoos::drv::Gpio::isPullUp()
     */                               
    virtual bool_t isPullUp() const;

    /**
     * @copydoc eoos::drv::Gpio::isPullDown()
     */                               
    virtual bool_t isPullDown() const;
        
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
     * @brief Tests if given number is correct.
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
     * @brief Enables port clock.
     */
    void enableClock();

    /**
     * @brief Configs low port.
     */    
    void configureLow();

    /**
     * @brief Configs high port.
     */
    void configureHigh();
    
    /**
     * @brief Modifies value for CRL or CRH register.
     *
     * @param value Current value of a register 
     * @param gpio  GPIO possition in the register
     * @return A new value for the register to write it into.
     */
    uint32_t getConfigureRegister(uint32_t value, uint32_t gpio);   
        
    /**
     * @brief Global data for all these objects;
     */
    Data& data_;
        
    /**
     * @brief Configuration of the resource.
     */
    Config config_;    
    
    /**
     * @brief GPIO registers.
     */
    cpu::reg::Gpio* reg_;
    
    /**
     * @brief This resource mutex.
     */
    lib::Mutex<A> mutex_;
    
};

template <class A>
GpioResource<A>::GpioResource(Data& data, Config const& config)
    : lib::NonCopyable<A>()
    , data_( data )
    , config_( config )
    , reg_(  data_.reg.gpio[config_.port]  )
    , mutex_() {
    bool_t const isConstructed( construct() );
    setConstructed( isConstructed );
}    

template <class A>
GpioResource<A>::~GpioResource()
{
    deinitialize();
}

template <class A>
bool_t GpioResource<A>::isConstructed() const
{
    return Parent::isConstructed();
}

template <class A>
void GpioResource<A>::pullUp()
{
    if( isConstructed() && (config_.mode != MODE_INPUT) )
    {
        uint32_t const bit( 1 << config_.gpio );
        reg_->odr.value = reg_->odr.value | bit;
    }
}

template <class A>
void GpioResource<A>::pullDown()
{
    if( isConstructed() && (config_.mode != MODE_INPUT) )
    {
        uint32_t const mask( ~(1 << config_.gpio) & 0xFFFF );
        reg_->odr.value = reg_->odr.value & mask;
    }    
}

template <class A>
bool_t GpioResource<A>::isPullUp() const
{
    bool_t bit(false);
    if( isConstructed() )
    {
        uint32_t value( reg_->idr.value );
        uint32_t const mask( 1 << config_.gpio );
        value &= mask;
        bit = (value != 0) ? true : false;
    }
    return bit;
}

template <class A>
bool_t GpioResource<A>::isPullDown() const
{
    bool_t bit(false);
    if( isConstructed() )
    {
        uint32_t value( reg_->idr.value );
        uint32_t const mask( 1 << config_.gpio );
        value &= mask;
        bit = (value == 0) ? true : false;
    }
    return bit;
}

template <class A>
bool_t GpioResource<A>::construct()
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
bool_t GpioResource<A>::isNumberValid()
{
    return ( 
        ( PORTNUMBER_A <= config_.port && config_.port <= PORTNUMBER_E )
     && ( GPIONUMBER_0 <= config_.gpio && config_.gpio <= GPIONUMBER_15 )
    );    
}

template <class A>
bool_t GpioResource<A>::initialize()
{
    bool_t res( false );
    do 
    {
        lib::Guard<A> const guard(data_.mutex);
        enableClock();
        configureLow();
        configureHigh();
        res = true;
    } while(false);
    return res;
}

template <class A>
void GpioResource<A>::deinitialize()
{
    lib::Guard<A> const guard(data_.mutex);
}

template <class A>
void GpioResource<A>::enableClock()
{
    switch( config_.port )
    {
        case PORTNUMBER_A:
        {
            data_.reg.rcc->apb2enr.bit.iopaen = 1;
            break;
        }
        case PORTNUMBER_B:
        {
            data_.reg.rcc->apb2enr.bit.iopben = 1;
            break;
        }
        case PORTNUMBER_C:
        {
            data_.reg.rcc->apb2enr.bit.iopcen = 1;
            break;
        }
        case PORTNUMBER_D:
        {
            data_.reg.rcc->apb2enr.bit.iopden = 1;
            break;
        }
        case PORTNUMBER_E:
        {
            data_.reg.rcc->apb2enr.bit.iopeen = 1;
            break;
        }
        default:
        {
            break;
        }
    }
}

template <class A>
void GpioResource<A>::configureLow()
{
    if( GPIONUMBER_0 <= config_.gpio && config_.gpio <= GPIONUMBER_7 )
    {
        reg_->crl.value = getConfigureRegister(reg_->crl.value, config_.gpio);  
    }
}
 
template <class A>
void GpioResource<A>::configureHigh()
{
    if( GPIONUMBER_8 <= config_.gpio && config_.gpio <= GPIONUMBER_15 )
    {
        reg_->crh.value = getConfigureRegister(reg_->crh.value, config_.gpio - 8);          
    }
}

template <class A>
uint32_t GpioResource<A>::getConfigureRegister(uint32_t value, uint32_t gpio)
{
    uint32_t const shift( gpio * 4 );
    uint32_t cnf(0);
    uint32_t mode( config_.mode );
    if( config_.mode != MODE_INPUT )
    {
        cnf = config_.direction.output;
    }
    else
    {
        cnf = config_.direction.input;
    }
    uint32_t conf( ((cnf << 2) | mode) << shift );
    uint32_t mask( 0xF << shift );
    value &= ~mask;
    value |= conf;
    return value;
}

template <class A>
GpioResource<A>::Data::Data(cpu::Registers& areg, api::Supervisor& asvc)
    : reg( areg )
    , svc( asvc )
    , mutex() {
}

} // namespace drv
} // namespace eoos
#endif // DRV_USARTRESOURCE_HPP_
