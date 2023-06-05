/**
 * @file      api.Object.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2015-2022, Sergey Baigudin, Baigudin Software
 */
#ifndef API_OBJECT_HPP_
#define API_OBJECT_HPP_

#include "Types.hpp"

namespace eoos
{
namespace api
{

/**
 * @class Object
 * @brief Root interface of the system class hierarchy.
 */
class Object
{

public:

    /**
     * @brief Destructor.
     */
    virtual ~Object() = 0;

    /**
     * @brief Tests if this object has been constructed.
     *
     * @return True if object has been constructed successfully.
     */
    virtual bool_t isConstructed() const = 0;

};

inline Object::~Object() {}
    
} // namespace api
} // namespace eoos
#endif // API_OBJECT_HPP_
