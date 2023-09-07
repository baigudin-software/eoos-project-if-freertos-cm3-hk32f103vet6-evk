/**
 * @file      cpu.NoAllocator.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2023, Sergey Baigudin, Baigudin Software
 */
#ifndef CPU_NOALLOCATOR_HPP_
#define CPU_NOALLOCATOR_HPP_

#include "cpu.Types.hpp"

namespace eoos
{
namespace cpu
{
 
/**
 * @class NoAllocator
 * @brief No memory allocator.
 */ 
class NoAllocator
{

public:

    /**
     * @brief Does not allocate memory.
     *
     * @return The null pointer.
     */
    static void* allocate(size_t);

    /**
     * @brief Frees allocated memory.
     */
    static void free(void*);

};

} // namespace cpu
} // namespace eoos

#endif // CPU_NOALLOCATOR_HPP_
