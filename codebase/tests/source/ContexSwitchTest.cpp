/**
 * @file      ContexSwitchTest.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2023, Sergey Baigudin, Baigudin Software
 *
 * @brief Tests of contex switch.
 */
#include "ContexSwitchTest.hpp"
#include "lib.AbstractThreadTask.hpp"

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
 * @class Thread3
 * @brief Test thread with value 3 of registers.
 */
class Thread3 : public lib::AbstractThreadTask<>
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
 * @class Thread2
 * @brief Test thread with value 2 of registers.
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
        lockOnContex2();
    }
};

} // namespace

void testContexSwitch()
{
    Thread2 thread2;
    thread2.execute();    
    lockOnContex1();
}

} // namespace eoos
