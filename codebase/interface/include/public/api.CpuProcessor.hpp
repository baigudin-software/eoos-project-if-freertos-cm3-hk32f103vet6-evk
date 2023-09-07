/**
 * @file      api.CpuProcessor.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2018-2023, Sergey Baigudin, Baigudin Software
 */ 
#ifndef API_CPUPROCESSOR_HPP_
#define API_CPUPROCESSOR_HPP_

#include "api.Object.hpp"
#include "api.CpuPllController.hpp"
#include "api.CpuInterruptController.hpp"
#include "api.CpuTimerController.hpp"

namespace eoos
{
namespace api
{

/**
 * @class CpuProcessor
 * @brief A target CPU interface.
 */
class CpuProcessor : public Object
{

public:
    
    /** 
     * @brief Destructor.
     */                               
    virtual ~CpuProcessor() = 0;
    
    /**
     * @brief Returns a name of a target Central Processing Unit. 
     *
     * The function should return a certain name of target CPU, 
     * or a complex name of CPUs family. In addition, the function 
     * might return NULL pointer if a target CPU name were undefined, 
     * but basically the case is an exception.
     *
     * @return CPU name, or NULL if an error has been occurred.
     */      
    virtual const char_t* getName() const = 0;

    /**
     * @brief Returns an ID of CPU core executing this program code.
     *
     * @return CPU ID, or -1 if an error has been occurred.
     */
    virtual int32_t getCoreId() const = 0;

    /**
     * @brief Returns CPU HW phase-locked loop controller.
     *
     * @return Phase-locked loop controller.
     */
    virtual CpuPllController& getPllController() = 0;

    /**
     * @brief Returns CPU HW interrupt controller.
     *
     * @return Interrupt controller.
     */
    virtual CpuInterruptController& getInterruptController() = 0;

    /**
     * @brief Returns CPU HW timer controller.
     *
     * @return Timer controller.
     */
    virtual CpuTimerController& getTimerController() = 0;

};

inline CpuProcessor::~CpuProcessor() {}
    
} // namespace api
} // namespace eoos
#endif // API_CPU_HPP_
