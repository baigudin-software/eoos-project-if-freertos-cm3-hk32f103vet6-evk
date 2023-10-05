/**
 * @file      cpu.InterruptController.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2019-2023, Sergey Baigudin, Baigudin Software
 */ 
#ifndef CPU_INTERRUPTCONTROLLER_HPP_
#define CPU_INTERRUPTCONTROLLER_HPP_

#include "cpu.NonCopyable.hpp"
#include "api.CpuInterruptController.hpp"
#include "cpu.Interrupt.hpp"
#include "cpu.Registers.hpp"
#include "lib.ResourceMemory.hpp"

namespace eoos
{
namespace cpu
{

/**
 * @class InterruptController
 * @brief CPU HW interrupt controller.
 */
class InterruptController : public NonCopyable<NoAllocator>, public api::CpuInterruptController
{
    typedef NonCopyable<NoAllocator> Parent;

public:

    /**
     * @brief Constructor.
     *
     * @param reg Target CPU register model.     
     * @param gie Global interrupt enable controller.
     */
    InterruptController(Registers& reg, api::Guard& gie);

    /** 
     * @brief Destructor.
     */                               
    virtual ~InterruptController();
    
    /**
     * @copydoc eoos::api::Object::isConstructed()
     */
    virtual bool_t isConstructed() const;
        
    /**
     * @copydoc eoos::api::CpuInterruptController::createResource()
     */
    virtual api::CpuInterrupt* createResource(api::Task& handler, int32_t source);

    /**
     * @copydoc eoos::api::CpuInterruptController::getGlobal()
     */      
    virtual api::Guard& getGlobal();
    
    /**
     * @copydoc eoos::api::CpuInterruptController::jump(int32_t)
     */      
    virtual void jump(int32_t exception);
    
    /**
     * @brief Allocates memory.
     *
     * @param size Number of bytes to allocate.
     * @return Allocated memory address or a null pointer.
     */
    static void* allocate(size_t size);

    /**
     * @brief Frees allocated memory.
     *
     * @param ptr Address of allocated memory block or a null pointer.
     */
    static void free(void* ptr);

    /**
     * @brief Handles exceptions.
     *
     * @param exception Exception number.
     */
    static void handleException(int32_t exception);

private:

    /**
     * @brief Constructs this object.
     *
     * @return true if object has been constructed successfully.
     */
    bool_t construct();

    /**
     * @brief Initializes the allocator with heap for allocation.
     *
     * @param heap Heap for allocation.
     * @return True if initialized.
     */
    bool_t initialize(api::Heap* heap);

    /**
     * @brief Deinitializes the allocator.
     */
    static void deinitialize();
    
    /**
     * @brief Heap for allocation.
     */
    static api::Heap* heap_;

    /**
     * @brief This object.
     */
    static InterruptController* this_;

    /**
     * @brief Target CPU register model.
     */        
    Registers& reg_;
    
    /**
     * @brief Global interrupt enable controller.
     */
    api::Guard& gie_;    

    /**
     * @brief Resource memory allocator.
     */     
    lib::ResourceMemory<Interrupt<InterruptController>, EOOS_CPU_GLOBAL_NUMBER_OF_INTERRUPTS> memory_;
    
    /**
     * @brief Global data for all Interrupt objects;
     */    
    Interrupt<InterruptController>::Data data_;

};
    
} // namespace cpu
} // namespace eoos
#endif // CPU_INTERRUPTCONTROLLER_HPP_
