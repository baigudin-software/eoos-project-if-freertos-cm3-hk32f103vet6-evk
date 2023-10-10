/**
 * @file      SemaphoreTest.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2023, Sergey Baigudin, Baigudin Software
 *
 * @brief Tests of thread yield.
 */
#include "SemaphoreTest.hpp"
#include "lib.AbstractThreadTask.hpp"
#include "lib.Semaphore.hpp"

namespace eoos
{
namespace
{

const int32_t MAX_WAIT_COUNT(0x800000);
    
/**
 * @class Task
 * @brief Semaphore task for the test.
 */
class ThreadTask : public lib::AbstractThreadTask<>
{
    typedef AbstractThreadTask<> Parent;

public:
    
    /**
     * @brief Constructor.
     *
     * @param semAcquire Semaphore to acquire in the thread.
     * @param semRelease Semaphore to release in the thread after the acquirement.
     */
    ThreadTask(api::Semaphore& semAcquire, api::Semaphore& semRelease) : Parent(),
        isAcquired_ (false),
        semAcquire_ (semAcquire),
        semRelease_ (semRelease){
    }

    /**
     * @brief Test if semaphore was acquired.
     *
     * @return True if semaphore was acquired.
     */        
    bool_t wasAcquired()
    {
        return isAcquired_;
    }
                    
private:    
        
    /**
     * @copydoc eoos::api::Task::start()
     */        
    virtual void start()
    {
        bool_t res( false );
        res = isAcquired_ = semAcquire_.acquire();
        if( res == false )
        {   // Failure
            while(true){}        
        }
        res = semRelease_.release();
        if( res == false )
        {   // Failure
            while(true){}        
        }
        // Success
        while(true){}
    }
    
    bool_t isAcquired_;          ///< Acquirement flag.
    api::Semaphore& semAcquire_; ///< Semaphore to acquire in the thread.
    api::Semaphore& semRelease_; ///< Semaphore to release in the thread after the acquirement.
};

void testSemaphoreAsMutex()
{
    bool res( false );    
    lib::Semaphore<> sem(1);
    res = sem.acquire();
    if( res == false )
    {   // Failure
        while(true){}        
    }
    res = sem.release();
    if( res == false )
    {   // Failure
        while(true){}        
    }
}


} // namespace

void testSemaphore()
{
    testSemaphoreAsMutex();
    
    bool res( false );
    lib::Semaphore<> semAcquire(0);
    lib::Semaphore<> semRelease(0);
    ThreadTask thread(semAcquire, semRelease);
    thread.execute();
    res = semAcquire.release();
    if( res == false )
    {   // Failure
        while(true){}        
    }
    res = semRelease.acquire();
    if( res == false )
    {   // Failure
        while(true){}        
    }
    bool_t wasAcquired( thread.wasAcquired() );
    if( !wasAcquired )
    {   // Failure
        while(true){}
    }
    // Success
    while(true){}
}

} // namespace eoos
