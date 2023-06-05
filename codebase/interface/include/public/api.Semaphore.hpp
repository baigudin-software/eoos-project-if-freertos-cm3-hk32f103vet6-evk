/**
 * @file      api.Semaphore.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2015-2022, Sergey Baigudin, Baigudin Software
 */
#ifndef API_SEMAPHORE_HPP_
#define API_SEMAPHORE_HPP_

#include "api.Object.hpp"

namespace eoos
{
namespace api
{

/**
 * @class Semaphore
 * @brief Semaphore interface.
 */
class Semaphore : public Object
{

public:

    /**
     * @brief Destructor.
     */
    virtual ~Semaphore() = 0;

    /**
     * @brief Acquires one permit from this semaphore.
     *
     * The function acquires one permit or waits
     * while the permit will be released.
     *
     * @return True if the semaphore is acquired successfully.
     */
    virtual bool_t acquire() = 0;

    /**
     * @brief Releases one permit.
     *
     * The function releases from one permit and returns this to the semaphore.
     */
    virtual void release() = 0;

};
        
inline Semaphore::~Semaphore() {}

} // namespace api
} // namespace eoos
#endif // API_SEMAPHORE_HPP_
