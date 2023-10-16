/**
 * @file      drv.Usart.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2023, Sergey Baigudin, Baigudin Software
 */
#ifndef DRV_USART_HPP_
#define DRV_USART_HPP_

#include "api.OutStream.hpp"

namespace eoos
{
namespace drv
{

/**
 * @class Usart
 * @brief Universal Synchronous Asynchronous Transceiver (USART) driver.
 */
class Usart : public api::OutStream<char_t>
{
public:
    
    /** 
     * @brief Destructor.
     */                               
    virtual ~Usart() = 0;

    /**
     * @brief Create the driver resource.
     *
     * @param number Number of USART or UART.
     * @return A new driver resource, or NULLPTR if an error has been occurred.
     */
    static Usart* create(int32_t number);

};

} // namespace drv
} // namespace eoos
#endif // DRV_USART_HPP_
