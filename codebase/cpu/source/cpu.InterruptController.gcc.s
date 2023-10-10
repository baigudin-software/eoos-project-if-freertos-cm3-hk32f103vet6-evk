/**
 * @file      cpu.Interrupt.gcc.s
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2023, Sergey Baigudin, Baigudin Software
 *
 * @brief Interrupt low level module.
 */
                .arch armv7-m
                .cpu cortex-m3
                .fpu softvfp
                .syntax unified
                .thumb
                    
                .global m_handle_reset
                .global CpuInterruptController_jumpUsrLow
                .global CpuInterruptController_jumpSvcLow
                .global CpuInterruptGlobal_disableLow
                .global CpuInterruptGlobal_enableLow
                
                .extern d_tos_main
                .extern CpuInterruptController_handleException

/**
 * @brief Exception handler macro.
 */
.macro HANDLE_EXCEPTION name, index
                .thumb_func
\name:
                mov     r0, #\index
                b       m_handle_exception
.endm

/**
 * @brief Exception vector table.
 */
                .section .exception_vectors, "ax"
                .align  0                         /* EXN | IRQ | PRI | Description                                        */
m_vectors:      .word   d_tos_main                /*  00 |   - |   - | Main stack pointer                                 */
                .word   m_handle_reset            /*  01 |   - |  -3 | Reset                                              */
                .word   m_handle_nmi              /*  02 | -14 |  -2 | System handler NMI                                 */
                .word   m_handle_hardfault        /*  03 | -13 |  -1 | Fault handler Hard Fault                           */
                .word   m_handle_memmanage        /*  04 | -12 |   0 | Fault handler MPU Fault                            */
                .word   m_handle_busfault         /*  05 | -11 |   1 | Fault handler Bus Fault                            */
                .word   m_handle_usagefault       /*  06 | -10 |   2 | Fault handler Usage Fault                          */
                .word   0                         /*  07 |   - |   - | Reserved                                           */
                .word   0                         /*  08 |   - |   - | Reserved                                           */
                .word   0                         /*  09 |   - |   - | Reserved                                           */
                .word   0                         /*  10 |   - |   - | Reserved                                           */
                .word   m_handle_svcall           /*  11 |  -5 |   3 | System handler SVCall                              */
                .word   m_handle_debugmon         /*  12 |   - |   4 | Debug Monitor                                      */
                .word   0                         /*  13 |   - |   - | Reserved                                           */
                .word   m_handle_pendsv           /*  14 |  -2 |   5 | System ISR PendSV                                  */
                .word   m_handle_systick          /*  15 |  -1 |   6 | System ISR SysTick                                 */
                .word   m_handle_wwdg             /*  16 |   0 |   7 | ISR Window Watchdog                                */
                .word   m_handle_pvd              /*  17 |   1 |   8 | ISR PVD through EXTI Line detect                   */
                .word   m_handle_tamper           /*  18 |   2 |   9 | ISR Tamper                                         */
                .word   m_handle_rtc              /*  19 |   3 |  10 | ISR RTC                                            */
                .word   m_handle_flash            /*  20 |   4 |  11 | ISR Flash                                          */
                .word   m_handle_rcc              /*  21 |   5 |  12 | ISR RCC                                            */
                .word   m_handle_exti0            /*  22 |   6 |  13 | ISR EXTI Line 0                                    */
                .word   m_handle_exti1            /*  23 |   7 |  14 | ISR EXTI Line 1                                    */
                .word   m_handle_exti2            /*  24 |   8 |  15 | ISR EXTI Line 2                                    */
                .word   m_handle_exti3            /*  25 |   9 |  16 | ISR EXTI Line 3                                    */
                .word   m_handle_exti4            /*  26 |  10 |  17 | ISR EXTI Line 4                                    */
                .word   m_handle_dma1_channel1    /*  27 |  11 |  18 | ISR DMA Channel 1                                  */
                .word   m_handle_dma1_channel2    /*  28 |  12 |  19 | ISR DMA Channel 2                                  */
                .word   m_handle_dma1_channel3    /*  29 |  13 |  20 | ISR DMA Channel 3                                  */
                .word   m_handle_dma1_channel4    /*  30 |  14 |  21 | ISR DMA Channel 4                                  */
                .word   m_handle_dma1_channel5    /*  31 |  15 |  22 | ISR DMA Channel 5                                  */
                .word   m_handle_dma1_channel6    /*  32 |  16 |  23 | ISR DMA Channel 6                                  */
                .word   m_handle_dma1_channel7    /*  33 |  17 |  24 | ISR DMA Channel 7                                  */
                .word   m_handle_adc1_2           /*  34 |  18 |  25 | ISR ADC                                            */
                .word   m_handle_usb_hp_can_tx    /*  35 |  19 |  26 | ISR USB High Priority or CAN TX                    */
                .word   m_handle_usb_lp_can_rx0   /*  36 |  20 |  27 | ISR USB Low  Priority or CAN RX0                   */
                .word   m_handle_can_rx1          /*  37 |  21 |  28 | ISR CAN RX1                                        */
                .word   m_handle_can_sce          /*  38 |  22 |  29 | ISR CAN SCE                                        */
                .word   m_handle_exti9_5          /*  39 |  23 |  30 | ISR EXTI Line 9..5                                 */
                .word   m_handle_tim1_brk         /*  40 |  24 |  31 | ISR TIM1 Break                                     */
                .word   m_handle_tim1_up          /*  41 |  25 |  32 | ISR TIM1 Update                                    */
                .word   m_handle_tim1_trg_com     /*  42 |  26 |  33 | ISR TIM1 Trigger and Commutation                   */
                .word   m_handle_tim1_cc          /*  43 |  27 |  34 | ISR TIM1 Capture Compare                           */
                .word   m_handle_tim2             /*  44 |  28 |  35 | ISR TIM2                                           */
                .word   m_handle_tim3             /*  45 |  29 |  36 | ISR TIM3                                           */
                .word   m_handle_tim4             /*  46 |  30 |  37 | ISR TIM4                                           */
                .word   m_handle_i2c1_ev          /*  47 |  31 |  38 | ISR I2C1 Event                                     */
                .word   m_handle_i2c1_er          /*  48 |  32 |  39 | ISR I2C1 Error                                     */
                .word   m_handle_i2c2_ev          /*  49 |  33 |  40 | ISR I2C2 Event                                     */
                .word   m_handle_i2c2_er          /*  50 |  34 |  41 | ISR I2C2 Error                                     */
                .word   m_handle_spi1             /*  51 |  35 |  42 | ISR SPI1                                           */
                .word   m_handle_spi2             /*  52 |  36 |  43 | ISR SPI2                                           */
                .word   m_handle_usart1           /*  53 |  37 |  44 | ISR USART1                                         */
                .word   m_handle_usart2           /*  54 |  38 |  45 | ISR USART2                                         */
                .word   m_handle_usart3           /*  55 |  39 |  46 | ISR USART3                                         */
                .word   m_handle_exti15_10        /*  56 |  40 |  47 | ISR EXTI Line 15..10                               */
                .word   m_handle_rtcalarm         /*  57 |  41 |  48 | ISR RTC Alarm through EXTI Line 17                 */
                .word   m_handle_usbwakeup        /*  58 |  42 |  49 | ISR USB Wakeup from suspend                        */
                .word   m_handle_tim8_brk         /*  59 |  43 |  50 | ISR TIM8 Brake interrupt                           */
                .word   m_handle_tim8_up          /*  60 |  44 |  51 | ISR TIM8 Update interrupt                          */
                .word   m_handle_tim8_trg_com     /*  61 |  45 |  52 | ISR TIM8 Trigger and communication interrupts      */
                .word   m_handle_tim8_cc          /*  62 |  46 |  53 | ISR TIM8 Capture Compare Interrupt                 */
                .word   m_handle_adc3             /*  63 |  47 |  54 | ISR ADC3 Global Interrupts (including EXTI26)      */
                .word   m_handle_fsmc             /*  64 |  48 |  55 | ISR FSMC Global Interrupt                          */
                .word   m_handle_sdio             /*  65 |  49 |  56 | ISR SDIO Global Interrupt                          */
                .word   m_handle_tim5             /*  66 |  50 |  57 | ISR TIM5 Global Interrupt                          */
                .word   m_handle_spi3             /*  67 |  51 |  58 | ISR SPI3 Global Interrupts                         */
                .word   m_handle_uart4            /*  68 |  52 |  59 | ISR UART4 Global Interrupt                         */
                .word   m_handle_uart5            /*  69 |  53 |  60 | ISR UART5 Global Interrupt                         */
                .word   m_handle_tim6             /*  70 |  54 |  61 | ISR TIM6 Global Interruptions                      */
                .word   m_handle_tim7             /*  71 |  55 |  62 | ISR TIM7 Global Interruptions                      */
                .word   m_handle_dma2_channel1    /*  72 |  56 |  63 | ISR DMA2 Channel 1 Global Interrupt                */
                .word   m_handle_dma2_channel2    /*  73 |  57 |  64 | ISR DMA2 Channel 2 Global Interrupt                */
                .word   m_handle_dma2_channel3    /*  74 |  58 |  65 | ISR DMA2 Channel 3 Global Interrupt                */
                .word   m_handle_dma2_channel4_5  /*  75 |  59 |  66 | ISR DMA2 Channel 4 and Channel 5 Global Interrupts */

                .text
