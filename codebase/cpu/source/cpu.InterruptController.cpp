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
    
/**
 * @brief Jumps to the exception handler.
 *
 * @param exception Exception number.
 * @note The function relies the exception argument is valid, as
 *       it has ASM implementation and difficulty to check the argument.
 */
extern "C" void CpuInterruptController_jumpUsrLow(int32_t exception);

/**
 * @brief Jumps to the SVCall exception handler.
 *
 * @param exception Exception number.
 * @note The function relies the exception argument is valid, as
 *       it has ASM implementation and difficulty to check the argument.
 */
extern "C" void CpuInterruptController_jumpSvcLow(int32_t exception);

/**
 * @brief Handles exceptions.
 *
 * @param exception Exception number.
 */
extern "C" void CpuInterruptController_handleException(int32_t exception)
{
    InterruptController::handleException(exception);
}

    
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

void InterruptController::jump(int32_t exception)
{
    if( !Interrupt<InterruptController>::isException(exception) )
    {
        return;
    }
    if( exception == getNumberSupervisor() )
    {
        CpuInterruptController_jumpSvcLow(exception);
    }
    else
    {
        CpuInterruptController_jumpUsrLow(exception);
    }
}

int32_t InterruptController::getNumberSystick() const
{
    return Interrupt<InterruptController>::EXCEPTION_SYSTICK;
}

int32_t InterruptController::getNumberSupervisor() const
{
    return Interrupt<InterruptController>::EXCEPTION_SVCALL;
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
    #ifdef EOOS_DEBUG_MODE
    // As soon as ISR must be as fast as possible, do these checkes only in debug mode.
    if( this_ == NULLPTR )
    {
        return;
    }
    if( !Interrupt<InterruptController>::isException(exception) )
    {
        return;
    }
    if( this_->data_.handlers[exception] == NULLPTR )
    {
        return;
    }
    #endif // EOOS_DEBUG_MODE
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
    
} // namespace cpu
} // namespace eoos
