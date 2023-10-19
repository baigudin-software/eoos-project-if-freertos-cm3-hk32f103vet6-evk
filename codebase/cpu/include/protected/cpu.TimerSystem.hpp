/**
 * @file      cpu.TimerSystem.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2014-2023, Sergey Baigudin, Baigudin Software
 */
#ifndef CPU_TIMERSYSTEM_HPP_
#define CPU_TIMERSYSTEM_HPP_

#include "cpu.NonCopyable.hpp"
#include "api.CpuTimer.hpp"
#include "api.Task.hpp"
#include "api.Guard.hpp"
#include "cpu.Registers.hpp"
#include "lib.Guard.hpp"

namespace eoos
{
namespace cpu
{

/**
 * @class TimerSystem
 * @brief CPU HW system timer (SysTick) resource.
 * 
 * @tparam A Heap memory allocator class.
 */
template <class A>
class TimerSystem : public NonCopyable<A>, public api::CpuTimer
{
    typedef NonCopyable<A> Parent;

public:

    /**
     * @enum Index
     * @brief Timer indexs.
     */
    enum Index
    {
        INDEX_SYSTICK = 0
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

    };

    /**
     * @brief Constructor.
     *
     * @param data Global data for all theses objects.
     */
    TimerSystem(Data& data);
    
    /** 
     * @brief Destructor.
     */                               
    virtual ~TimerSystem();
    
    /**
     * @copydoc eoos::api::Object::isConstructed()
     */
    virtual bool_t isConstructed() const;    
    
    /**
     * @copydoc eoos::api::CpuTimer::setPeriod()
     */      
    virtual bool_t setPeriod(int64_t us);
    
    /**
     * @copydoc eoos::api::CpuTimer::start()
     */      
    virtual void start();
    
    /**
     * @copydoc eoos::api::CpuTimer::stop()
     */      
    virtual void stop();
    
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
    
};

template <class A>
TimerSystem<A>::TimerSystem(Data& data)
    : NonCopyable<A>()
    , api::CpuTimer() 
    , data_( data ) {
    bool_t const isConstructed( construct() );
    setConstructed( isConstructed );
}    

template <class A>
TimerSystem<A>::~TimerSystem()
{
    deinitialize();
}

template <class A>
bool_t TimerSystem<A>::isConstructed() const
{
    return Parent::isConstructed();
}

template <class A>
bool_t TimerSystem<A>::setPeriod(int64_t us)
{
    if( !isConstructed() )
    {
        return false;
    }
    // @todo Implement calculation for SysTick Reload Value Register
    // depending on calibration value TENMS and the argument param.
    if( us != 1000 )
    {
        return false;
    }
    lib::Guard<A> guard(data_.gie);
    // System Tick (SysTick) Calibration Value Register
    // The system tick calibration value is fixed at 9000, 
    // and when the system tick clock is set to 9 MHz (HCLK/8 and HCLK=72 MHz), 
    // 1 ms is generated.
    // @note Therefore, suppose HK put value 9000 for 1 ms instead of 
    // that ARMv7-M says this indicates the preload value required for 
    // a 10ms (100Hz) system clock.
    data_.reg.scs.tick->rvr.bit.reload = data_.reg.scs.tick->cr.bit.tenms;
    // The SYST_CVR value is UNKNOWN on reset. Before enabling the SysTick counter, software must write the
    // required counter value to SYST_RVR, and then write to SYST_CVR. This clears SYST_CVR to zero.
    data_.reg.scs.tick->cvr.bit.current = data_.reg.scs.tick->cr.bit.tenms;
    return true;
}

template <class A>
void TimerSystem<A>::start()
{
    if( isConstructed() )
    {
        lib::Guard<A> guard(data_.gie);
        data_.reg.scs.tick->csr.bit.enable = 1;
    }
}

template <class A>
void TimerSystem<A>::stop()
{
    if( isConstructed() )
    {
        lib::Guard<A> guard(data_.gie);
        data_.reg.scs.tick->csr.bit.enable = 0;
    }
}

template <class A>
bool_t TimerSystem<A>::construct()
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

template <class A>
bool_t TimerSystem<A>::initialize()
{
    bool_t res( false );
    do 
    {
        lib::Guard<A> guard(data_.gie);
        // Test if the timer resource is not occupied
        //
        // @todo Avoid checking the enable bit, as the timer might be stopped
        // and if dynamic heap memory allocation is enabled, the timer resource
        // will be occupied twice. It needs to check resource initialization
        // based on an external global flag.
        if( data_.reg.scs.tick->csr.bit.enable == 1 )
        {
            break;
        }
        // Test if the reference clock is implemented
        if( data_.reg.scs.tick->cr.bit.noref == 1 )
        {
            break;
        }
        data_.reg.scs.tick->rvr.bit.reload = 0;    // Disables the counter on the next wrap
        data_.reg.scs.tick->cvr.bit.current = 0;   // Clear both the register and the COUNTFLAG status bit to zero
        data_.reg.scs.tick->csr.bit.clksource = 0; // Set SysTick uses the external reference clock (HCLK/8).
        res = true;
    } while(false);
    return res;
}

template <class A>
void TimerSystem<A>::deinitialize()
{
    lib::Guard<A> guard(data_.gie);
    data_.reg.scs.tick->csr.bit.enable = 0;
}

template <class A>
TimerSystem<A>::Data::Data(Registers& areg, api::Guard& agie)
    : reg(areg)
    , gie(agie) {
}

} // namespace cpu
} // namespace eoos
#endif // CPU_TIMERSYSTEM_HPP_
