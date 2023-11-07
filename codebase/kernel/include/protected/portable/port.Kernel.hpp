/**
 * @file      port.Kernel.hpp
 * @brief     Universal EOOS port of FreeRTOS Kernel V10.5.1 (V202212.01)
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2023, Sergey Baigudin, Baigudin Software
 */
#ifndef PORT_KERNEL_HPP_
#define PORT_KERNEL_HPP_

#include "lib.NonCopyable.hpp"
#include "lib.NoAllocator.hpp"
#include "api.CpuProcessor.hpp"

namespace eoos
{
namespace port
{
   
/**
 * @class Kernel
 * @brief The operating system kernel.
 */   
class Kernel : public lib::NonCopyable<lib::NoAllocator>
{

public:

    /**
     * @brief Constructor.
     *
     * @param cpu The target processor.
     */
    Kernel(api::CpuProcessor& cpu);

    /**
     * @brief Destructor.
     */
    virtual ~Kernel();

    /**
     * @brief Causes to execute FeeRTOS kernel.
     *
     * @return The function will never return control to a caller.
     */
    void execute();
    
private:

    /**
     * @brief Constructs this object.
     *
     * @param cpu The target processor.
     * @return true if object has been constructed successfully.
     */
    bool_t construct(api::CpuProcessor& cpu);    

};

} // namespace port
} // namespace eoos

#endif // PORT_KERNEL_HPP_
