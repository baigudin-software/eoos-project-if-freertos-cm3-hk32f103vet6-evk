/**
 * @file      cpu.Processor.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2019-2023, Sergey Baigudin, Baigudin Software
 */
#include "cpu.Processor.hpp"

namespace eoos
{
namespace cpu
{

/**
 * @brief Starts a first task.
 *
 * The function does not return control to a calling function.
 */              
extern "C" void CpuBoot_startFirstTask(void);

Processor::Processor()
    : NonCopyable<NoAllocator>()
    , api::CpuProcessor()
    , reg_()
    , gie_()
    , pll_(reg_, gie_)
    , int_(reg_, gie_) 
    , tim_(reg_, gie_) {
    bool_t const isConstructed( construct() );
    setConstructed( isConstructed );
}    

Processor::~Processor()
{
}

bool_t Processor::isConstructed() const
{
    return Parent::isConstructed();
}

void Processor::bootPrimaryThread()
{
    CpuBoot_startFirstTask();
}

const char_t* Processor::getName() const
{
    return "HK32F103xCxDxE";
}

int32_t Processor::getCoreId() const
{
    return 0;
}

api::CpuPllController& Processor::getPllController()
{
    return pll_;
}

api::CpuInterruptController& Processor::getInterruptController()
{
    return int_;
}

api::CpuTimerController& Processor::getTimerController()
{
    return tim_;
}

bool_t Processor::construct()
{
    bool_t res( false );
    do 
    {
        if( !isConstructed() )
        {
            break;
        }
        if( !pll_.isConstructed() )
        {
            break;
        }        
        if( !int_.isConstructed() )
        {
            break;
        }
        res = true;
    } while(false);    
    return res; 
}

} // namespace cpu
} // namespace eoos
