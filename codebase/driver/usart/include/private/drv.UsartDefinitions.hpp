/**
 * @file      drv.UsartDefinitions.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2023, Sergey Baigudin, Baigudin Software
 *
 * @brief Driver global definitions.
 */
#ifndef DRV_USARTDEFINITIONS_HPP_
#define DRV_USARTDEFINITIONS_HPP_

/**
 * @brief Define number of static allocated resources.
 * 
 * @note
 *  - If EOOS_DRV_GLOBAL_NUMBER_OF_<resource_name> does not equal zero and EOOS_GLOBAL_ENABLE_NO_HEAP is any,
 *    the resource will be allocated in pre-allocated pool memory.
 *  - If EOOS_DRV_GLOBAL_NUMBER_OF_<resource_name> equals zero and EOOS_GLOBAL_ENABLE_NO_HEAP is not defined, 
 *    the resource will be allocated in heap memory.
 *  - If EOOS_DRV_GLOBAL_NUMBER_OF_<resource_name> equals zero and EOOS_GLOBAL_ENABLE_NO_HEAP is defined, 
 *    the resource will NOT be allocated.
 *  - EOOS_DRV_GLOBAL_NUMBER_OF_<resource_name> less then zero is prohibbited.
 * 
 * @note 
 *  To comply MISRA-C++:2008 in Rule 18–4–1:
 *  - EOOS_DRV_GLOBAL_NUMBER_OF_<resource_name> shall not equal zero
 *  - EOOS_GLOBAL_ENABLE_NO_HEAP shall be defined.
 *
 * @note 
 * 	The EOOS_DRV_GLOBAL_NUMBER_OF_<resource_name> shall be passed to the project build system through compile definition.
 */
#ifndef EOOS_DRV_GLOBAL_NUMBER_OF_USARTS
    #define EOOS_DRV_GLOBAL_NUMBER_OF_USARTS (5)
#endif

#endif // DRV_USARTDEFINITIONS_HPP_
