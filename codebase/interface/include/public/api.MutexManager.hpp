/**
 * @file      api.MutexManager.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2023, Sergey Baigudin, Baigudin Software
 */
#ifndef API_MUTEXMANAGER_HPP_
#define API_MUTEXMANAGER_HPP_

#include "api.Object.hpp"
#include "api.Mutex.hpp"

namespace eoos
{
namespace api
{

/**
 * @class MutexManager
 * @brief Mutex sub-system manager interface.
 */    
class MutexManager : public Object
{

public:

    /**
     * @brief Destructor.
     */
    virtual ~MutexManager() = 0;

    /**
     * @brief Creates a new mutex resource.
     *
     * @return A new mutex resource, or NULLPTR if an error has been occurred.
     */
    virtual Mutex* create() = 0;

    /**
     * @brief Removes a new mutex resource.
     *
     * @param mutex A created mutex resource.
     */
    virtual void remove(Mutex* mutex) = 0;
    
};

inline MutexManager::~MutexManager() {}

} // namespace api
} // namespace eoos
#endif // API_MUTEXMANAGER_HPP_
