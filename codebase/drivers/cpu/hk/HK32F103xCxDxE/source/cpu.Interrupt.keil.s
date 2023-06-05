; ----------------------------------------------------------------------------
; @brief Interrupt low level module.
;
; @file      cpu.Interrupt.keil.s
; @author    Sergey Baigudin, sergey@baigudin.software
; @copyright 2023, Sergey Baigudin, Baigudin Software
; ----------------------------------------------------------------------------

                PRESERVE8
                THUMB

                AREA    RESET, DATA, READONLY

m_vectors       DCD     0                         ; 0                         ; Reserved
                DCD     m_handle_reset            ; m_handle_reset            ; Reset
                DCD     m_handle_nothing              ; m_handle_nmi              ; NMI
                DCD     m_handle_nothing          ; m_handle_hardfault        ; Hard Fault
                DCD     m_handle_nothing          ; m_handle_memmanage        ; MPU Fault
                DCD     m_handle_nothing          ; m_handle_busfault         ; Bus Fault
                DCD     m_handle_nothing          ; m_handle_usagefault       ; Usage Fault
                DCD     0                         ; 0                         ; Reserved
                DCD     0                         ; 0                         ; Reserved
                DCD     0                         ; 0                         ; Reserved
                DCD     0                         ; 0                         ; Reserved
                DCD     m_handle_nothing          ; m_handle_svcall           ; SVCall
                DCD     m_handle_nothing          ; m_handle_debugmon         ; Debug Monitor
                DCD     0                         ; 0                         ; Reserved
                DCD     m_handle_nothing          ; m_handle_pendsv           ; PendSV
                DCD     m_handle_nothing          ; m_handle_systick          ; SysTick

                ; External Interrupts
                DCD     m_handle_nothing          ; WWDG_IRQHandler           ; Window Watchdog
                DCD     m_handle_nothing          ; PVD_IRQHandler            ; PVD through EXTI Line detect
                DCD     m_handle_nothing          ; TAMPER_IRQHandler         ; Tamper
                DCD     m_handle_nothing          ; RTC_IRQHandler            ; RTC
                DCD     m_handle_nothing          ; FLASH_IRQHandler          ; Flash
                DCD     m_handle_nothing          ; RCC_IRQHandler            ; RCC
                DCD     m_handle_nothing          ; EXTI0_IRQHandler          ; EXTI Line 0
                DCD     m_handle_nothing          ; EXTI1_IRQHandler          ; EXTI Line 1
                DCD     m_handle_nothing          ; EXTI2_IRQHandler          ; EXTI Line 2
                DCD     m_handle_nothing          ; EXTI3_IRQHandler          ; EXTI Line 3
                DCD     m_handle_nothing          ; EXTI4_IRQHandler          ; EXTI Line 4
                DCD     m_handle_nothing          ; DMAChannel1_IRQHandler    ; DMA Channel 1
                DCD     m_handle_nothing          ; DMAChannel2_IRQHandler    ; DMA Channel 2
                DCD     m_handle_nothing          ; DMAChannel3_IRQHandler    ; DMA Channel 3
                DCD     m_handle_nothing          ; DMAChannel4_IRQHandler    ; DMA Channel 4
                DCD     m_handle_nothing          ; DMAChannel5_IRQHandler    ; DMA Channel 5
                DCD     m_handle_nothing          ; DMAChannel6_IRQHandler    ; DMA Channel 6
                DCD     m_handle_nothing          ; DMAChannel7_IRQHandler    ; DMA Channel 7
                DCD     m_handle_nothing          ; ADC_IRQHandler            ; ADC
                DCD     m_handle_nothing          ; USB_HP_CAN_TX_IRQHandler  ; USB High Priority or CAN TX
                DCD     m_handle_nothing          ; USB_LP_CAN_RX0_IRQHandler ; USB Low  Priority or CAN RX0
                DCD     m_handle_nothing          ; CAN_RX1_IRQHandler        ; CAN RX1
                DCD     m_handle_nothing          ; CAN_SCE_IRQHandler        ; CAN SCE
                DCD     m_handle_nothing          ; EXTI9_5_IRQHandler        ; EXTI Line 9..5
                DCD     m_handle_nothing          ; TIM1_BRK_IRQHandler       ; TIM1 Break
                DCD     m_handle_nothing          ; TIM1_UP_IRQHandler        ; TIM1 Update
                DCD     m_handle_nothing          ; TIM1_TRG_COM_IRQHandler   ; TIM1 Trigger and Commutation
                DCD     m_handle_nothing          ; TIM1_CC_IRQHandler        ; TIM1 Capture Compare
                DCD     m_handle_nothing          ; vTimer2IntHandler         ; TIM2
                DCD     m_handle_nothing          ; TIM3_IRQHandler           ; TIM3
                DCD     m_handle_nothing          ; TIM4_IRQHandler           ; TIM4
                DCD     m_handle_nothing          ; I2C1_EV_IRQHandler        ; I2C1 Event
                DCD     m_handle_nothing          ; I2C1_ER_IRQHandler        ; I2C1 Error
                DCD     m_handle_nothing          ; I2C2_EV_IRQHandler        ; I2C2 Event
                DCD     m_handle_nothing          ; I2C2_ER_IRQHandler        ; I2C2 Error
                DCD     m_handle_nothing          ; SPI1_IRQHandler           ; SPI1
                DCD     m_handle_nothing          ; SPI2_IRQHandler           ; SPI2
                DCD     m_handle_nothing          ; vUARTInterruptHandler     ; USART1
                DCD     m_handle_nothing          ; USART2_IRQHandler         ; USART2
                DCD     m_handle_nothing          ; USART3_IRQHandler         ; USART3
                DCD     m_handle_nothing          ; EXTI15_10_IRQHandler      ; EXTI Line 15..10
                DCD     m_handle_nothing          ; RTCAlarm_IRQHandler       ; RTC Alarm through EXTI Line
                DCD     m_handle_nothing          ; USBWakeUp_IRQHandler      ; USB Wakeup from suspend


                AREA    |.text|, CODE, READONLY
                ENTRY
m_handle_reset
                nop
                nop
                nop                
                b       m_handle_reset

m_handle_nothing
                b       m_handle_nothing
                
                END


