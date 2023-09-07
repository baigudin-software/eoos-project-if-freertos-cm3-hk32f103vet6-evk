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
