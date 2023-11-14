/**
 * @file      drv.Null.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2023, Sergey Baigudin, Baigudin Software
 */
#ifndef DRV_NULL_HPP_
#define DRV_NULL_HPP_

#include "api.OutStream.hpp"

namespace eoos
{
namespace drv
{

/**
 * @class Null
 * @brief Unknown device driver.
 */
class Null : public api::OutStream<char_t>
{
public:

    /**
     * @enum Number
     * @brief NULL numbers.
     */
    enum Number
    {
        NUMBER_NULL0 = 0
    };

    /**
     * @struct Config
     * @brief Configure Null driver resource.
     */    
    struct Config
    {
        Number number;
    };
    
    /** 
     * @brief Destructor.
     */                               
    virtual ~Null() = 0;

    /**
     * @brief Create the driver resource.
     *
     * @param config Configuration of the driver resource.
     * @return A new driver resource, or NULLPTR if an error has been occurred.
     */
    static Null* create(Config const& config);

};

} // namespace drv
} // namespace eoos
#endif // DRV_NULL_HPP_
