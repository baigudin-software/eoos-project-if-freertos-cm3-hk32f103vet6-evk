/**
 * @brief Boot routine.
 *
 * The module initializes HK32F103x MCU and C/C++ run-time environment.
 *
 * @file      cpu.Boot.gcc.s
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2023, Sergey Baigudin, Baigudin Software
 */
                .cpu cortex-m3
                .fpu softvfp
                .thumb
                
                .global     _start
                .global     mg_bootstrap
                .global     d_tos_main
                    
                .extern     main
                .extern     CpuBoot_initialize
                .extern     CpuBoot_fillStack
                
                .bss
                .align  8
d_eos_process:  .space  0x00000400
d_tos_process:

                .bss
                .align  8
d_eos_main:     .space  0x00000400
d_tos_main:  
                    
                .text
                .thumb_func
mg_bootstrap:
                /* Set processor PRIMASK and FAULTMASK values */
                cpsid   i
                cpsie   f

                /* Synchronize data and instructions */
                dsb
                isb

                /* Set Thread mode uses SP_process and Handler mode uses SP_main */
                mrs     r0, CONTROL
                mov     r1, #2
                orr     r0, r1
                msr     CONTROL, r0
                isb                         /* Following ST Cortex-M3 Programming manual (PM0056) */
                ldr     r0, =d_tos_process
                mov     r13, r0

                /* Copy .data from FLASH to SRAM */
                ldr     r0, =_sdata
                ldr     r1, =_edata
                ldr     r2, =_sidata
                mov     r3, #0
                b       m_copy_data
mc_copy_data:   ldr     r4, [r2, r3]
                str     r4, [r0, r3]
                add     r3, r3, #4
m_copy_data:    add     r4, r0, r3
                cmp     r4, r1
                bcc     mc_copy_data

                /* Zero .bss section */
                ldr     r0, =_sbss
                ldr     r1, =_ebss
                mov     r3, #0
                b       m_zero_bss
mc_zero_bss:    str     r3, [r0]
                add     r0, r0, #4
m_zero_bss:     cmp     r0, r1
                bcc     mc_zero_bss

                /* Call C/C++ environment initialization */
                bl      CpuBoot_initialize 

                /* Fill main stack */
                ldr     r0, =d_eos_main
                ldr     r1, =d_tos_main
                ldr     r3, =v_stack_fill
                ldr     r3, [r3]
                b       m_zero_stack0
mc_zero_stack0: str     r3, [r0]
                add     r0, r0, #4
m_zero_stack0:  cmp     r0, r1
                bcc     mc_zero_stack0

                /* Fill process stack */
                ldr     r0, =d_eos_process
                ldr     r1, =d_tos_process
                ldr     r3, =v_stack_fill
                ldr     r3, [r3]
                b       m_zero_stack1
mc_zero_stack1: str     r3, [r0]
                add     r0, r0, #4
m_zero_stack1:  cmp     r0, r1
                bcc     mc_zero_stack1

                /* Clean general purpose registers */
                mov     r0,  #0
                mov     r1,  r0
                mov     r2,  r0
                mov     r3,  r0
                mov     r4,  r0
                mov     r5,  r0
                mov     r6,  r0
                mov     r7,  r0
                mov     r8,  r0
                mov     r9,  r0
                mov     r10, r0
                mov     r11, r0
                mov     r12, r0

                /* Run the main() function */
                bl      main
                
                /* Program execution complited */
                cpsid   i
                cpsid   f                
mc_idle:        b       mc_idle

v_stack_fill:   .word   0xDAEDDAED
    