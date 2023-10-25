/**
 * @file      MutexTest.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2023, Sergey Baigudin, Baigudin Software
 *
 * @brief Tests of thread yield.
 */
#include "MutexTest.hpp"
#include "lib.AbstractThreadTask.hpp"
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
 * @brief Count up thread`.
 */
class CountUp : public lib::AbstractThreadTask<>
{

public:
    
    /**
     * @brief Constructor.
     *
     * @param mutex Mutex resource to lock on.
     */    
    CountUp(api::Mutex& mutex)
        : lib::AbstractThreadTask<>()
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
            lib::Guard<> const guard(mutex_);
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
class CountDw : public lib::AbstractThreadTask<>
{

public:
    
    /**
     * @brief Constructor.
     *
     * @param mutex Mutex resource to lock on.
     */
    CountDw(api::Mutex& mutex)
        : lib::AbstractThreadTask<>()
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
            lib::Guard<> const guard(mutex_);
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
    CountUp countUp(mutex);
    CountDw countDw(mutex);
    countUp.execute();
    countDw.execute();
    while(true)
    {
        bool_t isCompleted = true;
        isCompleted &= countUp.isCompleted();
        isCompleted &= countDw.isCompleted();
        if(isCompleted)
        {
            break;
        }
    }
    if(resource_ != 0)
    {   // Failure
        while(true){}
    }
    // Success
    while(true){}    
}

} // namespace eoos
