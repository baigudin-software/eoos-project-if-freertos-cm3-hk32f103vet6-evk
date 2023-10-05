/**
 * @file      api.CpuTimerController.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2023, Sergey Baigudin, Baigudin Software
 */ 
#ifndef API_CPUTIMERCONTROLLER_HPP_
#define API_CPUTIMERCONTROLLER_HPP_

#include "api.Object.hpp"
#include "api.CpuTimer.hpp"

namespace eoos
{
namespace api
{

/**
 * @class CpuTimerController
 * @brief CPU HW timer controller.
 */
class CpuTimerController : public Object
{

public:
    
    /** 
     * @brief Destructor.
     */
    virtual ~CpuTimerController() = 0;
    
    /**
     * @brief Creates a new HW timer resource.
     *
     * @param index An available timer index.
     * @return A new timer resource, or NULL if an error has been occurred.
     */      
    virtual CpuTimer* createResource(int32_t index) = 0;

};

inline CpuTimerController::~CpuTimerController() {}
    
} // namespace api
} // namespace eoos
#endif // API_CPUTIMERCONTROLLER_HPP_
