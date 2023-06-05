/**
 * @file      api.SemaphoreManager.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2023, Sergey Baigudin, Baigudin Software
 */
#ifndef API_SEMAPHOREMANAGER_HPP_
#define API_SEMAPHOREMANAGER_HPP_

#include "api.Object.hpp"
#include "api.Semaphore.hpp"

namespace eoos
{
namespace api
{

/**
 * @class SemaphoreManager
 * @brief Semaphore sub-system manager interface.
 */    
class SemaphoreManager : public Object
{

public:

    /**
     * @brief Destructor.
     */
    virtual ~SemaphoreManager() = 0;

    /**
     * @brief Creates a new semaphore resource.
     *
     * @param permits The initial number of permits available.
     * @return A new semaphore resource, or NULLPTR if an error has been occurred.
     */
    virtual Semaphore* create(int32_t permits) = 0;

    /**
     * @brief Removes a new semaphore resource.
     *
     * @param semaphore A created semaphore resource.
     */     
    virtual void remove(Semaphore* semaphore) = 0;
    
};

inline SemaphoreManager::~SemaphoreManager() {}

} // namespace api
} // namespace eoos
#endif // API_SEMAPHOREMANAGER_HPP_
