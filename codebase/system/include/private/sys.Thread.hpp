/**
 * @file      sys.Thread.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2014-2023, Sergey Baigudin, Baigudin Software
 */
#ifndef SYS_THREAD_HPP_
#define SYS_THREAD_HPP_

#include "sys.NonCopyable.hpp"
#include "api.Thread.hpp"
#include "api.Task.hpp"

namespace eoos
{
namespace sys
{

/**
 * @class Thread
 * @brief Thread class.
 * 
 * @tparam A Heap memory allocator class.
 */
template <class A>
class Thread : public NonCopyable<A>, public api::Thread
{
    typedef NonCopyable<A> Parent;

public:

    /**
     * @brief Constructor of not constructed object.
     *
     * @param task A task interface whose main method is invoked when this thread is started.
     */
    Thread(api::Task& task);

    /**
     * @brief Destructor.
     */
    virtual ~Thread();

    /**
     * @copydoc eoos::api::Object::isConstructed()
     */
    virtual bool_t isConstructed() const;

    /**
     * @copydoc eoos::api::Thread::execute()
     */
    virtual bool_t execute();
    
    /**
     * @copydoc eoos::api::Thread::join()
     */
    virtual bool_t join();

    /**
     * @copydoc eoos::api::Thread::getPriority()
     */
    virtual int32_t getPriority() const;

    /**
     * @copydoc eoos::api::Thread::setPriority(int32_t)
     */
    virtual bool_t setPriority(int32_t priority);

protected:

    using Parent::setConstructed;

private:

    /**
     * @brief Constructor.
     *
     * @return True if object has been constructed successfully.
     */
    bool_t construct();

    /**
     * @brief Starts a thread routine.
     *
     * @param argument Pointer to arguments passed by the POSIX pthread_create function.
     */
    static void* start(void* argument);

//TODO    /**
//TODO     * @struct The pthread attr container for the pthread_create function
//TODO     * @brief The struct implements RAII approach on pthread_attr_t.
//TODO     */
//TODO    struct PthreadAttr
//TODO    {
//TODO        /**
//TODO         * @brief Attributes of the pthread_create function.
//TODO         */
//TODO        ::pthread_attr_t attr; ///< SCA MISRA-C++:2008 Justified Rule 9-5-1 and Rule 11-0-1
//TODO        
//TODO        /**
//TODO         * @brief Constructor of not constructed object.
//TODO         */        
//TODO        PthreadAttr();
//TODO        
//TODO        /**
//TODO         * @brief Destructor.
//TODO         */        
//TODO        ~PthreadAttr();
//TODO
//TODO    };    
    
    /**
     * @brief User executing runnable interface.
     */
    api::Task* task_;

    /**
     * @brief Current status.
     */
    Status status_;
    
    /**
     * @brief This thread priority.
     */    
    int32_t priority_;    
    
