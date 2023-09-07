/**
 * @file      cpu.InterruptController.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2019-2023, Sergey Baigudin, Baigudin Software
 */ 
#include "cpu.InterruptController.hpp"
#include "lib.UniquePointer.hpp"

namespace eoos
{
namespace cpu
{
    
api::Heap* InterruptController::heap_( NULLPTR );

InterruptController* InterruptController::this_( NULLPTR );

InterruptController::InterruptController(Registers& reg, api::Guard& gie)
    : NonCopyable<NoAllocator>()
    , api::CpuInterruptController()
    , reg_(reg)
    , gie_(gie)
    , memory_(gie_)
    , data_(reg_, gie_) {
    bool_t const isConstructed( construct() );
    setConstructed( isConstructed );
}

InterruptController::~InterruptController()
{
    InterruptController::deinitialize();
}

bool_t InterruptController::isConstructed() const
{
    return Parent::isConstructed();
}
    
api::CpuInterrupt* InterruptController::createResource(api::Task& handler, int32_t source)
{
    api::CpuInterrupt* ptr( NULLPTR );
    if( isConstructed() )
    {
        lib::UniquePointer<api::CpuInterrupt> res( new Interrupt<InterruptController>(data_, handler, source) );
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

api::Guard& InterruptController::getGlobal()
{
    return gie_;
}

bool_t InterruptController::construct()
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

void* InterruptController::allocate(size_t size)
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

void InterruptController::free(void* ptr)
{
    if( heap_ != NULLPTR )
    {
        heap_->free(ptr);
    }
}

void InterruptController::handleException(int32_t exception)
{
    if( this_ == NULLPTR )
    {
        return;
    }
    if( exception >= Interrupt<InterruptController>::EXCEPTION_LAST )
    {
        return;
    }
    if( this_->data_.handlers[exception] == NULLPTR )
    {
        return;
    }
    this_->data_.handlers[exception]->start();
}

bool_t InterruptController::initialize(api::Heap* heap)
{
    if( heap_ != NULLPTR || this_ != NULLPTR) 
    {
        return false;
    }
    heap_ = heap;
    this_ = this;
    return true;
}

void InterruptController::deinitialize()
{
    heap_ = NULLPTR;
    this_ = NULLPTR;
}

extern "C"
{

/**
 * @brief Handles exceptions.
 *
 * @param exception Exception number.
 */
void CpuInterruptController_handleException(int32_t exception)
{
    InterruptController::handleException(exception);
}

}
    
} // namespace cpu
} // namespace eoos
