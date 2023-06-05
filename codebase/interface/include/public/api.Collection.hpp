/**
 * @file      api.Collection.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2016-2022, Sergey Baigudin, Baigudin Software
 */
#ifndef API_COLLECTION_HPP_
#define API_COLLECTION_HPP_

#include "api.Object.hpp"

namespace eoos
{
namespace api
{
    
/**
 * @class Collection<T>
 * @brief The root interface of some collections.
 *
 * @tparam T Data type of collection element.
 */
template <typename T>
class Collection : public Object
{

public:

    /**
     * @brief Destructor.
     */
    virtual ~Collection() = 0;

    /**
     * @brief Returns a number of elements in this container.
     *
     * For dynamic-size class implementation the return value depends on 
     * length of containing data. For example, the String class shall return 
     * length of containing string.
     *
     * From other side, for static-size class implementation the return value equals
     * to number of element of such container. For example, the Buffer class shall return 
     * number of its elements not relying on if element assigned a value.
     *
     * @return Number of elements, or always 0 if an error occurred.
     */
    virtual size_t getLength() const = 0;
    
    /**
     * @brief Tests if this collection has elements.
     *
     * For dynamic-size class implementation the return value depends on 
     * length of containing data. For example, the String class shall return 
     * true if containing string length is zero.
     *
     * From other side, for static-size class implementation the return value relies
     * on number of its elements, which actually means that the Buffer class
     * for example shall return always false if it's constructed.
     *
     * @return True if this collection does not contain any elements, or always true if an error occurred.
     */
    virtual bool_t isEmpty() const = 0;

};

template <typename T> ///< SCA MISRA-C++:2008 Defected Rule 7-3-1
Collection<T>::~Collection() {}

} // namespace api
} // namespace eoos
#endif // API_COLLECTION_HPP_
