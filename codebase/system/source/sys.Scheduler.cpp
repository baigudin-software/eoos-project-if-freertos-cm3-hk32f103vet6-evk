/**
 * @file      sys.Scheduler.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2017-2023, Sergey Baigudin, Baigudin Software
 */
#include "sys.Scheduler.hpp"
#include "lib.UniquePointer.hpp"

namespace eoos
{
namespace sys
{

api::Heap* Scheduler::heap_( NULLPTR );

Scheduler::Scheduler(api::CpuProcessor& cpu)
    : NonCopyable<NoAllocator>()
    , api::Scheduler()
    , isr_()
    , cpu_(cpu)
    , tim_(NULLPTR)
    , int_(NULLPTR)
    , mutex_()
    , memory_(mutex_) {
    bool_t const isConstructed( construct() );
    setConstructed( isConstructed );    
}

Scheduler::~Scheduler()
{
    Scheduler::deinitialize();
}

bool_t Scheduler::isConstructed() const
{
    return Parent::isConstructed();
}

api::Thread* Scheduler::createThread(api::Task& task)
{
    api::Thread* ptr( NULLPTR );
    if( isConstructed() )
    {
        lib::UniquePointer<api::Thread> res( new Thread<Scheduler>(task) );
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

bool_t Scheduler::sleep(int32_t ms)
{
    bool_t res( false );
    if( isConstructed() )
    {
        int32_t time( ms / 1000 );
        sSleep(time);
        time = ms % 1000;
        res = msSleep(time);
    }
    return res;
}

void Scheduler::yield()
{
    if( isConstructed() )
    {
//TODO        int_t const error( ::sched_yield() );
//TODO        if(error != 0)
//TODO        {   ///< UT Justified Branch: OS dependency
//TODO            setConstructed(false);
//TODO        }
    }
}

bool_t Scheduler::construct()
{
    bool_t res( false );
    do 
    {
        if( !isConstructed() )
        {
            break;
        }
        if( !isr_.isConstructed() )
        {
            break;
        }        
        if( !cpu_.isConstructed() )
        {
            break;
        }
        if( !memory_.isConstructed() )
        {
            break;
        }
        if( !Scheduler::initialize(&memory_) )
        {
            break;
        }
        res = true;
    } while(false);
    return res;
}

void Scheduler::sSleep(int32_t const s)
{
//TODO    uint_t sec( static_cast<uint_t>(s) );
//TODO    while(sec != 0U)
//TODO    {
//TODO        sec = ::sleep(sec);
//TODO    }
}    

bool_t Scheduler::msSleep(int32_t const ms)
{
    bool_t res( false );
    if( (0 < ms) && (ms < 1000) )
    {
//TODO        ::useconds_t const us( static_cast< ::useconds_t >(ms) * 1000U );
//TODO        int_t const error( ::usleep(us) );
//TODO        if(error == 0)
//TODO        {
//TODO            res = true;
//TODO        }
    }
    return res;
}

void* Scheduler::allocate(size_t size)
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

void Scheduler::free(void* ptr)
{
    if( heap_ != NULLPTR )
    {
        heap_->free(ptr);
    }
}

bool_t Scheduler::initialize(api::Heap* heap)
{
    bool_t res( false );
    do 
    {
        if( heap_ != NULLPTR )
        {
            break;
        }
        heap_ = heap;
        tim_ = cpu_.getTimerController().createResource(0);
        if( tim_ == NULLPTR || !tim_->isConstructed() )
        {
            break;
        }
        int32_t const source ( tim_->getInterrupSource() );
        int_ = cpu_.getInterruptController().createResource(isr_, source);
        if( int_ == NULLPTR || !int_->isConstructed() )
        {
            break;
        }
        if( !tim_->setPeriod(QUANT) )
        {
            break;
        }
        int_->enable();        
        tim_->start();
        res = true;
    } while(false);
    return res;    
}

void Scheduler::deinitialize()
{
    heap_ = NULLPTR;
    if(tim_ != NULLPTR)
    {
        delete tim_;
    }
    if(int_ != NULLPTR)
    {
        delete int_;
    }    
}

} // namespace sys
} // namespace eoos
