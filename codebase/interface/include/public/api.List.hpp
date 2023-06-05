/**
 * @file      api.List.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2014-2022, Sergey Baigudin, Baigudin Software
 */
#ifndef API_LIST_HPP_
#define API_LIST_HPP_

#include "api.Collection.hpp"
#include "api.IllegalValue.hpp"
#include "api.ListIterator.hpp"

namespace eoos
{
namespace api
{

/**
 * @class List<T>
 * @brief List interface.
 *
 * @tparam T Data type of list element.
 */
template <typename T>
class List : public Collection<T>, public IllegalValue<T>
{

public:

    static const int32_t ERROR_INDEX = -2147483647;

    /**
     * @brief Destructor.
     */
    virtual ~List() = 0;

    /**
     * @brief Inserts new element to the end of this container.
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
     * @brief Inserts new element to the specified position in this container.
     *
     * @note A passed element must be copied to an internal data structure of
     * a realizing class by calling a copy constructor so that the element
     * might be invalidated after the function called.
     *
     * @param index   A position in this container.
     * @param element An inserting element.
     * @return True if element is inserted.
     */
    virtual bool_t add(int32_t index, T const& element) = 0;

    /**
     * @brief Removes all elements from this container.
     */
    virtual void clear() = 0;

    /**
     * @brief Removes the element at the specified position in this container.
     *
     * @param index Position in this container.
     * @return True if an element is removed successfully.
     */
    virtual bool_t remove(int32_t index) = 0;

    /**
     * @brief Removes the first element from this container.
     *
     * @return True if an element is removed successfully.
     */
    virtual bool_t removeFirst() = 0;

    /**
     * @brief Removes the last element from this container.
     *
     * @return True if an element is removed successfully.
     */
    virtual bool_t removeLast() = 0;

    /**
     * @brief Removes the first occurrence of the specified element from this container.
     *
     * @param element Reference to element.
     * @return True if an element is removed successfully.
     */
    virtual bool_t removeElement(T const& element) = 0;

    /**
     * @brief Returns an element from this container by index.
     *
     * @param index Position in this container.
     * @return Indexed element of this container.
     *
     * @todo Declare constant function to satisfy MISRA-C++:2008 Rule 9–3–1
     */
    virtual T& get(int32_t index) = 0;

    /**
     * @brief Returns the first element in this container.
     *
     * @return The first element in this container.
     *
     * @todo Declare constant function to satisfy MISRA-C++:2008 Rule 9–3–1
     */
    virtual T& getFirst() = 0;

    /**
     * @brief Returns the last element in this container.
     *
     * @return The last element in this container.
     *
     * @todo Declare constant function to satisfy MISRA-C++:2008 Rule 9–3–1
     */
    virtual T& getLast() = 0;

    /**
     * @brief Returns a list iterator of this container elements.
     *
     * @note Either the delete operator must be called for returned value when
     * the iterating of a collection has been completed, or returned raw pointer
     * assigned to a smart pointer.
     *
     * @note Given index must not be out of bounds (index < 0 || index > length()) for LinkedList
     *       and out of bounds (index < 0 || index >= length()) for CircularList
     * 
     * @note Modification of the list by the list functions is not desirable 
     * if operability of the returned iterator has to be.
     *
     * @param index Start position in this container.
     * @return Pointer to new list iterator.
     *
     * @todo Declare constant function to satisfy MISRA-C++:2008 Rule 9–3–1
     */
    virtual ListIterator<T>* getListIterator(int32_t index=0) = 0;

    /**
     * @brief Returns the index of the first occurrence of the specified element in this container.
     *
     * @param element Reference to the element.
     * @return Index or ERROR_INDEX if this container does not contain the element.
     */
    virtual int32_t getIndexOf(T const& element) const = 0;

    /**
     * @brief Tests if given index is available.
     *
     * @param index Checking position in this container.
     * @return True if index is present.
     */
    virtual bool_t isIndex(int32_t index) const = 0;

};

template <typename T> ///< SCA MISRA-C++:2008 Defected Rule 7-3-1
List<T>::~List() {}
        
} // namespace api
} // namespace eoos
#endif // API_LIST_HPP_
