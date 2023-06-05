/**
 * @file      api.System.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2017-2023, Sergey Baigudin, Baigudin Software
 */
#ifndef API_SYSTEM_HPP_
#define API_SYSTEM_HPP_

#include "api.Object.hpp"
#include "api.Scheduler.hpp"
#include "api.Heap.hpp"
#include "api.MutexManager.hpp"
#include "api.SemaphoreManager.hpp"
#include "api.StreamManager.hpp"

namespace eoos
{
namespace api
{

/**
 * @class System
 * @brief The operating system syscall interface.
 */
class System : public Object
{

public:

    /**
     * @brief Returns the system heap memory.
     *
     * @return The system heap memory.
     */
    virtual Heap& getHeap() = 0;

    /**
     * @brief Returns the system scheduler.
     *
     * @return The system scheduler.
     */
    virtual Scheduler& getScheduler() = 0;

    /**
     * @brief Test if system has the mutex manager.
     *
     * @return True if system has the mutex manager.
     */
    virtual bool_t hasMutexManager() = 0;

    /**
     * @brief Returns mutex sub-system.
     *
     * @return The mutex sub-system.
     */
    virtual MutexManager& getMutexManager() = 0;

    /**
     * @brief Test if system has the semaphore manager.
     *
     * @return True if system has the semaphore manager.
     */
    virtual bool_t hasSemaphoreManager() = 0;

    /**
     * @brief Returns semaphore sub-system.
     *
     * @return The semaphore sub-system.
     */
    virtual SemaphoreManager& getSemaphoreManager() = 0;

    /**
     * @brief Test if system has the stream manager.
     *
     * @return True if system has the stream manager.
     */
    virtual bool_t hasStreamManager() = 0;

    /**
     * @brief Returns stream sub-system.
     *
     * @return The stream sub-system.
     */
    virtual StreamManager& getStreamManager() = 0;
    
protected:

    /**
     * @brief Destructor.
     */
    virtual ~System() = 0;

};

inline System::~System() {}

} // namespace api
} // namespace eoos
#endif // API_SYSTEM_HPP_
