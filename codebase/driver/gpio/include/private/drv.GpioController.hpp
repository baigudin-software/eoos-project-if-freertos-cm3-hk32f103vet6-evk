/**
 * @file      drv.GpioController.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2023, Sergey Baigudin, Baigudin Software
 */  
#ifndef DRV_GPIOCONTROLLER_HPP_
#define DRV_GPIOCONTROLLER_HPP_

#include "drv.GpioResource.hpp"
#include "drv.GpioDefinitions.hpp"
#include "lib.NonCopyable.hpp"
#include "lib.NoAllocator.hpp"
#include "lib.Mutex.hpp"
#include "lib.ResourceMemory.hpp"
#include "cpu.Registers.hpp"

namespace eoos
{
namespace drv
{

/**
 * @class GpioController
 * @brief Unknown device controller.
 */
class GpioController : public lib::NonCopyable<lib::NoAllocator>
{
    typedef lib::NonCopyable<lib::NoAllocator> Parent;
    typedef GpioResource<GpioController> Resource;
    
public:

    /**
     * @brief Constructor.
     */
    GpioController();

    /**
     * @brief Destructor.
     */
    virtual ~GpioController();

    /**
     * @copydoc eoos::api::Object::isConstructed()
     */
    virtual bool isConstructed() const;
    
    /**
     * @brief Creates a new HW interrupt resource.
     *
     * @param config Configuration of the driver resource.
     * @return A new resource, or NULL if an error has been occurred.
     */      
    Gpio* createResource(Gpio::Config const& config);
    
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
     * @param resource Heap for resource allocation.
     * @return True if initialized.
     */
    static bool_t initialize(api::Heap* resource);

    /**
     * @brief Deinitializes the allocator.
     */
    static void deinitialize();
    
    /**
     * @struct ResourcePool
     * @brief Resource memory pool.
     */
    struct ResourcePool
    {

    public:
        
        /**
         * @brief Constructor.
         */        
        ResourcePool();

    private:
            
        /**
         * @brief Mutex memory resource.
         */    
        lib::Mutex<lib::NoAllocator> mutex_;
    
    public:
    
        /**
         * @brief Resource memory allocator.
         */
        lib::ResourceMemory<Resource, EOOS_GLOBAL_DRV_NUMBER_OF_GPIOS> memory;

    };    
    
    /**
     * @brief Heap for resource allocation.
     */
    static api::Heap* resource_;
    
    /**
     * @brief Target CPU register model.
     *
     * @note Declare this here not in the resource class to minimize memory needed.
     */    
    cpu::Registers reg_;
    
    /**
     * @brief Resource memory pool.
     */
    ResourcePool pool_;

    /**
     * @brief Global data for all resource objects;
     */    
    Resource::Data data_;

};

} // namespace drv
} // namespace eoos
#endif // DRV_GPIOCONTROLLER_HPP_
