/**
 * @file      api.CpuInterrupt.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2016-2023, Sergey Baigudin, Baigudin Software
 */ 
#ifndef API_CPUINTERRUPT_HPP_
#define API_CPUINTERRUPT_HPP_

#include "api.Object.hpp"

namespace eoos
{
namespace api
{

/**
 * @class CpuInterrupt
 * @brief CPU HW interrupt resource.
 */
class CpuInterrupt : public Object
{

public:
    
    /** 
     * @brief Destructor.
     */                               
    virtual ~CpuInterrupt() = 0;

    /**
     * @brief Disable interrupt.
     */      
    virtual void disable() = 0;

    /**
     * @brief Enable interrupt.
     */      
    virtual void enable() = 0;

};

inline CpuInterrupt::~CpuInterrupt() {}
    
} // namespace api
} // namespace eoos
#endif // API_CPUINTERRUPT_HPP_
