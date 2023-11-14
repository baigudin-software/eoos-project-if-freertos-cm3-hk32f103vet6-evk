/**
 * @file      drv.GpioController.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2019-2023, Sergey Baigudin, Baigudin Software
 */  
#include "drv.GpioController.hpp"
#include "sys.Svc.hpp"
#include "lib.UniquePointer.hpp"

namespace eoos
{
namespace drv
{
    
/**
 * @brief Driver memory pool.
 * 
 * @note Memory is uint64_t type to be align 8.  
 */
static uint64_t memory_[(sizeof(GpioController) >> 3) + 1]; 
    
api::Heap* GpioController::resource_( NULLPTR );

GpioController::GpioController()
    : lib::NonCopyable<lib::NoAllocator>()
    , reg_()
    , pool_()
    , data_( reg_, sys::Svc::get() ) {     
    bool_t const isConstructed( construct() );
    setConstructed( isConstructed );
}

GpioController::~GpioController()
{
    GpioController::deinitialize();
}

bool_t GpioController::isConstructed() const
{
    return Parent::isConstructed();
}

Gpio* GpioController::createResource(Gpio::Config const& config)
{
    Resource* ptr( NULLPTR );
    if( isConstructed() )
    {
        lib::UniquePointer<Resource> res( new Resource(data_, config) );
        if( !res.isNull() )
        {
            if( !res->isConstructed() )
            {
                res.reset();
            }
        }
        ptr = res.release();
    }    
    return ptr;
}

bool_t GpioController::construct()
{
    bool_t res( false );
    do 
    {
        if( !isConstructed() )
        {
            break;
        }
        if( !pool_.memory.isConstructed() )
        {
            break;
        }
        if( !initialize(&pool_.memory) )
        {
            break;
        }
        res = true;
    } while(false);
    return res;
}

void* GpioController::allocate(size_t size)
{
    if( resource_ != NULLPTR )
    {
        return resource_->allocate(size, NULLPTR);
    }
    else
    {
        return NULLPTR;
    }
}

void GpioController::free(void* ptr)
{
    if( resource_ != NULLPTR )
    {
        resource_->free(ptr);
    }
}

bool_t GpioController::initialize(api::Heap* resource)
{
    if( resource_ != NULLPTR )
    {
        return false;
    }
    else
    {
        resource_ = resource;
        return true;
    }
}

void GpioController::deinitialize()
{
    resource_ = NULLPTR;
}

void* GpioController::operator new(size_t size)
{
    void* memory( NULLPTR );
    if( size == sizeof(GpioController) )
    {
        memory = reinterpret_cast<void*>(memory_);
    }
    return memory;
}

void GpioController::operator delete(void* const ptr)
{
}

GpioController::ResourcePool::ResourcePool()
    : mutex_()
    , memory( mutex_ ) {
}

} // namespace cpu
} // namespace eoos
