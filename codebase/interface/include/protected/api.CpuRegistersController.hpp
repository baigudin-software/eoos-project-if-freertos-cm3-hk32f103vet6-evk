/**
 * @file      api.CpuRegistersController.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2016-2023, Sergey Baigudin, Baigudin Software
 */
#ifndef API_CPUREGISTERSCONTROLLER_HPP_
#define API_CPUREGISTERSCONTROLLER_HPP_

#include "api.Object.hpp"

namespace eoos
{
namespace api
{
    
/**
 * @class CpuRegistersController
 * @brief CPU ABI registers controller.
 */
class CpuRegistersController : public Object
{
  
public:
  
    /** 
     * @brief Destructor.
     */
    virtual ~CpuRegistersController() = 0;
    
    /** 
     * @brief Initializes the CPU registers on stack.
     *
     * @param stack    Tot of stack to be initialized.
     * @param entry    Entry point address.
     * @param exit     Exit point address.
     * @param argument First argument passed to entry function following ABI.
     * @return New top of stack.
     */  
    virtual void* initializeStack(void* stack, void* entry, void* exit, int32_t argument) = 0;

};

inline CpuRegistersController::~CpuRegistersController() {}
    
} // namespace api
} // namespace eoos
#endif // API_CPUREGISTERSCONTROLLER_HPP_
