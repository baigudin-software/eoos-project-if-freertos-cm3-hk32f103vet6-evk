/**
 * @file      cpu.Definitions.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2023, Sergey Baigudin, Baigudin Software
 *
 * @brief CPU global definitions.
 */
#ifndef CPU_DEFINITIONS_HPP_
#define CPU_DEFINITIONS_HPP_

/**
 * @brief Define number of static allocated resources.
 * 
 * @note
 *  - If EOOS_CPU_GLOBAL_NUMBER_OF_<resource_name> does not equal zero and EOOS_GLOBAL_ENABLE_NO_HEAP is any,
 *    the resource will be allocated in pre-allocated pool memory.
 *  - If EOOS_CPU_GLOBAL_NUMBER_OF_<resource_name> equals zero and EOOS_GLOBAL_ENABLE_NO_HEAP is not defined, 
 *    the resource will be allocated in heap memory.
 *  - If EOOS_CPU_GLOBAL_NUMBER_OF_<resource_name> equals zero and EOOS_GLOBAL_ENABLE_NO_HEAP is defined, 
 *    the resource will NOT be allocated.
 *  - EOOS_CPU_GLOBAL_NUMBER_OF_<resource_name> less then zero is prohibbited.
 * 
 * @note 
 *  To comply MISRA-C++:2008 in Rule 18–4–1:
 *  - EOOS_CPU_GLOBAL_NUMBER_OF_<resource_name> shall not equal zero
 *  - EOOS_GLOBAL_ENABLE_NO_HEAP shall be defined.
 *
 * @note 
 * 	The EOOS_CPU_GLOBAL_NUMBER_OF_<resource_name> shall be passed to the project build system through compile definition.
 *
 * @note
 *	Currently EOOS_CPU_GLOBAL_NUMBER_OF_<resource_name> feature supported only by EOOS POSIX.
 *  For EOOS WIN32 these defines have no effects.
 */
#ifndef EOOS_CPU_GLOBAL_NUMBER_OF_INTERRUPTS
    #define EOOS_CPU_GLOBAL_NUMBER_OF_INTERRUPTS (0)
#endif

#ifndef EOOS_CPU_GLOBAL_NUMBER_OF_SYSTEM_TIMERS
    #define EOOS_CPU_GLOBAL_NUMBER_OF_SYSTEM_TIMERS (0)
#endif

#if EOOS_CPU_GLOBAL_NUMBER_OF_SYSTEM_TIMERS > 1
    #error "The Cortex-M3 has only one system timer"
#endif

#endif // CPU_DEFINITIONS_HPP_
