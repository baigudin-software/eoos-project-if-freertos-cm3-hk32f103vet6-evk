/**
 * @file      sys.MutexManager.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2023, Sergey Baigudin, Baigudin Software
 */
#include "sys.MutexManager.hpp"
#include "lib.UniquePointer.hpp"

namespace eoos
{
namespace sys
{

api::Heap* MutexManager::heap_( NULLPTR );

MutexManager::MutexManager() 
    : NonCopyable<NoAllocator>()
    , api::MutexManager()
    , mutex_()
    , memory_(mutex_) {
    bool_t const isConstructed( construct() );
    setConstructed( isConstructed );
}

MutexManager::~MutexManager()
{
    MutexManager::deinitialize();    
}

bool_t MutexManager::isConstructed() const
{
    return Parent::isConstructed();
}

api::Mutex* MutexManager::create()
{
    api::Mutex* ptr( NULLPTR );
    if( isConstructed() )
    {
        lib::UniquePointer<api::Mutex> res( new Mutex<MutexManager>() );
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

bool_t MutexManager::construct()
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
        if( !MutexManager::initialize(&memory_) )
        {
            break;
        }
        res = true;
    } while(false);
    return res;
}

void* MutexManager::allocate(size_t size)
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

void MutexManager::free(void* ptr)
{
    if( heap_ != NULLPTR )
    {
        heap_->free(ptr);
    }
}

bool_t MutexManager::initialize(api::Heap* heap)
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

void MutexManager::deinitialize()
{
    heap_ = NULLPTR;
}

} // namespace sys
} // namespace eoos
