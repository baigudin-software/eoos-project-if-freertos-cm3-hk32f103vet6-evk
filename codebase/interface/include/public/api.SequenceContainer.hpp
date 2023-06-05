/**
 * @file      api.SequenceContainer.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2022, Sergey Baigudin, Baigudin Software
 */
#ifndef API_SEQUENCECONTAINER_HPP_
#define API_SEQUENCECONTAINER_HPP_

#include "api.Collection.hpp"

namespace eoos
{
namespace api
{

/**
 * @class SequenceContainer<T>
 * @brief Sequence сontainer interface.
 *
 * @tparam T Data type of string characters.
 */
template <typename T>
class SequenceContainer : public Collection<T>
{

public:

    /**
     * @brief Destructor.
     */
    virtual ~SequenceContainer() = 0;

    /**
     * @brief Returns pointer to the first element of sequence сontainer.
     *
     * @note Be careful, some action with the object might relocate internal buffer
     * that contains elements. By this reason, a returned address will be actual
     * until you do not call a non-constant function of this class for an object.
     *
     * @return Address of the first element, or NULLPTR if an error occurred.
     *
     * @todo Extend this function with constant function declaration as well.     
     */
    virtual T* getData() const = 0;

};

template <typename T> ///< SCA MISRA-C++:2008 Defected Rule 7-3-1
SequenceContainer<T>::~SequenceContainer() {}
        
} // namespace api
} // namespace eoos
#endif // API_SEQUENCECONTAINER_HPP_
