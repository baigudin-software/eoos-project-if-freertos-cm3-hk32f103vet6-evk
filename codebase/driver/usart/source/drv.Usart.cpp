/**
 * @file      drv.Usart.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2023, Sergey Baigudin, Baigudin Software
 */
#include "drv.Usart.hpp"
#include "drv.UsartController.hpp"
#include "lib.UniquePointer.hpp"

namespace eoos
{
namespace drv
{
    
Usart* Usart::create(int32_t number)
{
    static UsartController* controller( NULLPTR );    
    if( controller == NULLPTR )
    {
        controller = new UsartController;
        if( controller == NULLPTR )
        {
            return NULLPTR;
        }
        if( !controller->isConstructed() )
        {
            delete controller;
            controller = NULLPTR;
            return NULLPTR;
        }
    }
    lib::UniquePointer<Usart> res( controller->createResource(number) );
    if( !res.isNull() )
    {
        if( !res->isConstructed() )
        {
            res.reset();
        }
    }
    return res.release();
}

Usart::~Usart(){}

} // namespace drv
} // namespace eoos
