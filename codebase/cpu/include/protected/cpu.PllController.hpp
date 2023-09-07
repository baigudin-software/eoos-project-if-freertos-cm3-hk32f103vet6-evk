/**
 * @file      cpu.PllController.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2017-2023, Sergey Baigudin, Baigudin Software
 */ 
#ifndef CPU_PLLCONTROLLER_HPP_
#define CPU_PLLCONTROLLER_HPP_

#include "cpu.NonCopyable.hpp"
#include "api.CpuPllController.hpp"
#include "api.Guard.hpp"
#include "cpu.Registers.hpp"

namespace eoos
{
namespace cpu
{

/**
 * @class PllController
 * @brief CPU HW PLL controller.
 */
class PllController : public NonCopyable<NoAllocator>, public api::CpuPllController
{
    typedef NonCopyable<NoAllocator> Parent;

public:

    /**
     * @brief Constructor.
     *
     * @param reg Target CPU register model.
     * @param gie Global interrupt enable controller.
     */
    PllController(Registers& reg, api::Guard& gie);

    /** 
     * @brief Destructor.
     */                               
    virtual ~PllController();
    
    /**
     * @copydoc eoos::api::Object::isConstructed()
     */ 
    virtual bool_t isConstructed() const;
        
    /**
     * @copydoc eoos::api::CpuPllController::getSourceClock()
     */      
    virtual int64_t getSourceClock();

    /**
     * @copydoc eoos::api::CpuPllController::getCpuClock()
     */  
    virtual int64_t getCpuClock();
    
private:

    /**
     * @brief Constructs this object.
     *
     * @return true if object has been constructed successfully.
     */
    bool_t construct();
    
    /**
     * @brief  Initializes HW clocks.
     *
     * @return true if initialized successfully.
     */
    bool_t initialize();

    /**
     * @brief  Sets SYSCLK source to 72 MHz.
     *
     * @return true if is set successfully.
     *
     * @todo This function has to be redeclarated and reimplemented to calculate 
     * all the divs and muls for all avalable SYSCLKs can be given as argument.
     */    
    bool_t setSysClkTo72();
    
    /**
     * @brief HSERDY bit waitting timeout.
     */        
    static const int32_t REG_RCC_HSERDY_TIMEOUT = 0xFFFF;
    
    /**
     * @brief Target CPU register model.
     */        
    Registers& reg_;
    
    /**
     * @brief Global interrupt enable controller.
     */
    api::Guard& gie_;

};
    
} // namespace cpu
} // namespace eoos
#endif // CPU_PLLCONTROLLER_HPP_
