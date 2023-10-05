/**
 * @file      cpu.RegistersController.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2019-2023, Sergey Baigudin, Baigudin Software
 */ 
#include "cpu.RegistersController.hpp"
#include "lib.UniquePointer.hpp"

namespace eoos
{
namespace cpu
{
    
RegistersController::RegistersController(Registers& reg, api::Guard& gie)
    : NonCopyable<NoAllocator>()
    , api::CpuRegistersController()
    , reg_(reg)
    , gie_(gie) {
    bool_t const isConstructed( construct() );
    setConstructed( isConstructed );
}

RegistersController::~RegistersController()
{
}

bool_t RegistersController::isConstructed() const
{
    return Parent::isConstructed();
}

void* RegistersController::initializeStack(void* stack, void* entry, void* exit, int32_t argument)
{
    static stack_t id = 0;
    if(id > 0xFF)
    {
        id = 0;
    }
    id += 1;
    // Align SP on 8
    stack_t* sp( reinterpret_cast<stack_t*>( reinterpret_cast<uint32_t>(stack) & ~0x7UL ) );
    stack_t xPSR = 0x01000000UL;
    *--sp = xPSR;                               // xPSR
    *--sp = reinterpret_cast<stack_t>(entry);   // R15(PC)
    *--sp = reinterpret_cast<stack_t>(exit);    // R14(LR)
    *--sp = 0xCCCCCC00 | id;                    // R12
    *--sp = 0x33333300 | id;                    // R3
    *--sp = 0x22222200 | id;                    // R2
    *--sp = 0x11111100 | id;                    // R1
    *--sp = static_cast<stack_t>(argument);     // R0
    *--sp = 0xBBBBBB00 | id;                    // R11
    *--sp = 0xAAAAAA00 | id;                    // R10
    *--sp = 0x99999900 | id;                    // R9
    *--sp = 0x88888800 | id;                    // R8
    *--sp = 0x77777700 | id;                    // R7
    *--sp = 0x66666600 | id;                    // R6
    *--sp = 0x55555500 | id;                    // R5
	*--sp = 0x44444400 | id;                    // R4
    return sp;
}

bool_t RegistersController::construct()
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