/**
 * @brief Common exception routine enterence.
 */
HANDLE_EXCEPTION m_handle_nmi              2
HANDLE_EXCEPTION m_handle_hardfault        3
HANDLE_EXCEPTION m_handle_memmanage        4
HANDLE_EXCEPTION m_handle_busfault         5   
HANDLE_EXCEPTION m_handle_usagefault       6
HANDLE_EXCEPTION m_handle_debugmon         12              
HANDLE_EXCEPTION m_handle_pendsv           14
HANDLE_EXCEPTION m_handle_wwdg             16
HANDLE_EXCEPTION m_handle_pvd              17
HANDLE_EXCEPTION m_handle_tamper           18
HANDLE_EXCEPTION m_handle_rtc              19
HANDLE_EXCEPTION m_handle_flash            20
HANDLE_EXCEPTION m_handle_rcc              21
HANDLE_EXCEPTION m_handle_exti0            22
HANDLE_EXCEPTION m_handle_exti1            23
HANDLE_EXCEPTION m_handle_exti2            24
HANDLE_EXCEPTION m_handle_exti3            25
HANDLE_EXCEPTION m_handle_exti4            26
HANDLE_EXCEPTION m_handle_dma1_channel1    27
HANDLE_EXCEPTION m_handle_dma1_channel2    28
HANDLE_EXCEPTION m_handle_dma1_channel3    29
HANDLE_EXCEPTION m_handle_dma1_channel4    30
HANDLE_EXCEPTION m_handle_dma1_channel5    31
HANDLE_EXCEPTION m_handle_dma1_channel6    32
HANDLE_EXCEPTION m_handle_dma1_channel7    33
HANDLE_EXCEPTION m_handle_adc1_2           34
HANDLE_EXCEPTION m_handle_usb_hp_can_tx    35
HANDLE_EXCEPTION m_handle_usb_lp_can_rx0   36
HANDLE_EXCEPTION m_handle_can_rx1          37
HANDLE_EXCEPTION m_handle_can_sce          38
HANDLE_EXCEPTION m_handle_exti9_5          39
HANDLE_EXCEPTION m_handle_tim1_brk         40
HANDLE_EXCEPTION m_handle_tim1_up          41
HANDLE_EXCEPTION m_handle_tim1_trg_com     42
HANDLE_EXCEPTION m_handle_tim1_cc          43
HANDLE_EXCEPTION m_handle_tim2             44
HANDLE_EXCEPTION m_handle_tim3             45
HANDLE_EXCEPTION m_handle_tim4             46
HANDLE_EXCEPTION m_handle_i2c1_ev          47
HANDLE_EXCEPTION m_handle_i2c1_er          48
HANDLE_EXCEPTION m_handle_i2c2_ev          49
HANDLE_EXCEPTION m_handle_i2c2_er          50
HANDLE_EXCEPTION m_handle_spi1             51
HANDLE_EXCEPTION m_handle_spi2             52
HANDLE_EXCEPTION m_handle_usart1           53
HANDLE_EXCEPTION m_handle_usart2           54
HANDLE_EXCEPTION m_handle_usart3           55
HANDLE_EXCEPTION m_handle_exti15_10        56
HANDLE_EXCEPTION m_handle_rtcalarm         57
HANDLE_EXCEPTION m_handle_usbwakeup        58
HANDLE_EXCEPTION m_handle_tim8_brk         59
HANDLE_EXCEPTION m_handle_tim8_up          60
HANDLE_EXCEPTION m_handle_tim8_trg_com     61
HANDLE_EXCEPTION m_handle_tim8_cc          62
HANDLE_EXCEPTION m_handle_adc3             63
HANDLE_EXCEPTION m_handle_fsmc             64
HANDLE_EXCEPTION m_handle_sdio             65
HANDLE_EXCEPTION m_handle_tim5             66
HANDLE_EXCEPTION m_handle_spi3             67
HANDLE_EXCEPTION m_handle_uart4            68
HANDLE_EXCEPTION m_handle_uart5            69
HANDLE_EXCEPTION m_handle_tim6             70
HANDLE_EXCEPTION m_handle_tim7             71
HANDLE_EXCEPTION m_handle_dma2_channel1    72
HANDLE_EXCEPTION m_handle_dma2_channel2    73
HANDLE_EXCEPTION m_handle_dma2_channel3    74
HANDLE_EXCEPTION m_handle_dma2_channel4_5, 75

