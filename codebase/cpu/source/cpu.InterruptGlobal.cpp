/**
 * @file      cpu.InterruptGlobal.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2016-2023, Sergey Baigudin, Baigudin Software
 */ 
#include "cpu.InterruptGlobal.hpp"

extern "C"
{

/**
 * @brief Sets PRIMASK to 1 raises the execution priority to 0.
 *
 * @return Value of PRIMASK bit before the function called.
 */
extern bool CpuInterruptGlobal_disable();

/**
 * @brief Sets PRIMASK to 0 raises the execution priority to base level.
 */
extern void CpuInterruptGlobal_enable();

}


namespace eoos
{
namespace cpu
{

InterruptGlobal::InterruptGlobal()
    : NonCopyable<NoAllocator>()
    , api::Guard() {    
    bool_t const isConstructed( construct() );
    setConstructed( isConstructed );
}

InterruptGlobal::~InterruptGlobal()
{
}

bool_t InterruptGlobal::isConstructed() const
{
    return Parent::isConstructed();  
}
    
bool_t InterruptGlobal::lock()
{
    return !::CpuInterruptGlobal_disable();
}

void InterruptGlobal::unlock()
{
    ::CpuInterruptGlobal_enable();
}

bool_t InterruptGlobal::construct()
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
    
} // namespace cpu
} // namespace eoos
