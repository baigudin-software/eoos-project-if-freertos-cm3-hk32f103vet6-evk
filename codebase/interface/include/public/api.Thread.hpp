/**
 * @file      api.Thread.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2014-2022, Sergey Baigudin, Baigudin Software
 */
#ifndef API_THREAD_HPP_
#define API_THREAD_HPP_

#include "api.Object.hpp"

namespace eoos
{
namespace api
{
    
/**
 * @class Thread
 * @brief Thread interface.
 */
class Thread : public Object
{

public:
    
    /**
     * @brief Wrong thead priority.
     */
    static const int32_t PRIORITY_WRONG = -1;     

    /**
     * @brief Maximum thead priority.
     */
    static const int32_t PRIORITY_MAX = 10;

    /**
     * @brief Minimum thead priority.
     */
    static const int32_t PRIORITY_MIN = 1;

    /**
     * @brief Normal thead priority.
     */
    static const int32_t PRIORITY_NORM = 5;

    /**
     * @brief Thead locked on executing priority.
     */
    static const int32_t PRIORITY_LOCK  = 0;

    /**
     * @enum Status
     * @brief Thread available statuses.
     *
     * Thread status state machine:
     *   |-- On any error of creation -->|
     * (NEW)->(RUNNABLE)<->(RUNNING)->(DEAD)
     *           |<-(SLEEPING)<-|
     *           |<-(BLOCKED) <-|
     *
     * @todo Currently there is no function to get a thread status for OS, as statuses 
     *       of different OSs are different, and we need to align them to this.
     */
    enum Status
    {
        STATUS_NEW      = 0, //< Thread is constructed
        STATUS_RUNNABLE = 1, //< Thread is set with execute()
        STATUS_RUNNING  = 2, //< Thread is run
        STATUS_BLOCKED  = 4, //< Thread is blocked on a resource
        STATUS_SLEEPING = 5, //< Thread is sleeping on a resource
        STATUS_DEAD     = 6  //< Thread is dead because it finished execution
    };  

    /**
     * @brief Destructor.
     */
    virtual ~Thread() = 0;

    /**
     * @brief Causes this thread to begin execution.
     *
     * @return True if execution of the thread initiated successfully.     
     */
    virtual bool_t execute() = 0;

    /**
     * @brief Waits for this thread to die.
     *
     * @return True, if this thread is dead.
     */
    virtual bool_t join() = 0;

    /**
     * @brief Returns this thread priority.
     *
     * @return Priority value, or PRIORITY_WRONG if an error has been occurred.
     */
    virtual int32_t getPriority() const = 0;

    /**
     * @brief Sets this thread priority.
     *
     * @param priority Number of priority in range [PRIORITY_MIN, PRIORITY_MAX], or PRIORITY_LOCK.
     * @return True if priority is set.
     */
    virtual bool_t setPriority(int32_t priority) = 0;
    
};

inline Thread::~Thread() {}
        
} // namespace api
} // namespace eoos
#endif // API_THREAD_HPP_
