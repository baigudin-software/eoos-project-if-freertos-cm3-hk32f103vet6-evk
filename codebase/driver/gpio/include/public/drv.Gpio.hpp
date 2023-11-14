/**
 * @file      drv.Gpio.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2023, Sergey Baigudin, Baigudin Software
 */
#ifndef DRV_GPIO_HPP_
#define DRV_GPIO_HPP_

#include "api.Object.hpp"

namespace eoos
{
namespace drv
{

/**
 * @class Gpio
 * @brief GPIO driver.
 */
class Gpio : public api::Object
{
public:

    /**
     * @enum Mode
     * @brief GPIO direction mode.
     */
    enum Mode
    {
        MODE_INPUT        = 0,
        MODE_OUTPUT_10MHZ = 1,
        MODE_OUTPUT_2MHZ  = 2,
        MODE_OUTPUT_50MHZ = 3        
    };

    /**
     * @enum ModeInput
     * @brief GPIO input mode.
     */
    enum ModeInput
    {
        MODEINPUT_ANALOG          = 0,
        MODEINPUT_FLOATING        = 1,
        MODEINPUT_PULLUP_PULLDOWN = 2
    };

    /**
     * @enum ModeOutput
     * @brief GPIO output mode.
     */
    enum ModeOutput
    {
        MODEOUTPUT_PUSH_PULL  = 0,
        MODEOUTPUT_OPEN_DRAIN = 1
    };

    /**
     * @union ModeDirection
     * @brief GPIO direction mode.
     *
     * @note A GPIO pin can be either input or output configured, thus such union is relevant here.
     */
    union ModeDirection
    {
        ModeInput  input;
        ModeOutput output; 
    };

    /**
     * @enum PortNumber
     * @brief GPIO port numbers.
     */
    enum PortNumber
    {
        PORTNUMBER_A = 0,
        PORTNUMBER_B = 1,
        PORTNUMBER_C = 2,
        PORTNUMBER_D = 3,
        PORTNUMBER_E = 4        
    };

    /**
     * @enum GpioNumber
     * @brief Pin numbers.
     */
    enum GpioNumber
    {
        GPIONUMBER_0  = 0,
        GPIONUMBER_1  = 1,
        GPIONUMBER_2  = 2,
        GPIONUMBER_3  = 3,
        GPIONUMBER_4  = 4,
        GPIONUMBER_5  = 5,
        GPIONUMBER_6  = 6,
        GPIONUMBER_7  = 7,
        GPIONUMBER_8  = 8,
        GPIONUMBER_9  = 9,
        GPIONUMBER_10 = 10,
        GPIONUMBER_11 = 11,
        GPIONUMBER_12 = 12,
        GPIONUMBER_13 = 13,
        GPIONUMBER_14 = 14,
        GPIONUMBER_15 = 15
    };    

    /**
     * @struct Config
     * @brief Configure GPIO driver resource.
     */    
    struct Config
    {
        Mode          mode;
        ModeDirection direction;
        PortNumber    port;
        GpioNumber    gpio;
    };
    
    /** 
     * @brief Destructor.
     */                               
    virtual ~Gpio() = 0;

    /**
     * @brief Pulls GPIO pin up.
     */                               
    virtual void pullUp() = 0;

    /**
     * @brief Pulls GPIO pin down.
     */                               
    virtual void pullDown() = 0;

    /**
     * @brief Test if GPIO pin is pulled up.
     *
     * @return True is the pin pulled up.
     */                               
    virtual bool_t isPullUp() const = 0;

    /**
     * @brief Test if GPIO pin is pulled down.
     *
     * @return True is the pin pulled down.     
     */                               
    virtual bool_t isPullDown() const = 0;

    /**
     * @brief Create the driver resource.
     *
     * @param config Configuration of the driver resource.
     * @return A new driver resource, or NULLPTR if an error has been occurred.
     */
    static Gpio* create(Config const& config);

};

} // namespace drv
} // namespace eoos
#endif // DRV_GPIO_HPP_
