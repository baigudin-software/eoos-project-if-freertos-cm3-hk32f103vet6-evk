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
     * @enum Number
     * @brief USART numbers.
     */
    enum Number
    {
        NUMBER_USART1 = 0,
        NUMBER_USART2,
        NUMBER_USART3,
        NUMBER_UART4,
        NUMBER_UART5
    };

    /**
     * @enum Mode
     * @brief USART numbers.
     */
    enum Mode
    {
        MODE_RX   = 1,
        MODE_TX   = 2,
        MODE_TXRX = 3
    };

    /**
     * @enum Baud
     * @brief USART speed (rate) in Bauds.
     */
    enum Baud
    {
        BAUD_9600 = 9600
    };

    /**
     * @enum DataBits
     * @brief USART data bits.
     */
    enum DataBits
    {
        DATABITS_8 = 8,
        DATABITS_9 = 9
    };

    /**
     * @enum StopBits
     * @brief USART stop bits.
     */
    enum StopBits
    {
        STOPBITS_1 = 1,
        STOPBITS_2 = 2
    };
    
    /**
     * @enum Parity
     * @brief USART parity.
     */
    enum Parity
    {
        PARITY_NONE = 0,
        PARITY_ODD  = 1,
        PARITY_EVEN = 2,        
    };

    /**
     * @enum FlowControl
     * @brief USART flow control.
     */
    enum FlowControl
    {
        FLOWCONTROL_NONE = 0,
    };

    /**
     * @struct SerialLineConfig
     * @brief Configure USART as Serial Line.
     */    
    struct SerialLineConfig
    {
        Number      number;
        Mode        mode;
        Baud        speed;
        DataBits    dataBits;
        StopBits    stopBits;
        Parity      parity;
        FlowControl flowControl;
    };
    
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
