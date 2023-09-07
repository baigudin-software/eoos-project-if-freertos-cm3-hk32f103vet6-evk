/**
 * @file      api.CpuPllController.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2017-2023, Sergey Baigudin, Baigudin Software
 */
#ifndef API_CPUPLLCONTROLLER_HPP_
#define API_CPUPLLCONTROLLER_HPP_

#include "api.Object.hpp"

namespace eoos
{
namespace api
{
    
/**
 * @class CpuPllController
 * @brief CPU HW phase-locked loop controller.
 */
class CpuPllController : public Object
{

public:

    /**
     * @brief Destructor.
     */                               
    virtual ~CpuPllController() = 0;

    /**
     * @brief Returns source clock of CPU oscillator in Hz.
     *
     * @return Frequency value in Hz.         
     */      
    virtual int64_t getSourceClock() = 0;

    /**
     * @brief Returns source clock of CPU in Hz.
     *
     * @return Frequency value in Hz.
     */  
    virtual int64_t getCpuClock() = 0;

};

inline CpuPllController::~CpuPllController() {}

} // namespace api
} // namespace eoos
#endif // API_CPUPLLCONTROLLER_HPP_
