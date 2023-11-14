/**
 * @file      drv.Null.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2023, Sergey Baigudin, Baigudin Software
 */
#include "drv.Null.hpp"
#include "drv.NullController.hpp"
#include "lib.UniquePointer.hpp"

namespace eoos
{
namespace drv
{
    
static NullController* getController()
{
    static NullController* controller( NULLPTR );    
    if( controller == NULLPTR )
    {
        controller = new NullController;
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
    
Null* Null::create(Config const& config)
{
    NullController* const controller( getController() );    
    lib::UniquePointer<Null> res( controller->createResource(config) );
    if( !res.isNull() )
    {
        if( !res->isConstructed() )
        {
            res.reset();
        }
    }
    return res.release();
}

Null::~Null(){}

} // namespace drv
} // namespace eoos
