/**
 * @file      cpu.NoAllocator.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2023, Sergey Baigudin, Baigudin Software
 */
#include "cpu.NoAllocator.hpp"

namespace eoos
{
namespace cpu
{
 
void* NoAllocator::allocate(size_t)
{
    return NULLPTR;
}

void NoAllocator::free(void*)
{
}

} // namespace cpu
} // namespace eoos
