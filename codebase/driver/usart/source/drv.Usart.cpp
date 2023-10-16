/**
 * @file      drv.Usart.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2023, Sergey Baigudin, Baigudin Software
 */
#include "drv.Usart.hpp"
#include "drv.UsartController.hpp"

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
    }
    return controller->createResource(number);
}

Usart::~Usart(){}

} // namespace drv
} // namespace eoos
