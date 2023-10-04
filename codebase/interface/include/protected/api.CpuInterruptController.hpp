/**
 * @file      api.CpuInterruptController.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2023, Sergey Baigudin, Baigudin Software
 */ 
#ifndef API_CPUINTERRUPTCONTROLLER_HPP_
#define API_CPUINTERRUPTCONTROLLER_HPP_

#include "api.Object.hpp"
#include "api.CpuInterrupt.hpp"
#include "api.Task.hpp"
#include "api.Guard.hpp"

namespace eoos
{
namespace api
{

/**
 * @class CpuInterruptController
 * @brief CPU HW interrupt controller.
 */
class CpuInterruptController : public Object
{

public:
    
    /** 
     * @brief Destructor.
     */                               
    virtual ~CpuInterruptController() = 0;
    
    /**
     * @brief Creates a new HW interrupt resource.
     *
     * @param handler User class which implements an interrupt handler interface.
     * @param source  Available interrupt source number.
     * @return A new interrupt resource, or NULL if an error has been occurred.
     */      
    virtual CpuInterrupt* createResource(Task& handler, int32_t source) = 0;

    /**
     * @brief Returns global interrupt controller.
     *
     * @returns Global interrupt controller.
     */      
    virtual api::Guard& getGlobal() = 0;
    
    /**
     * @brief Jumps to interrupt service routine.
     *
     * @param source Interrupt source number.
     */      
    virtual void jump(int32_t source) = 0;

};

inline CpuInterruptController::~CpuInterruptController() {}
    
} // namespace api
} // namespace eoos
#endif // API_CPUINTERRUPTCONTROLLER_HPP_
