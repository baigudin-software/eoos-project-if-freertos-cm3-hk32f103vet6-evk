/**
 * @file      cpu.TimerController.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2019-2023, Sergey Baigudin, Baigudin Software
 */  
#ifndef CPU_TIMERCONTROLLER_HPP_
#define CPU_TIMERCONTROLLER_HPP_

#include "cpu.NonCopyable.hpp"
#include "api.CpuTimerController.hpp"
#include "cpu.TimerSystem.hpp"
#include "cpu.Registers.hpp"
#include "lib.ResourceMemory.hpp"

namespace eoos
{
namespace cpu
{

/**
 * @class TimerController
 * @brief CPU HW timer controller.
 */
class TimerController : public NonCopyable<NoAllocator>, public api::CpuTimerController
{
    typedef NonCopyable<NoAllocator> Parent;
    typedef TimerSystem<TimerController> Resource;
    
public:

    /**
     * @brief Constructor.
     *
     * @param reg Target CPU register model.
     * @param gie Global interrupt enable controller.
     */
    TimerController(Registers& reg, api::Guard& gie);

    /**
     * @brief Destructor.
     */
    virtual ~TimerController();

    /**
     * @copydoc eoos::api::Object::isConstructed()
     */
    virtual bool isConstructed() const;
    
    /**
     * @copydoc eoos::api::CpuTimerController::createResource()
     */      
    virtual api::CpuTimer* createResource(int32_t index);
    
    /**
     * @copydoc eoos::api::CpuTimerController::getNumberSystick()
     */
    virtual int32_t getNumberSystick() const;    

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

private:

    /**
     * @brief Constructs this object.
     *
     * @return true if object has been constructed successfully.
     */
    bool_t construct();
    
    /**
     * @brief Creates system timer.
     *
     * @return SysTick timer.
     */      
    api::CpuTimer* createResourceTimerSystem();
    
    /**
     * @brief Initializes the allocator with heap for resource allocation.
     *
     * @param resource Heap for resource allocation.
     * @return True if initialized.
     */
    static bool_t initialize(api::Heap* resource);

    /**
     * @brief Deinitializes the allocator.
     */
    static void deinitialize();
    
    /**
     * @brief Heap for resource allocation.
     */
    static api::Heap* resource_;
    
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
    lib::ResourceMemory<Resource, EOOS_GLOBAL_CPU_NUMBER_OF_SYSTEM_TIMERS> memory_;

    /**
     * @brief Global data for all TimerSystem objects;
     */    
    Resource::Data data_;

};

} // namespace cpu
} // namespace eoos
#endif // CPU_TIMERCONTROLLER_HPP_
