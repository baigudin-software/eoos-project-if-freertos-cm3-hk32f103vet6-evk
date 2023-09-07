/**
 * @file      cpu.Processor.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2019-2023, Sergey Baigudin, Baigudin Software
 */
#ifndef CPU_PROCESSOR_HPP_
#define CPU_PROCESSOR_HPP_

#include "cpu.NonCopyable.hpp"
#include "api.CpuProcessor.hpp"
#include "cpu.Registers.hpp"
#include "cpu.InterruptGlobal.hpp"
#include "cpu.PllController.hpp"
#include "cpu.InterruptController.hpp"
#include "cpu.TimerController.hpp"

namespace eoos
{
namespace cpu
{

/**
 * @class Processor
 * @brief The operating system target CPU class..
 */
class Processor : public NonCopyable<NoAllocator>, public api::CpuProcessor
{
    typedef NonCopyable<NoAllocator> Parent;

public:

    /**
     * Constructor.
     */
    Processor();

    /**
     * Destructor.
     */
    virtual ~Processor();

    /**
     * @copydoc eoos::api::Object::isConstructed()
     */
    virtual bool_t isConstructed() const;

    /**
     * @copydoc eoos::api::CpuProcessor::getName()
     */
    virtual const char_t* getName() const;

    /**
     * @copydoc eoos::api::CpuProcessor::getCoreId()
     */
    virtual int32_t getCoreId() const;
    
    /**
     * @copydoc eoos::api::CpuProcessor::getPllController()     
     */
    virtual api::CpuPllController& getPllController();

    /**
     * @copydoc eoos::api::CpuProcessor::getInterruptController()
     */
    virtual api::CpuInterruptController& getInterruptController();

    /**
     * @copydoc eoos::api::CpuProcessor::getTimerController()
     */
    virtual api::CpuTimerController& getTimerController();

private:

    /**
     * @brief Constructs this object.
     *
     * @return true if object has been constructed successfully.
     */
    bool_t construct();
    
    /**
     * @brief Target CPU register model.
     */        
    Registers reg_;
    
    /**
     * @brief Target CPU global interrupt enable controller.
     */
    InterruptGlobal gie_;
    
    /**
     * @brief Target CPU phase-locked loopt controller.
     */    
    PllController pll_;

    /**
     * @brief Target CPU interrupt controller.
     */
    InterruptController int_;

    /**
     * @brief Target TIM interrupt controller.
     */
    TimerController tim_;

};

} // namespace cpu
} // namespace eoos
#endif // CPU_PROCESSOR_HPP_
