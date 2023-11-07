/**
 * @file      Types.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2014-2022, Sergey Baigudin, Baigudin Software
 *
 * @brief Common type definitions.
 */
#ifndef TYPES_HPP_
#define TYPES_HPP_

#include "Definitions.hpp"

#ifdef EOOS_GLOBAL_TYPE_STDLIB
#include <cstdint>
#endif

namespace eoos
{
    
#if EOOS_CPP_STANDARD >= 2011
typedef decltype(nullptr) nullptr_t;
#else
typedef signed int nullptr_t;
#endif // __cplusplus


#ifndef NULL
#if EOOS_CPP_STANDARD >= 2011
static const nullptr_t NULL( nullptr );
#else
static const nullptr_t NULL( 0 );
#endif
#endif

// NULLPTR definition for EOOS implenemtation
static const nullptr_t NULLPTR( NULL );

#if defined (EOOS_GLOBAL_TYPE_STDLIB)
// C++ Standard Library types
typedef ::std::int16_t          int16_t;
typedef ::std::uint16_t         uint16_t;
typedef ::std::int32_t          int32_t;
typedef ::std::uint32_t         uint32_t;
typedef ::std::int64_t          int64_t;
typedef ::std::uint64_t         uint64_t;
typedef ::std::uintptr_t        intptr_t;
typedef ::std::uintptr_t        uintptr_t;
#elif defined (EOOS_TYPE_WIDTH_LP32)
// LP32 or 2/4/4 (int is 16-bit, long and pointer are 32-bit)
typedef signed   int            int16_t;
typedef unsigned int            uint16_t;
typedef signed   long  int      int32_t;
typedef unsigned long  int      uint32_t;
typedef signed   long  long int int64_t;
typedef unsigned long  long int uint64_t;
typedef signed   long  int      intptr_t;
typedef unsigned long  int      uintptr_t;
#elif defined (EOOS_TYPE_WIDTH_ILP32)
// ILP32 or 4/4/4 (int, long, and pointer are 32-bit)
typedef signed   short int      int16_t;
typedef unsigned short int      uint16_t;
typedef signed   int            int32_t;
typedef unsigned int            uint32_t;
typedef signed   long  long int int64_t;
typedef unsigned long  long int uint64_t;
typedef signed   int            intptr_t;
typedef unsigned int            uintptr_t;
#elif defined (EOOS_TYPE_WIDTH_LLP64)
// LLP64 or 4/4/8 (int and long are 32-bit, pointer is 64-bit)
typedef signed   short int      int16_t;
typedef unsigned short int      uint16_t;
typedef signed   long  int      int32_t;
typedef unsigned long  int      uint32_t;
typedef signed   long  long int int64_t;
typedef unsigned long  long int uint64_t;
typedef signed   long  long int intptr_t;
typedef unsigned long  long int uintptr_t;
#elif defined (EOOS_TYPE_WIDTH_LP64)
// LP64 or 4/8/8 (int is 32-bit, long and pointer are 64-bit)
typedef signed   short int      int16_t;
typedef unsigned short int      uint16_t;
typedef signed   int            int32_t;
typedef unsigned int            uint32_t;
typedef signed   long  int      int64_t;
typedef unsigned long  int      uint64_t;
typedef signed   long  int      intptr_t;
typedef unsigned long  int      uintptr_t;
#else
// C++ standard
typedef signed   int            int16_t;
typedef unsigned int            uint16_t;
typedef signed   long  int      int32_t;
typedef unsigned long  int      uint32_t;
typedef signed   long  long int int64_t;
typedef unsigned long  long int uint64_t;
typedef signed   int            intptr_t;
typedef unsigned int            uintptr_t;
#endif

// Byte types for byte addressing
typedef signed char             int8_t;
typedef unsigned char           uint8_t;
// Floating point types
typedef float                   float32_t;
typedef double                  float64_t;
typedef long double             float128_t;
// Boolean type
typedef bool                    bool_t;  
// Type of minimal addressable memory cell
typedef signed char             cell_t;
typedef unsigned char           ucell_t;
// Typy of the maximum size of a theoretically possible object of any types including array
typedef EOOS_SIZE_TYPE          size_t;
// Char type
typedef char                    char_t;

} // namespace eoos
#endif // TYPES_HPP_
