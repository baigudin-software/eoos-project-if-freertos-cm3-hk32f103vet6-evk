/**
 * @file      api.Iterable.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2016-2022, Sergey Baigudin, Baigudin Software
 */
#ifndef API_ITERABLE_HPP_
#define API_ITERABLE_HPP_

#include "api.Object.hpp"
#include "api.Iterator.hpp"

namespace eoos
{
namespace api
{
    
/**
 * @class Iterable<T>
 * @brief Iterable interface.
 *
 * @tparam T Data type of element.
 */
template <typename T>
class Iterable : public Object
{

public:

    /**
     * @brief Destructor.
     */
    virtual ~Iterable() = 0;

    /**
     * @brief Returns an iterator of elements.
     *
     * @note Either the delete operator must be called for returned value when
     * the iterating of a collection has been completed, or returned raw pointer
     * assigned to a smart pointer.
     *
     * @note Modification of the list by the list functions is not desirable 
     * if operability of the returned iterator has to be.
     *
     * @return Pointer to new iterator.
     *
     * @todo Declare constant function to satisfy MISRA-C++:2008 Rule 9–3–1     
     */
    virtual Iterator<T>* getIterator() = 0;

};

template <typename T> ///< SCA MISRA-C++:2008 Defected Rule 7-3-1
Iterable<T>::~Iterable() {}

} // namespace api
} // namespace eoos
#endif // API_ITERABLE_HPP_
