/**
 * @file      sys.SchedulerRoutine.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2017-2023, Sergey Baigudin, Baigudin Software
 */
#include "sys.SchedulerRoutine.hpp"

namespace eoos
{
namespace sys
{

SchedulerRoutine::SchedulerRoutine()
    : NonCopyable<NoAllocator>()
    , api::Task() {
    bool_t const isConstructed( construct() );
    setConstructed( isConstructed );    
}

SchedulerRoutine::~SchedulerRoutine()
{
}

bool_t SchedulerRoutine::isConstructed() const
{
    return Parent::isConstructed();
}

void SchedulerRoutine::start()
{
    // Called by the portable layer each time a tick interrupt occurs.
    // Increments the tick then checks to see if the new tick 
    // value will cause any tasks to be unblocked.
    ::BaseType_t xSwitchRequired( ::xTaskIncrementTick() );
    // Select the next task to execute
    if(xSwitchRequired == pdTRUE)
    {
        ::vTaskSwitchContext();
    }    
}

size_t SchedulerRoutine::getStackSize() const
{
    return 0;
}

bool_t SchedulerRoutine::construct()
{
    bool_t res( false );
    do 
    {
        if( !isConstructed() )
        {
            break;
        }
        res = true;
    } while(false);
    return res;
}

} // namespace sys
} // namespace eoos