    /**
     * @brief The new thread resource identifier.
     */
//TODO    ::pthread_t thread_;
    uint32_t thread_;

};

template <class A>
Thread<A>::Thread(api::Task& task) 
    : NonCopyable<A>()
    , api::Thread()
    , task_ (&task)
    , status_ (STATUS_NEW)
    , priority_ (PRIORITY_NORM)
    , thread_ (0) {
    bool_t const isConstructed( construct() );
    setConstructed( isConstructed );
}

template <class A>
Thread<A>::~Thread()
{
//TODO    if( thread_ != 0U )
//TODO    {
//TODO        // @todo The thread detaching means the thread will still be executed by OS.
//TODO        // Thus, to keep compatibility, common approach for all OSs shall be found
//TODO        // for using pthread_cancel function to cancel the thread execution forcely.
//TODO        static_cast<void>( ::pthread_detach(thread_) );
//TODO        status_ = STATUS_DEAD;            
//TODO    }
}

template <class A>
bool_t Thread<A>::isConstructed() const ///< SCA MISRA-C++:2008 Justified Rule 10-3-1
{
    return Parent::isConstructed();
}

template <class A>
bool_t Thread<A>::execute()
{
    bool_t res( false );
    do{
        if( !isConstructed() )
        {
            break;
        }
        if( status_ != STATUS_NEW )
        {
            break;
        }
//TODO        int_t error( 0 );
//TODO        PthreadAttr pthreadAttr; ///< SCA MISRA-C++:2008 Justified Rule 9-5-1
//TODO        size_t const stackSize( task_->getStackSize() );
//TODO        if(stackSize != 0U)
//TODO        {
//TODO            error = ::pthread_attr_setstacksize(&pthreadAttr.attr, stackSize);
//TODO            if(error != 0)
//TODO            {   ///< UT Justified Branch: OS dependency
//TODO                break;
//TODO            }
//TODO        }
//TODO        error = ::pthread_create(&thread_, &pthreadAttr.attr, &start, &task_);
//TODO        if(error != 0)
//TODO        {   ///< UT Justified Branch: OS dependency
//TODO            break;
//TODO        }
//TODO        status_ = STATUS_RUNNABLE;
//TODO        res = true;
    } while(false);
    return res;        
}

template <class A>
bool_t Thread<A>::join()
{
    bool_t res( false );    
    if( isConstructed() && (status_ == STATUS_RUNNABLE) )
    {
//TODO        int_t const error( ::pthread_join(thread_, NULL) );
//TODO        res = (error == 0) ? true : false;
//TODO        status_ = STATUS_DEAD;
    }
    return res;
}

template <class A>
int32_t Thread<A>::getPriority() const
{
    return isConstructed() ? priority_ : PRIORITY_WRONG;        
}

template <class A>
bool_t Thread<A>::setPriority(int32_t priority)
{
    bool_t res( false );
    if( isConstructed() )
    {
        if( (PRIORITY_MIN <= priority) && (priority <= PRIORITY_MAX) )
        {
            priority_ = priority;
            res = true;
        }
        else if (priority == PRIORITY_LOCK)
        {
            priority_ = priority;
            res = true;
        }
        else 
        {
            res = false;
        }
    }
    // @todo Implemet setting priority on system level regarding common API rage
    return res;
}

template <class A>
bool_t Thread<A>::construct()
{  
    bool_t res( false );
    do
    {
        if( !isConstructed() )
        {   ///< UT Justified Branch: HW dependency
            break;
        }
        if( task_ == NULLPTR )
        {   ///< UT Justified Branch: SW dependency
            break;
        }
        if( !task_->isConstructed() )
        {
            break;
        }
        status_ = STATUS_NEW;
        res = true;
    } while(false);
    if( res == false )
    {
        status_ = STATUS_DEAD;
    }
    return res;    
}

template <class A>
void* Thread<A>::start(void* argument)
{
//TODO    if(argument == NULLPTR) 
//TODO    {   ///< UT Justified Branch: SW dependency
//TODO        return NULLPTR;
//TODO    }
//TODO    api::Task* const task( *reinterpret_cast<api::Task**>(argument) ); ///< SCA MISRA-C++:2008 Justified Rule 5-2-8
//TODO    if(task == NULLPTR)
//TODO    {   ///< UT Justified Branch: HW dependency
//TODO        return NULLPTR;
//TODO    }
//TODO    if( !task->isConstructed() )
//TODO    {   ///< UT Justified Branch: HW dependency
//TODO        return NULLPTR;
//TODO    }        
//TODO    int_t oldtype;
//TODO    // The thread is cancelable.  This is the default
//TODO    // cancelability state in all new threads, including the
//TODO    // initial thread.  The thread's cancelability type
//TODO    // determines when a cancelable thread will respond to a
//TODO    // cancellation request.
//TODO    int_t error( ::pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, &oldtype) );
//TODO    if(error != 0)
//TODO    {   ///< UT Justified Branch: OS dependency
//TODO        return NULLPTR;
//TODO    }
//TODO    // The thread can be canceled at any time. Typically, it
//TODO    // will be canceled immediately upon receiving a cancellation
//TODO    // request, but the system doesn't guarantee this.
//TODO    error = ::pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, &oldtype);
//TODO    if(error != 0)
//TODO    {   ///< UT Justified Branch: OS dependency
//TODO        return NULLPTR;
//TODO    }
//TODO    task->start();
//TODO    return NULLPTR;
    return NULLPTR;
}

//TODO template <class A>
//TODO Thread<A>::PthreadAttr::PthreadAttr()
//TODO {
//TODO     static_cast<void>( ::pthread_attr_init(&attr) );
//TODO }
//TODO 
//TODO template <class A>
//TODO Thread<A>::PthreadAttr::~PthreadAttr()
//TODO {
//TODO     static_cast<void>( ::pthread_attr_destroy(&attr) );
//TODO }

} // namespace sys
} // namespace eoos
#endif // SYS_THREAD_HPP_
