/**
 * @file      api.CpuTimer.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2016-2023, Sergey Baigudin, Baigudin Software
 */ 
#ifndef API_CPUTIMER_HPP_
#define API_CPUTIMER_HPP_

#include "api.Object.hpp"

namespace eoos
{
namespace api
{

/**
 * @class CpuTimer
 * @brief CPU HW timer resource.
 */
class CpuTimer : public Object
{

public:
    
    /** 
     * @brief Destructor.
     */                               
    virtual ~CpuTimer() = 0;
        
    /**
     * @brief Sets this timer period.
     *
     * @param us - timer period in microseconds, zero value sets a period to maximum value.
     * @return True if period is set successfully.
     */      
    virtual bool_t setPeriod(int64_t us) = 0;
    
    /**
     * @brief Starts this timer count.
     */      
    virtual void start() = 0;
    
    /**
     * @brief Stops this timer count.
     */      
    virtual void stop() = 0;

};

inline CpuTimer::~CpuTimer() {}
    
} // namespace api
} // namespace eoos
#endif // API_CPUTIMER_HPP_
