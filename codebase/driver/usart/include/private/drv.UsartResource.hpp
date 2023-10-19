/**
 * @file      drv.UsartResource.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2023, Sergey Baigudin, Baigudin Software
 */
#ifndef DRV_USARTRESOURCE_HPP_
#define DRV_USARTRESOURCE_HPP_

#include "lib.NonCopyable.hpp"
#include "drv.Usart.hpp"
#include "cpu.Registers.hpp"
#include "api.Supervisor.hpp"

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
     * @brief Global data for all these objects;
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
     * @brief Global data for all these objects;
     */
    Data& data_;
    
    /**
     * @brief number Number of USART or UART.
     */
    int32_t number_;
    
};

template <class A>
UsartResource<A>::UsartResource(Data& data, int32_t number)
    : lib::NonCopyable<A>()
    , data_( data )
    , number_( number ) {
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
        res = false;
    } while(false);
    return res;
}

template <class A>
void UsartResource<A>::deinitialize()
{
}

template <class A>
UsartResource<A>::Data::Data(cpu::Registers& areg, api::Supervisor& asvc)
    : reg( areg )
    , svc( asvc ) {
}

} // namespace drv
} // namespace eoos
#endif // DRV_USARTRESOURCE_HPP_
