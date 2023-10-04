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

namespace eoos
{
namespace
{
    
/**
 * @class Task3
 * @brief Test task 3.
 */
class Task3 : public lib::AbstractTask<>
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
 * @class Task2
 * @brief Test task 2.
 */
class Task2 : public lib::AbstractTask<>
{
    /**
     * @copydoc eoos::api::Task::start()
     */        
    virtual void start()
    {
        Task3 task3;
        lib::Thread<> thread3(task3);
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
    Task2 task2;
    lib::Thread<> thread2(task2);
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
