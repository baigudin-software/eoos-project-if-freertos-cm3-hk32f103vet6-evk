/**
 * @file      port.hpp
 * @brief     Universal EOOS port of FreeRTOS Kernel V10.5.1 (V202212.01)
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2023, Sergey Baigudin, Baigudin Software
 */
#ifndef PORT_HPP_
#define PORT_HPP_

#include "api.SystemPort.hpp"

namespace eoos
{
    
class Kernel
{

public:

    /**
     * @brief Causes to execute FeeRTOS kernel.
     *
     * @param eoos EOOS system port.
     */
    static void execute(api::SystemPort& port);

};

} // namespace eoos

#endif // KNL_PORT_HPP_
