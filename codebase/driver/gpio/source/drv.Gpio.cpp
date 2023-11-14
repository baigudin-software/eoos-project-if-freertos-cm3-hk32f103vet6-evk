/**
 * @file      drv.Gpio.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2023, Sergey Baigudin, Baigudin Software
 */
#include "drv.Gpio.hpp"
#include "drv.GpioController.hpp"
#include "lib.UniquePointer.hpp"

namespace eoos
{
namespace drv
{

static GpioController* getController()
{
    static GpioController* controller( NULLPTR );    
    if( controller == NULLPTR )
    {
        controller = new GpioController;
        if( controller != NULLPTR )
        {
            if( !controller->isConstructed() )
            {
                delete controller;
                controller = NULLPTR;                
            }
        }
    }
    return controller;
}
    
Gpio* Gpio::create(Config const& config)
{
    GpioController* const controller( getController() );    
    lib::UniquePointer<Gpio> res( controller->createResource(config) );
    if( !res.isNull() )
    {
        if( !res->isConstructed() )
        {
            res.reset();
        }
    }
    return res.release();
}

Gpio::~Gpio(){}

} // namespace drv
} // namespace eoos
