/**
 * @file      lib.Types.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2020-2022, Sergey Baigudin, Baigudin Software
 *
 * @brief Library type definitions.
 */
#ifndef LIB_TYPES_HPP_
#define LIB_TYPES_HPP_

#include "Types.hpp"

namespace eoos
{
namespace lib
{

/**
 * @struct Number
 * @brief Number properties.
 */
struct Number
{    
    /**
     * @enum Base
     * @brief Radix or base of numbers.
     */
    enum Base
    {
        BASE_2 = 2,   ///< Binary system.
        BASE_8 = 8,   ///< Octal system.
        BASE_10 = 10, ///< Decimal system.
        BASE_16 = 16  ///< Hexadecimal system.
    };
};
    
#if EOOS_CPP_STANDARD >= 2011

/**
 * @brief Structs to remove references.
 */
template <class T> struct remove_reference      {typedef T type;};
template <class T> struct remove_reference<T&>  {typedef T type;};
template <class T> struct remove_reference<T&&> {typedef T type;};

/**
 * @brief Casts an object to right reference.
 */
template <class T>
constexpr typename remove_reference<T>::type&& move(T&& arg) noexcept
{
    return static_cast<typename remove_reference<T>::type&&>(arg);
}

#endif // EOOS_CPP_STANDARD >= 2011

} // namespace lib
} // namespace eoos
#endif // LIB_TYPES_HPP_
