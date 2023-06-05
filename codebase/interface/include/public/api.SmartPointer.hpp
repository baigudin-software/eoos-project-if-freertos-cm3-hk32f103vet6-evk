/**
 * @file      api.SmartPointer.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2022, Sergey Baigudin, Baigudin Software
 */
#ifndef API_SMARTPOINTER_HPP_
#define API_SMARTPOINTER_HPP_

#include "api.Object.hpp"

namespace eoos
{
namespace api
{

/**
 * @class SmartPointer<T>
 * @brief Smart Pointer interface.
 *
 * @tparam T Data type of an owning object.
 */
template <typename T>
class SmartPointer : public Object
{

public:

    /**
     * @brief Destructor.
     */
    virtual ~SmartPointer() = 0;
    
    /**
     * @brief Returns pointer to the managed object.
     *
     * @return Pointer to the managed object or NULLPTR if no object managed.
     */   
    virtual T* get() const = 0;

    /**
     * @brief Releases the managed object.
     */   
    virtual void reset() = 0;

    /**
     * @brief Replaces the managed object with a given object.
     *
     * @param ptr An object to replace the managed object.
     */
    virtual void reset(T* ptr) = 0;
    
    /**
     * @brief Returns amount of smart objects for the managed object.
     *
     * @return Amount of smart objects manage the same object, if no managed object, 0 is returned.
     */   
    virtual int32_t getCount() const = 0;

    /**
     * @brief Tests if this smart object does not manage any object.
     *
     * @return true if no object managed.
     */   
    virtual bool_t isNull() const = 0;

    /**
     * @brief Tests if this smart object is only one manages an object.
     *
     * @return true if this smart object is one, otherwise false.
     */   
    virtual bool_t isUnique() const = 0;

};

template <typename T> ///< SCA MISRA-C++:2008 Defected Rule 7-3-1
SmartPointer<T>::~SmartPointer() {}
        
} // namespace api
} // namespace eoos
#endif // API_STRING_HPP_
