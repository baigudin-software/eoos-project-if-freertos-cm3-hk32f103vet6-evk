/**
 * @file      cpu.RegistersController.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2016-2023, Sergey Baigudin, Baigudin Software
 */ 
#ifndef CPU_REGISTERSCONTROLLER_HPP_
#define CPU_REGISTERSCONTROLLER_HPP_

#include "cpu.NonCopyable.hpp"
#include "api.CpuRegistersController.hpp"
#include "cpu.Registers.hpp"
#include "api.Guard.hpp"

namespace eoos
{
namespace cpu
{

/**
 * @class RegistersController
 * @brief CPU ABI registers controller.
 */
class RegistersController : public NonCopyable<NoAllocator>, public api::CpuRegistersController
{
    typedef NonCopyable<NoAllocator> Parent;

public:

    /**
     * @brief Constructor.
     */
    RegistersController();

    /** 
     * @brief Destructor.
     */                               
    virtual ~RegistersController();
    
    /**
     * @copydoc eoos::api::Object::isConstructed()
     */
    virtual bool_t isConstructed() const;
        
    /**
     * @copydoc eoos::api::CpuRegistersController::initializeStack()
     */
    virtual void* initializeStack(void* stack, void* entry, void* exit, int32_t argument);

private:

    /**
     * @brief ABI stack type.
     */
    typedef uint32_t stack_t;

    /**
     * @brief Constructs this object.
     *
     * @return true if object has been constructed successfully.
     */
    bool_t construct();

};
    
} // namespace cpu
} // namespace eoos
#endif // CPU_REGISTERSCONTROLLER_HPP_
