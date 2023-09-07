/**
 * @file      cpu.TimerController.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2019-2023, Sergey Baigudin, Baigudin Software
 */  
#include "cpu.TimerController.hpp"
#include "lib.UniquePointer.hpp"

namespace eoos
{
namespace cpu
{
    
api::Heap* TimerController::heap_( NULLPTR );

TimerController::TimerController(Registers& reg, api::Guard& gie)
    : NonCopyable<NoAllocator>()
    , api::CpuTimerController()
    , reg_(reg)
    , gie_(gie)
    , memory_(gie_)
    , data_(reg_, gie_) {        
    bool_t const isConstructed( construct() );
    setConstructed( isConstructed );
}

TimerController::~TimerController()
{
    TimerController::deinitialize();
}

bool_t TimerController::isConstructed() const
{
    return Parent::isConstructed();
}

api::CpuTimer* TimerController::createResource(int32_t index)
{
    api::CpuTimer* res( NULLPTR );
    if( index == TimerSystem<TimerController>::INDEX_SYSTICK )
    {
        // @todo Test if the System Timer is already created.
        // By now this promlem is solved only by defining 
        // EOOS_CPU_GLOBAL_NUMBER_OF_SYSTEM_TIMERS to 1.
        res = createResourceTimerSystem();
    }
    return res;
}

api::CpuTimer* TimerController::createResourceTimerSystem()
{
    api::CpuTimer* ptr( NULLPTR );
    if( isConstructed() )
    {
        lib::UniquePointer<api::CpuTimer> res( new TimerSystem<TimerController>(data_) );
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

bool_t TimerController::construct()
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

void* TimerController::allocate(size_t size)
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

void TimerController::free(void* ptr)
{
    if( heap_ != NULLPTR )
    {
        heap_->free(ptr);
    }
}

bool_t TimerController::initialize(api::Heap* heap)
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

void TimerController::deinitialize()
{
    heap_ = NULLPTR;
}

} // namespace cpu
} // namespace eoos
