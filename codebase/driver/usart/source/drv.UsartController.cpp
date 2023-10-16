/**
 * @file      drv.UsartController.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2019-2023, Sergey Baigudin, Baigudin Software
 */  
#include "drv.UsartController.hpp"
#include "lib.UniquePointer.hpp"
#include "cpu.reg.Usart.hpp"

namespace eoos
{
namespace drv
{
    
/**
 * @brief Driver memory pull.
 * 
 * @note Memory is uint64_t type to be align 8.  
 */
static uint64_t pull_[(sizeof(UsartController) >> 3) + 1]; 
    
api::Heap* UsartController::heap_( NULLPTR );

UsartController::UsartController()
    : lib::NonCopyable<lib::NoAllocator>()
    , mutex_()
    , memory_(mutex_) {        
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
        lib::UniquePointer<Resource> res( new Resource(number) );
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
        if( !memory_.isConstructed() )
        {
            break;
        }
        if( !initialize(&memory_) )
        {
            break;
        }
        res = true;
    } while(false);
    return res;
}

void* UsartController::allocate(size_t size)
{
    if( heap_ != NULLPTR )
    {
        return heap_->allocate(size, NULLPTR);
    }
    else
    {
        return NULLPTR;
    }
}

void UsartController::free(void* ptr)
{
    if( heap_ != NULLPTR )
    {
        heap_->free(ptr);
    }
}

bool_t UsartController::initialize(api::Heap* heap)
{
    if( heap_ != NULLPTR )
    {
        return false;
    }
    else
    {
        heap_ = heap;
        return true;
    }
}

void UsartController::deinitialize()
{
    heap_ = NULLPTR;
}

void* UsartController::operator new(size_t size)
{
    void* pull( NULLPTR );
    if( size == sizeof(UsartController) )
    {
        pull = reinterpret_cast<void*>(pull_);
    }
    return pull;
}

void UsartController::operator delete(void* const ptr)
{
}

} // namespace cpu
} // namespace eoos
