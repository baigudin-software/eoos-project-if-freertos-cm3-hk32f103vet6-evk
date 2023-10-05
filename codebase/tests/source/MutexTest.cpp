/**
 * @file      ThreadYieldTest.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2023, Sergey Baigudin, Baigudin Software
 *
 * @brief Tests of thread yield.
 */
#include "ThreadYieldTest.hpp"
#include "lib.Thread.hpp"
#include "lib.AbstractTask.hpp"
#include "lib.Mutex.hpp"
#include "lib.Guard.hpp"

namespace eoos
{
namespace
{

const int32_t MAX_COUNT(0x800000);
    
volatile int64_t resource_(0);
    
/**
 * @class CountUp
 * @brief Count up task.
 */
class CountUp : public lib::AbstractTask<>
{

public:
    
    /**
     * @brief Constructor.
     *
     * @param mutex Mutex resource to lock on.
     */    
    CountUp(api::Mutex& mutex)
        : lib::AbstractTask<>()
        , isCompleted_( false )
        , mutex_(mutex) {
    }
    
    /**
     * @brief Test if counting is completed.
     *
     * @return True ii completed.
     */
    bool_t isCompleted()
    {
        return isCompleted_;
    }
        
private:

    /**
     * @copydoc eoos::api::Task::start()
     */
    virtual void start()
    {
        {
            lib::Guard<> guard(mutex_);
            volatile int64_t resource( resource_ );
            for(int32_t i(0); i<=MAX_COUNT; i++)
            {
                resource = i;
            }
            resource_ = resource;
        }
        isCompleted_ = true;
        while(true){}
    }

    /**
     * @brief Complete flag.
     */
    bool_t isCompleted_;

    /**
     * @brief Mutex resource to lock on.
     */
    api::Mutex& mutex_;

};

/**
 * @class CountDw
 * @brief Count down task.
 */
class CountDw : public lib::AbstractTask<>
{

public:
    
    /**
     * @brief Constructor.
     *
     * @param mutex Mutex resource to lock on.
     */
    CountDw(api::Mutex& mutex)
        : lib::AbstractTask<>()
        , isCompleted_( false )
        , mutex_(mutex) {
    }
    
    /**
     * @brief Test if counting is completed.
     *
     * @return True ii completed.
     */    
    bool_t isCompleted()
    {
        return isCompleted_;
    }
        
private:

    /**
     * @copydoc eoos::api::Task::start()
     */
    virtual void start()
    {
        {
            lib::Guard<> guard(mutex_);
            volatile int64_t resource( resource_ );
            for(int32_t i(MAX_COUNT); i>=0; i--)
            {
                resource = i;
            }
            resource_ = resource;
        }
        isCompleted_ = true;
        while(true){}
    }
    
    /**
     * @brief Complete flag.
     */
    bool_t isCompleted_;

    /**
     * @brief Mutex resource to lock on.
     */
    api::Mutex& mutex_;

};

} // namespace

void testMutex()
{
    lib::Mutex<> mutex;
    CountUp taskUp(mutex);
    CountDw taskDw(mutex);
    lib::Thread<> threadUp(taskUp);   
    lib::Thread<> threadDw(taskDw);
    threadUp.execute();
    threadDw.execute();
    while(true)
    {
        bool_t isCompleted = true;
        isCompleted &= taskUp.isCompleted();
        isCompleted &= taskDw.isCompleted();
        if(isCompleted)
        {
            break;
        }
    }
    if(resource_ == 0)
    {
        // Success
        while(true){}
    }
    else
    {
        // Failure
        while(true){}
    }
}

} // namespace eoos
