/**
 * @file      cpu.Boot.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2019-2023, Sergey Baigudin, Baigudin Software
 */
#include "cpu.Types.hpp"

extern "C"
{

extern void (* const __init_array_start[])(void);
extern void (* const __init_array_end[])(void);

/**
 * @brief Initializes C/C++ global objects.
 */
void CpuBoot_initialize()
{
    int i;
    int const count = __init_array_end - __init_array_start;
    for(i=0; i<count; i++)
    {
        __init_array_start[i]();
    }
}

/**
 * @brief Fills stack with default value.
 */
void CpuBoot_fillStack(eoos::uint32_t* tos, eoos::uint32_t* eos)
{
    while( tos != eos )
    {
        *eos = 0xDEADDEAD;
        eos++;
    }
}


}
