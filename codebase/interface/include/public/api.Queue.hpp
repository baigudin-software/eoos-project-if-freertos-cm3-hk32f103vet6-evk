/**
 * @file      api.Queue.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2016-2022, Sergey Baigudin, Baigudin Software
 */
#ifndef API_QUEUE_HPP_
#define API_QUEUE_HPP_

#include "api.Collection.hpp"
#include "api.IllegalValue.hpp"

namespace eoos
{
namespace api
{
    
/**
 * @class Queue<T>
 * @brief Queue interface.
 *
 * @tparam T Data type of queue element.
 */
template <typename T>
class Queue : public Collection<T>, public IllegalValue<T>
{

public:

    /**
     * @brief Destructor.
     */
    virtual ~Queue() = 0;

    /**
     * @brief Inserts a new element to the end of this container.
     *
     * @note A passed element must be copied to an internal data structure of
     * a realizing class by calling a copy constructor so that the element
     * might be invalidated after the function called.
     *
     * @param element An inserting element.
     * @return True if element is added.
     */
    virtual bool_t add(T const& element) = 0;

    /**
     * @brief Removes the head element of this container.
     *
     * @return True if an element is removed successfully.
     */
    virtual bool_t remove() = 0;

    /**
     * @brief Examines the head element of this container.
     *
     * @return The head element.
     *
     * @todo Declare constant function to satisfy MISRA-C++:2008 Rule 9–3–1
     */
    virtual T& peek() = 0;

};

template <typename T> ///< SCA MISRA-C++:2008 Defected Rule 7-3-1
Queue<T>::~Queue() {}
        
} // namespace api
} // namespace eoos
#endif // API_QUEUE_HPP_
