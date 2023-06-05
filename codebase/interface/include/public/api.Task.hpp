/**
 * @file      api.Task.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2016-2022, Sergey Baigudin, Baigudin Software
 */
#ifndef API_TASK_HPP_
#define API_TASK_HPP_

#include "api.Object.hpp"

namespace eoos
{
namespace api
{
    
/**
 * @class Task
 * @brief Task interface.
 *
 * The interface of a task that is being executed in self context.
 */        
class Task : public Object
{

public:

    /**
     * @brief Destructor.
     */
    virtual ~Task() = 0;

    /**
     * @brief Starts executing an operating system task in itself context.
     */
    virtual void start() = 0;

    /**
     * @brief Returns size of stack.
     *
     * The function returns size of stack in bytes which should be allocated for the task.
     *
     * @note POSIX thread won't be created if the stack size is less than PTHREAD_STACK_MIN (16384) bytes.
     *       On some systems, thread creation can fail with if stacksize is not a multiple of the system page size.
     *
     *
     * @return Stack size in bytes, or zero if OS default stack size is needed.
     */
    virtual size_t getStackSize() const = 0;

};

inline Task::~Task() {}
        
} // namespace api
} // namespace eoos
#endif // API_TASK_HPP_
