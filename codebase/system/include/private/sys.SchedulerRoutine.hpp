/**
 * @file      sys.SchedulerRoutine.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2017-2023, Sergey Baigudin, Baigudin Software
 */
#ifndef SYS_SCHEDULERROUTINE_HPP_
#define SYS_SCHEDULERROUTINE_HPP_

#include "sys.NonCopyable.hpp"
#include "api.Task.hpp"

namespace eoos
{
namespace sys
{

/**
 * @class SchedulerRoutine
 * @brief Scheduler interrupt service routine.
 */
class SchedulerRoutine : public NonCopyable<NoAllocator>, public api::Task
{
    typedef NonCopyable<NoAllocator> Parent;

public:

    /**
     * @brief Constructor.
     */
    SchedulerRoutine();

    /**
     * @brief Destructor.
     */
    virtual ~SchedulerRoutine();

    /**
     * @copydoc eoos::api::Object::isConstructed()
     */
    virtual bool_t isConstructed() const;

    /**
     * @copydoc eoos::api::Task::start()
     */
    virtual void start();

    /**
     * @copydoc eoos::api::Task::getStackSize()
     */
    virtual size_t getStackSize() const;

protected:

    using Parent::setConstructed;    

private:

    /**
     * Constructs this object.
     *
     * @return true if object has been constructed successfully.
     */
    bool_t construct();

};

} // namespace sys
} // namespace eoos
#endif // SYS_SCHEDULERROUTINE_HPP_
