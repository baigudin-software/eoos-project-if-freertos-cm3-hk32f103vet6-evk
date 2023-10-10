/**
 * @file      ThreadYieldTest.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2023, Sergey Baigudin, Baigudin Software
 *
 * @brief Tests of thread yield.
 */
#include "ThreadYieldTest.hpp"
#include "lib.AbstractThreadTask.hpp"

namespace eoos
{
namespace
{
    
/**
 * @class Thread3
 * @brief Test thread 3.
 */
class Thread3 : public lib::AbstractThreadTask<>
{
    /**
     * @copydoc eoos::api::Task::start()
     */        
    virtual void start()
    {
        int32_t count( 0 );
        while(true)
        {
            // Task 3
            count++;
            lib::Thread<>::yield();
            count--;        
        }
    }
};

/**
 * @class Thread2
 * @brief Test thread 2.
 */
class Thread2 : public lib::AbstractThreadTask<>
{
    /**
     * @copydoc eoos::api::Task::start()
     */        
    virtual void start()
    {
        Thread3 thread3;
        thread3.execute();
        int32_t count( 0 );
        while(true)
        {
            // Task 2
            count++;
            lib::Thread<>::yield();
            count--;        
        }
    }
};

} // namespace

void testThreadYield()
{
    Thread2 thread2;
    thread2.execute();
    int32_t count( 0 );
    while(true)
    {
        // Task 1
        count++;
        lib::Thread<>::yield();
        count--;        
    }
}

} // namespace eoos
