/**
 * @file      api.Mutex.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2015-2023, Sergey Baigudin, Baigudin Software
 */
#ifndef API_MUTEX_HPP_
#define API_MUTEX_HPP_

#include "api.Guard.hpp"

namespace eoos
{
namespace api
{

/**
 * @class Mutex
 * @brief Mutex interface.
 */    
class Mutex : public Guard
{

public:

    /**
     * @brief Destructor.
     */
    virtual ~Mutex() = 0;
    
    /**
     * @brief Tries to locks this mutex.
     *
     * @return True if this mutex is locked successfully, or false if other thread locked on this mutex.
     */
    virtual bool_t tryLock() = 0;

};

inline Mutex::~Mutex() {}

} // namespace api
} // namespace eoos
#endif // API_MUTEX_HPP_
