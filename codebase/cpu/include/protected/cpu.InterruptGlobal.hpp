/**
 * @file      cpu.InterruptGlobal.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2016-2023, Sergey Baigudin, Baigudin Software
 */ 
#ifndef CPU_INTERRUPTGLOBAL_HPP_
#define CPU_INTERRUPTGLOBAL_HPP_

#include "cpu.NonCopyable.hpp"
#include "api.Guard.hpp"

namespace eoos
{
namespace cpu
{

/**
 * @class InterruptGlobal
 * @brief CPU HW global interrupt controller.
 */
class InterruptGlobal : public NonCopyable<NoAllocator>, public api::Guard
{
    typedef NonCopyable<NoAllocator> Parent;

public:

    /**
     * @brief Constructor.
     */
    InterruptGlobal();

    /** 
     * @brief Destructor.
     */                               
    virtual ~InterruptGlobal();
    
    /**
     * @copydoc eoos::api::Object::isConstructed()
     */
    virtual bool_t isConstructed() const;
        
    /**
     * @brief Disables all maskable interrupts.
     *
     * This function disables all maskable interrupts of the MCU and returns
     * true if GI was enabled before the function call. This means that not to 
     * break nesting call, the unlock function has to be called only if the lock
     * function returned true. Therefore, the best way to call API of the class
     * is to pass an object of the class to a lib::Guard object which follows
     * this agreement under hood.
     *
     * @return Global interrupts enable bit value before the function was called.
     */
    virtual bool_t lock();

    /**
     * @brief Enables all maskable interrupts.
     */
    virtual void unlock();

private:

    /**
     * Constructs this object.
     *
     * @return true if object has been constructed successfully.
     */
    bool_t construct();

};
    
} // namespace cpu
} // namespace eoos
#endif // CPU_INTERRUPTGLOBAL_HPP_
