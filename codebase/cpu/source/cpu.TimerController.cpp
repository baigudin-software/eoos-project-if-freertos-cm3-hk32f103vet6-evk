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
    
api::Heap* TimerController::resource_( NULLPTR );

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
    if( index == Resource::INDEX_SYSTICK )
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
        lib::UniquePointer<api::CpuTimer> res( new Resource(data_) );
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

int32_t TimerController::getNumberSystick() const
{
    return Resource::INDEX_SYSTICK;
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
    if( resource_ != NULLPTR )
    {
        return resource_->allocate(size, NULLPTR);
    }
    else
    {
        return NULLPTR;
    }
}

void TimerController::free(void* ptr)
{
    if( resource_ != NULLPTR )
    {
        resource_->free(ptr);
    }
}

bool_t TimerController::initialize(api::Heap* resource)
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

void TimerController::deinitialize()
{
    resource_ = NULLPTR;
}

} // namespace cpu
} // namespace eoos
