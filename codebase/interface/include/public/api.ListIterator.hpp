/**
 * @file      api.ListIterator.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2016-2022, Sergey Baigudin, Baigudin Software
 */
#ifndef API_LISTITERATOR_HPP_
#define API_LISTITERATOR_HPP_

#include "api.Iterator.hpp"

namespace eoos
{
namespace api
{
        
/**
 * @class ListIterator<T>
 * @brief List iterator interface.
 *
 * @tparam T Data type of list iterator element.
 */
template <typename T>
class ListIterator : public Iterator<T>
{

public:

    static const int32_t ERROR_INDEX = -2147483646;

    /**
     * @brief Destructor.
     */
    virtual ~ListIterator() = 0;

    /**
     * @brief Inserts the specified element into the list.
     *
     * Function inserts a given element before the element
     * that will be returned by the getNext() function.
     * Therefore subsequent call to getNext() will be unaffected,
     * and a subsequent call to getPrevious() will return the inserted element.
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
     * @brief Returns previous element and advances the cursor backwards.
     *
     * @return Reference to element.
     *
     * @todo Declare constant function to satisfy MISRA-C++:2008 Rule 9–3–1     
     */
    virtual T& getPrevious() = 0;

    /**
     * @brief Tests if this iteration may return a previous element.
     *
     * @return True if previous element is had.
     */
    virtual bool_t hasPrevious() const = 0;

    /**
     * @brief Returns the index of the element that would be returned by a subsequent call to getNext().
     *
     * @return For LinkedList: Index of the next element or list size if the list iterator is at the end of the list.
     *         For CircularList: Index of the previous element or -1 if the list is empty.
     *         On error ERROR_INDEX is returned.
     */
    virtual int32_t getNextIndex() const = 0;

    /**
     * @brief Returns the index of the element that would be returned by a subsequent call to getPrevious().
     *
     * @return For LinkedList: Index of the previous element or -1 if the the iterator is at the beginning of the list.
     *         For CircularList: Index of the previous element or -1 if the list is empty.
     *         On error ERROR_INDEX is returned.
     */
    virtual int32_t getPreviousIndex() const = 0;

};

template <typename T> ///< SCA MISRA-C++:2008 Defected Rule 7-3-1
ListIterator<T>::~ListIterator() {}

} // namespace api
} // namespace eoos
#endif // API_LISTITERATOR_HPP_
