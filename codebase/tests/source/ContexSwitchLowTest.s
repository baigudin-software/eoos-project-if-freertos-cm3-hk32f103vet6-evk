/**
 * @file      ContexSwitchLowTest.s
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2023, Sergey Baigudin, Baigudin Software
 *
 * @brief Tests of contex switch.
 */
                .arch armv7-m 
                .cpu cortex-m3
                .fpu softvfp
                .syntax unified
                .thumb
                
                .global     lockOnContex1
                .global     lockOnContex2
                .global     lockOnContex3
                    
                .text
              
/**
 * @fn void lockOnContex1(void);
 */
                .thumb_func
lockOnContex1:
                mov     r0,  #0x1110
                mov     r1,  #0x1111
                mov     r2,  #0x1112
                mov     r3,  #0x1113
                mov     r4,  #0x1114
                mov     r5,  #0x1115
                mov     r6,  #0x1116
                mov     r7,  #0x1117
                mov     r8,  #0x1118
                mov     r9,  #0x1119
                mov     r10, #0x111A
                mov     r11, #0x111B
                mov     r12, #0x111C
                mov     r14, #0x111E
                /* Check visually that on this point all the registers stay unchanged on thread switch */
mc_wait1:       b       mc_wait1

/**
 * @fn void lockOnContex2(void);
 */
                .thumb_func
lockOnContex2:
                mov     r0,  #0x2220
                mov     r1,  #0x2221
                mov     r2,  #0x2222
                mov     r3,  #0x2223
                mov     r4,  #0x2224
                mov     r5,  #0x2225
                mov     r6,  #0x2226
                mov     r7,  #0x2227
                mov     r8,  #0x2228
                mov     r9,  #0x2229
                mov     r10, #0x222A
                mov     r11, #0x222B
                mov     r12, #0x222C
                mov     r14, #0x222E
                /* Check visually that on this point all the registers stay unchanged on thread switch */
mc_wait2:       b       mc_wait2


/**
 * @fn void lockOnContex3(void);
 */
                .thumb_func
lockOnContex3:
                mov     r0,  #0x3330
                mov     r1,  #0x3331
                mov     r2,  #0x3332
                mov     r3,  #0x3333
                mov     r4,  #0x3334
                mov     r5,  #0x3335
                mov     r6,  #0x3336
                mov     r7,  #0x3337
                mov     r8,  #0x3338
                mov     r9,  #0x3339
                mov     r10, #0x333A
                mov     r11, #0x333B
                mov     r12, #0x333C
                mov     r14, #0x333E
                /* Check visually that on this point all the registers stay unchanged on thread switch */
mc_wait3:       b       mc_wait3
