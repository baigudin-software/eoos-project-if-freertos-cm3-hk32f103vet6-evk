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
 *  - If EOOS_GLOBAL_CPU_NUMBER_OF_<resource_name> does not equal zero and EOOS_GLOBAL_ENABLE_NO_HEAP is any,
 *    the resource will be allocated in pre-allocated pool memory.
 *  - If EOOS_GLOBAL_CPU_NUMBER_OF_<resource_name> equals zero and EOOS_GLOBAL_ENABLE_NO_HEAP is not defined, 
 *    the resource will be allocated in heap memory.
 *  - If EOOS_GLOBAL_CPU_NUMBER_OF_<resource_name> equals zero and EOOS_GLOBAL_ENABLE_NO_HEAP is defined, 
 *    the resource will NOT be allocated.
 *  - EOOS_GLOBAL_CPU_NUMBER_OF_<resource_name> less then zero is prohibbited.
 * 
 * @note 
 *  To comply MISRA-C++:2008 in Rule 18–4–1:
 *  - EOOS_GLOBAL_CPU_NUMBER_OF_<resource_name> must not equal zero
 *  - EOOS_GLOBAL_ENABLE_NO_HEAP must be defined.
 *
 * @note 
 * 	The EOOS_GLOBAL_CPU_NUMBER_OF_<resource_name> shall be passed to the project build system through compile definition.
 */
#ifndef EOOS_GLOBAL_CPU_NUMBER_OF_INTERRUPTS
    /**
     * @brief Number of Interrupt resources.
     *
     * @note This value shall not be more than Exeption Numbers of the MCU.
     * @note Reserve 2 resources by default for the EOOS system usage.
     */
    #define EOOS_GLOBAL_CPU_NUMBER_OF_INTERRUPTS (2)
#endif

#ifndef EOOS_GLOBAL_CPU_NUMBER_OF_SYSTEM_TIMERS
    /**
     * @brief Number of System Timer resources that must equal to 1.
     */
    #define EOOS_GLOBAL_CPU_NUMBER_OF_SYSTEM_TIMERS (1)
#endif

/**
 * @brief Do compile error check of static allocated resources.
 */
#ifndef EOOS_GLOBAL_ENABLE_NO_HEAP
    #error "The EOOS_GLOBAL_ENABLE_NO_HEAP must be defined for EOOS CPU layer to comply MISRA-C++:2008"
#endif

#if EOOS_GLOBAL_CPU_NUMBER_OF_INTERRUPTS < 2
    #error "Number of interrupt resources must be more than 2 for EOOS System usage"
#endif

#if EOOS_GLOBAL_CPU_NUMBER_OF_SYSTEM_TIMERS > 1
    #error "The Cortex-M3 has only one system timer"
#endif

#endif // CPU_DEFINITIONS_HPP_
