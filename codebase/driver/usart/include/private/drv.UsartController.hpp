/**
 * @file      drv.UsartController.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2023, Sergey Baigudin, Baigudin Software
 */  
#ifndef DRV_USARTCONTROLLER_HPP_
#define DRV_USARTCONTROLLER_HPP_

#include "drv.UsartResource.hpp"
#include "drv.UsartDefinitions.hpp"
#include "lib.NonCopyable.hpp"
#include "lib.NoAllocator.hpp"
#include "lib.Mutex.hpp"
#include "lib.ResourceMemory.hpp"

#ifndef EOOS_DRV_GLOBAL_NUMBER_OF_USARTS
#define EOOS_DRV_GLOBAL_NUMBER_OF_USARTS (5)
#endif

namespace eoos
{
namespace drv
{

/**
 * @class UsartController
 * @brief Universal Synchronous Asynchronous Transceiver (USART) controller.
 */
class UsartController : public lib::NonCopyable<lib::NoAllocator>
{
    typedef lib::NonCopyable<lib::NoAllocator> Parent;
    
public:

    /**
     * @class Resource.
     * @brief Universal Synchronous Asynchronous Transceiver (USART) resource.
     */
    typedef UsartResource<UsartController> Resource;

    /**
     * @brief Constructor.
     *
     * @param reg Target CPU register model.
     * @param gie Global interrupt enable controller.
     */
    UsartController();

    /**
     * @brief Destructor.
     */
    virtual ~UsartController();

    /**
     * @copydoc eoos::api::Object::isConstructed()
     */
    virtual bool isConstructed() const;
    
    /**
     * @brief Creates a new HW interrupt resource.
     *
     * @param number Number of the resource.
     * @return A new resource, or NULL if an error has been occurred.
     */      
    Resource* createResource(int32_t number);
    
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
     * @brief Operator new.
     *
     * @param size A number of bytes of this class.
     * @return The address memory_[] array.
     */
    static void* operator new(size_t size);
    
    /**
     * @brief Operator delete.
     *
     * @param ptr An address of allocated memory block or a null pointer.
     */
    static void operator delete(void* const ptr);    

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
    static bool_t initialize(api::Heap* heap);

    /**
     * @brief Deinitializes the allocator.
     */
    static void deinitialize();
    
    /**
     * @brief Heap for allocation.
     */
    static api::Heap* heap_;
    
    /**
     * @brief Mutex resource.
     */    
    lib::Mutex<lib::NoAllocator> mutex_;

    /**
     * @brief Resource memory allocator.
     */
    lib::ResourceMemory<Resource, EOOS_DRV_GLOBAL_NUMBER_OF_USARTS> memory_;

};

} // namespace drv
} // namespace eoos
#endif // DRV_USARTCONTROLLER_HPP_
