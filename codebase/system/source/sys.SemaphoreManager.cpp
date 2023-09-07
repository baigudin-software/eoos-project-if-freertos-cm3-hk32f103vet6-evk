/**
 * @file      sys.SemaphoreManager.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2023, Sergey Baigudin, Baigudin Software
 */
#include "sys.SemaphoreManager.hpp"
#include "lib.UniquePointer.hpp"

namespace eoos
{
namespace sys
{

api::Heap* SemaphoreManager::heap_( NULLPTR );

SemaphoreManager::SemaphoreManager() 
    : NonCopyable<NoAllocator>()
    , api::SemaphoreManager()
    , mutex_()
    , memory_(mutex_) {
    bool_t const isConstructed( construct() );
    setConstructed( isConstructed );
}

SemaphoreManager::~SemaphoreManager()
{
    SemaphoreManager::deinitialize();
}

bool_t SemaphoreManager::isConstructed() const
{
    return Parent::isConstructed();
}    

api::Semaphore* SemaphoreManager::create(int32_t permits)
{
    api::Semaphore* ptr( NULLPTR );
    if( isConstructed() )
    {
        lib::UniquePointer<api::Semaphore> res( new Semaphore<SemaphoreManager>(permits) );
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

bool_t SemaphoreManager::construct()
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
        if( !SemaphoreManager::initialize(&memory_) )
        {
            break;
        }
        res = true;
    } while(false);
    return res;
}

void* SemaphoreManager::allocate(size_t size)
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

void SemaphoreManager::free(void* ptr)
{
    if( heap_ != NULLPTR )
    {
        heap_->free(ptr);
    }
}

bool_t SemaphoreManager::initialize(api::Heap* heap)
{
    if( heap_ == NULLPTR )
    {
        heap_ = heap;
        return true;
    }
    else
    {
        return false;
    }
}

void SemaphoreManager::deinitialize()
{
    heap_ = NULLPTR;
}

} // namespace sys
} // namespace eoos
