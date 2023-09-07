/**
 * @file      api.Guard.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2023, Sergey Baigudin, Baigudin Software
 */
#ifndef API_GUARD_HPP_
#define API_GUARD_HPP_

#include "api.Object.hpp"

namespace eoos
{
namespace api
{

/**
 * @class Guard
 * @brief Guard interface.
 */    
class Guard : public Object
{

public:

    /**
     * @brief Destructor.
     */
    virtual ~Guard() = 0;

    /**
     * @brief Locks this guard.
     *
     * @return True if this guard is locked successfully, or false if an error occurred.
     */
    virtual bool_t lock() = 0;

    /**
     * @brief Unlocks this guard.
     */
    virtual void unlock() = 0;

};

inline Guard::~Guard() {}

} // namespace api
} // namespace eoos
#endif // API_GUARD_HPP_
