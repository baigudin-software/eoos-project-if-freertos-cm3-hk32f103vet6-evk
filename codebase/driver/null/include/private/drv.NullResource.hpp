/**
 * @file      drv.NullResource.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2023, Sergey Baigudin, Baigudin Software
 */
#ifndef DRV_NULLRESOURCE_HPP_
#define DRV_NULLRESOURCE_HPP_

#include "api.Supervisor.hpp"
#include "lib.NonCopyable.hpp"
#include "drv.Null.hpp"
#include "cpu.Registers.hpp"
#include "lib.NoAllocator.hpp"
#include "lib.Mutex.hpp"
#include "lib.Guard.hpp"

namespace eoos
{
namespace drv
{

/**
 * @class NullResource
 * @brief Unknown device resource.
 * 
 * @tparam A Heap memory allocator class.
 */
template <class A>
class NullResource : public lib::NonCopyable<A>, public Null
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
    NullResource(Data& data, Config const& config);
    
    /** 
     * @brief Destructor.
     */                               
    virtual ~NullResource();
    
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
     * @brief Global data for all these objects;
     */
    Data& data_;
        
    /**
     * @brief Configuration of the resource.
     */
    Config config_;    
    
    /**
     * @brief This resource mutex.
     */
    lib::Mutex<A> mutex_;
    
};

template <class A>
NullResource<A>::NullResource(Data& data, Config const& config)
    : lib::NonCopyable<A>()
    , data_( data )
    , config_( config )
    , mutex_() {
    bool_t const isConstructed( construct() );
    setConstructed( isConstructed );
}    

template <class A>
NullResource<A>::~NullResource()
{
    deinitialize();
}

template <class A>
bool_t NullResource<A>::isConstructed() const
{
    return Parent::isConstructed();
}

template <class A>
api::OutStream<char_t>& NullResource<A>::operator<<(char_t const* source)
{
    return *this;
}

template <class A>
api::OutStream<char_t>& NullResource<A>::operator<<(int32_t value)
{
    return *this;
}

template <class A>
api::OutStream<char_t>& NullResource<A>::flush()
{
    return *this;    
}

template <class A>
bool_t NullResource<A>::construct()
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
bool_t NullResource<A>::isNumberValid()
{
    return NUMBER_NULL0 == config_.number;
}

template <class A>
bool_t NullResource<A>::initialize()
{
    bool_t res( false );
    do 
    {
        lib::Guard<A> const guard(data_.mutex);
        res = true;
    } while(false);
    return res;
}

template <class A>
void NullResource<A>::deinitialize()
{
    lib::Guard<A> const guard(data_.mutex);
}

template <class A>
NullResource<A>::Data::Data(cpu::Registers& areg, api::Supervisor& asvc)
    : reg( areg )
    , svc( asvc )
    , mutex() {
}

} // namespace drv
} // namespace eoos
#endif // DRV_USARTRESOURCE_HPP_
