/**
 * @file      api.Iterator.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2016-2022, Sergey Baigudin, Baigudin Software
 */
#ifndef API_ITERATOR_HPP_
#define API_ITERATOR_HPP_

#include "api.IllegalValue.hpp"

namespace eoos
{
namespace api
{
        
/**
 * @class Iterator<T>
 * @brief Iterator interface.
 *
 * @tparam T Data type of iterator element.
 */
template <typename T>
class Iterator : public IllegalValue<T>
{

public:

    /**
     * @brief Destructor.
     */
    virtual ~Iterator() = 0;

    /**
     * @brief Returns next element and advances the cursor position.
     *
     * @return Reference to element.
     *
     * @todo Declare constant function to satisfy MISRA-C++:2008 Rule 9–3–1
     */
    virtual T& getNext() = 0;

    /**
     * @brief Tests if this iteration may return a next element.
     *
     * @return True if next element is had.
     */
    virtual bool_t hasNext() const = 0;

    /**
     * @brief Removes the last element returned by this iterator.
     *
     * The function removes an element that was returned by last call of an element getter.
     * In general such the element getter is the getNext() function, or a getPrevious() function
     * of a child class.
     *
     * @return True if an element is removed successfully.
     */
    virtual bool_t remove() = 0;

};

template <typename T> ///< SCA MISRA-C++:2008 Defected Rule 7-3-1
Iterator<T>::~Iterator() {}

}
}
#endif // API_ITERATOR_HPP_
