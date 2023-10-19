/**
 * @file      drv.UsartController.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2019-2023, Sergey Baigudin, Baigudin Software
 */  
#include "drv.UsartController.hpp"
#include "sys.Svc.hpp"
#include "cpu.reg.Usart.hpp"
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
static uint64_t memory_[(sizeof(UsartController) >> 3) + 1]; 
    
api::Heap* UsartController::resource_( NULLPTR );

UsartController::UsartController()
    : lib::NonCopyable<lib::NoAllocator>()
    , reg_()
    , pool_()
    , data_( reg_, sys::Svc::get() ) {        
    bool_t const isConstructed( construct() );
    setConstructed( isConstructed );
}

UsartController::~UsartController()
{
    UsartController::deinitialize();
}

bool_t UsartController::isConstructed() const
{
    return Parent::isConstructed();
}

UsartController::Resource* UsartController::createResource(int32_t number)
{
    Resource* ptr( NULLPTR );
    if( isConstructed() )
    {
        lib::UniquePointer<Resource> res( new Resource(data_, number) );
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

bool_t UsartController::construct()
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

void* UsartController::allocate(size_t size)
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

void UsartController::free(void* ptr)
{
    if( resource_ != NULLPTR )
    {
        resource_->free(ptr);
    }
}

bool_t UsartController::initialize(api::Heap* resource)
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

void UsartController::deinitialize()
{
    resource_ = NULLPTR;
}

void* UsartController::operator new(size_t size)
{
    void* memory( NULLPTR );
    if( size == sizeof(UsartController) )
    {
        memory = reinterpret_cast<void*>(memory_);
    }
    return memory;
}

void UsartController::operator delete(void* const ptr)
{
}

UsartController::ResourcePool::ResourcePool()
    : mutex_()
    , memory( mutex_ ) {
}

} // namespace cpu
} // namespace eoos
