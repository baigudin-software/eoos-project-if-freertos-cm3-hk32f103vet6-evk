/**
 * @file      Definitions.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2018-2022, Sergey Baigudin, Baigudin Software
 *
 * @brief Global definitions.
 */
#ifndef DEFINITIONS_HPP_
#define DEFINITIONS_HPP_

/**
 * @brief C++ language standard definition.
 */
#ifdef __cplusplus
    #if __cplusplus == 199711L
        #define EOOS_CPP_STANDARD 1998
    #elif __cplusplus == 201103L
        #define EOOS_CPP_STANDARD 2011
    #elif __cplusplus == 201402L
        #define EOOS_CPP_STANDARD 2014
    #elif __cplusplus == 201703L
        #define EOOS_CPP_STANDARD 2017
    #elif __cplusplus == 202002L
        #define EOOS_CPP_STANDARD 2020
    #else
        #error "C++ language standard set for compiler is not supported"
    #endif
#else
    #error "C language standard is not supported at all"
#endif

/**
 * @brief Microsoft C/C++ compiler (MSVC).
 */
#ifdef _MSC_VER
    
    #ifdef _WIN64
        #define EOOS_TYPE_WIDTH_LLP64
        #define EOOS_SIZE_TYPE unsigned __int64
    #else // _WIN32
        #define EOOS_TYPE_WIDTH_ILP32
        #define EOOS_SIZE_TYPE unsigned int
    #endif
    
    // Define Windows 10 if other is not set by using the /D compiler option.
    #ifndef WINVER
        #define WINVER 0x0A00
    #endif
    #ifndef _WIN32_WINNT
        #define _WIN32_WINNT 0x0A00
    #endif

/**
 * @brief GNU C/C++ compiler.
 */
#elif __GNUC__

    // @todo Avoid such style of definition here with definition EOOS_SIZE_TYPE
    #ifdef EOOS_TYPE_STDLIB
        #define EOOS_SIZE_TYPE std::size_t	
    #elif __LP64__
        #define EOOS_TYPE_WIDTH_LP64
        #define EOOS_SIZE_TYPE unsigned long int
    #else
        #error "Memory type is not supported"
    #endif

/**
 * @brief Undefined compiler 
 */ 
#else
    #define EOOS_TYPE_STDLIB
    #define EOOS_SIZE_TYPE std::size_t
#endif

/**
 * @brief C++ language keywords re-definition.
 */
#if EOOS_CPP_STANDARD >= 2011
    #define EOOS_KEYWORD_NOEXCEPT noexcept
#else
    #define EOOS_KEYWORD_NOEXCEPT
#endif // __cplusplus

/**
 * @brief Enable no heap memory usage.
 *
 * MISRA-C++:2008 prohibits dynamic heap memory usage in Rule 18–4–1.
 * AUTOSAR-C++14 allows dynamic heap memory allocation usage conditionally in Rules A18-5-1, A18-5-2, A18-5-3.
 *
 * @note The EOOS_GLOBAL_ENABLE_NO_HEAP shall be passed to the project build system through compile definition.
 */
// #define EOOS_GLOBAL_ENABLE_NO_HEAP

/**
 * @brief Define number of static allocated resources.
 * 
 * @note
 *  - If EOOS_GLOBAL_NUMBER_OF_<resource_name> does not equal zero and EOOS_GLOBAL_ENABLE_NO_HEAP is any,
 *    the resource will be allocated in pre-allocated pool memory.
 *  - If EOOS_GLOBAL_NUMBER_OF_<resource_name> equals zero and EOOS_GLOBAL_ENABLE_NO_HEAP is not defined, 
 *    the resource will be allocated in heap memory.
 *  - If EOOS_GLOBAL_NUMBER_OF_<resource_name> equals zero and EOOS_GLOBAL_ENABLE_NO_HEAP is defined, 
 *    the resource will NOT be allocated.
 *  - EOOS_GLOBAL_NUMBER_OF_<resource_name> less then zero is prohibbited.
 * 
 * @note 
 *  To comply MISRA-C++:2008 in Rule 18–4–1:
 *  - EOOS_GLOBAL_NUMBER_OF_<resource_name> shall not equal zero
 *  - EOOS_GLOBAL_ENABLE_NO_HEAP shall be defined.
 *
 * @note 
 * 	The EOOS_GLOBAL_NUMBER_OF_<resource_name> shall be passed to the project build system through compile definition.
 *
 * @note
 *	Currently EOOS_GLOBAL_NUMBER_OF_<resource_name> feature supported only by EOOS POSIX.
 *  For EOOS WIN32 these defines have no effects.
 */
#ifndef EOOS_GLOBAL_NUMBER_OF_MUTEXS
    #define EOOS_GLOBAL_NUMBER_OF_MUTEXS (0)
#endif

#ifndef EOOS_GLOBAL_NUMBER_OF_SEMAPHORES
    #define EOOS_GLOBAL_NUMBER_OF_SEMAPHORES (0)
#endif

#ifndef EOOS_GLOBAL_NUMBER_OF_THREADS
    #define EOOS_GLOBAL_NUMBER_OF_THREADS (0)
#endif

#endif // DEFINITIONS_HPP_