/**
 * @brief Common exception routine.
 */
                .thumb_func
m_handle_exception:
                mov     r8, lr
                bl      CpuInterruptController_handleException
                bx      r8

/**
 * @brief Reset vector routine.
 */
                .thumb_func
m_handle_reset:
                /* Set Vector Table Offset Register (VTOR) */
                ldr     r0, =0xE000ED08
                ldr     r1, =m_vectors
                str     r1, [r0]
                b       mg_bootstrap

/**
 * @brief SVC call routine.
 */
                .thumb_func
m_handle_svcall:
                /* Extract SVC instruction operand to R12 */
                mrs     r12, PSP
                ldr     r12, [r12, #24]
                ldrb    r12, [r12, #-2]
                /* Check if jump on the SCVCall handler */
                cmp     r12, #0xFF
                beq     m_handle_svcall_ff
                /* Check if jump on an ISR handler */
                cmp     r12, #0xFE
                beq     m_handle_svcall_fe
                /* Do return if no special command given */                
                bx      lr

/**
 * @brief SVC call to jump on an ISR.
 *
 * @param R0 Exception number to jump on it. 
 */
                .thumb_func 
m_handle_svcall_fe:
                ldr     r1, =m_vectors
                lsl     r0, r0, #2
                add     r1, r1, r0
                ldr     pc, [r1]

/**
 * @brief SVC call to route user scvcall handler.
 *
 * @param R0 SVC exception number (unused). 
 */
                .thumb_func 
m_handle_svcall_ff:
                mov     r12, #11
                b       m_handle_scheduler

/**
 * @brief System timer routine.
 */
                .thumb_func
m_handle_systick:
                mov     r12, #15
                b       m_handle_scheduler

/**
 * @brief System scheduler routine.
 * @see ARMv7-M Architecture Reference Manual, B1.5.6
 *
 * The routine extends ARMv7-M exception entry behavior by pushing registers on stack.
 * The saved stack is shown below:
 *
 * | R4      | <- PSP of a task on SW save
 * | R5      |
 * | R6      |
 * | R7      |
 * | R8      |
 * | R9      |
 * | R10     |
 * | R11     |
 * | R0      | <- PSP of a task on HW save
 * | R1      |
 * | R2      |
 * | R3      |
 * | R12     |
 * | R14(LR) |
 * | R15(PC) |  = PC of a task is return address
 * | xPSR    |
 * |         | <- PSP of a task on run
 *
 * Note that Thread mode uses SP_process and Handler mode uses SP_main, thus
 * the task R13(SP) on enerence saves in PSP, and the routine use MSP.
 *
 * @param R12 Scheduler exeption number
 */
                .thumb_func
m_handle_scheduler:
                /* Save the remained registers on the Process stack of interrupted thread */
                mrs     r0, psp
                isb
                stmdb   r0!, {r4-r11}
                /* Save new SP of interrupted thread to pxCurrentTCB->pxTopOfStack */                
                ldr	    r7, pxCurrentTCBConst
                ldr	    r1, [r7]
                str     r0, [r1]                
                /* Call the exception high level routine */
                mov     r0, r12
                mov     r8, lr
                bl      CpuInterruptController_handleException
                mov     lr, r8
                /* Load saved SP of a new thread from pxCurrentTCB->pxTopOfStack */                
                ldr     r1, [r7]
                ldr     r0, [r1]
                /* Load the remained registers from the Process stack of a new thread */                
                ldmia   r0!, {r4-r11}
                msr     psp, r0
                isb	
                bx      lr
pxCurrentTCBConst: .word pxCurrentTCB

/**
 * @fn void CpuInterruptController_jumpUsrLow();
 * @brief Jumps to the exception handler.
 *
 * @param R0 Exception number.
 */
                .thumb_func
CpuInterruptController_jumpUsrLow:
                svc     #0xFE
                bx      lr

/**
 * @fn void CpuInterruptController_jumpSvcLow();
 * @brief Jumps to the exception handler.
 *
 * @param R0 SVCall exception number.
 */
                .thumb_func
CpuInterruptController_jumpSvcLow:
                svc     #0xFF
                bx      lr

/**
 * @fn bool CpuInterruptGlobal_disable();
 * @brief Sets PRIMASK to 1 raises the execution priority to 0.
 *
 * @return Value of PRIMASK bit before the function called.
 */
                .thumb_func
CpuInterruptGlobal_disableLow:
                mrs     r0, PRIMASK
                cpsid   i
                bx      lr

/**
 * @fn bool CpuInterruptGlobal_enable();
 * @brief Sets PRIMASK to 0 raises the execution priority to base level.
 *
 * @return Value of PRIMASK bit before the function called. 
 */
                .thumb_func
CpuInterruptGlobal_enableLow:
                mrs     r0, PRIMASK
                cpsie   i
                bx      lr
