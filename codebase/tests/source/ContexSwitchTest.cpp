/**
 * @file      ContexSwitchTest.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2023, Sergey Baigudin, Baigudin Software
 *
 * @brief Tests of contex switch.
 */
#include "ContexSwitchTest.hpp"
#include "lib.Thread.hpp"
#include "lib.AbstractTask.hpp"

namespace eoos
{
    
/**
 * @brief Locks on contex 1.
 *
 * The function does not return control to a calling function.
 */
extern "C" void lockOnContex1(void);

/**
 * @brief Locks on contex 2.
 *
 * The function does not return control to a calling function.
 */
extern "C" void lockOnContex2(void);

/**
 * @brief Locks on contex 3.
 *
 * The function does not return control to a calling function.
 */
extern "C" void lockOnContex3(void);
    
namespace
{
    
/**
 * @class Task3
 * @brief Test task with value 3 of registers.
 */
class Task3 : public lib::AbstractTask<>
{
    /**
     * @copydoc eoos::api::Task::start()
     */
    virtual void start()
    {
        lockOnContex3();
    }
};

/**
 * @class Task2
 * @brief Test task with value 2 of registers.
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
        lockOnContex2();
    }
};

} // namespace

void testContexSwitch()
{
    Task2 task2;
    lib::Thread<> thread2(task2);
    thread2.execute();    
    lockOnContex1();
}

} // namespace eoos
