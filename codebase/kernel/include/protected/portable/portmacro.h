/**
 * @file      portmacro.h
 * @brief     Universal EOOS port of FreeRTOS Kernel V10.5.1 (V202212.01)
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2023, Sergey Baigudin, Baigudin Software
 */
#ifndef PORTMACRO_H
#define PORTMACRO_H

#ifdef __cplusplus
extern "C" {
#endif

/* Port restrictions */
#if configUSE_PORT_OPTIMISED_TASK_SELECTION == 1
#error "EOOS universal FreeRTOS port does not support the port optimised task selection"
#endif

#if configUSE_16_BIT_TICKS == 1
#error "EOOS universal FreeRTOS port does not support 16-bit tick counter"
#endif

/* Type definitions */
typedef uint32_t                                StackType_t;
typedef int32_t                                 BaseType_t;
typedef uint32_t                                UBaseType_t;
typedef uint32_t                                TickType_t;

#define portMAX_DELAY                           ( (TickType_t) 0xffffffffUL )
#define portTICK_TYPE_IS_ATOMIC                 ( 1 )

/* Architecture specifics */
#define portSTACK_GROWTH                        ( -1 )
#define portTICK_PERIOD_MS                      ( (TickType_t) 1000 / configTICK_RATE_HZ )
#define portBYTE_ALIGNMENT                      ( 8 )

/* Scheduler utilities */
extern void vPortYield(void);

#define portYIELD()                             vPortYield()

/* Critical section management
 *
 * @note
 * There is a common approach for ARM Cortex-M3 cores offered by FreeRTOS:
 * See http://www.FreeRTOS.org/RTOS-Cortex-M3-M4.html
 * But this universal EOOS port relies on common approach for most of MCUs
 * when GIE bit exists and all interrupts can be masked by it setting.
 * For ARM Cortex-M3 role of a GIE bit plays the PRIMASK bit, setting of which
 * raises the execution priority to 0, that prevents any exceptions with 
 * configurable priority from becoming active. */
extern void vPortDisableInterrupts(void);
extern void vPortEnableInterrupts(void);
extern void vPortEnterCritical(void);
extern void vPortExitCritical(void);
extern UBaseType_t uxPortEnterCriticalFromISR(void);
extern void vPortExitCriticalFromISR(UBaseType_t);

#define portDISABLE_INTERRUPTS()                vPortDisableInterrupts()
#define portENABLE_INTERRUPTS()                 vPortEnableInterrupts()
#define portENTER_CRITICAL()                    vPortEnterCritical()
#define portEXIT_CRITICAL()                     vPortExitCritical()
#define portSET_INTERRUPT_MASK_FROM_ISR()       uxPortEnterCriticalFromISR()
#define portCLEAR_INTERRUPT_MASK_FROM_ISR( x )  vPortExitCriticalFromISR(x)

/* Task function macros as described on the FreeRTOS.org WEB site.  These are
 * not necessary for to use this port.  They are defined so the common demo files
 * (which build with all the ports) will build. */
#define portTASK_FUNCTION_PROTO( vFunction, pvParameters )    void vFunction( void * pvParameters )
#define portTASK_FUNCTION( vFunction, pvParameters )          void vFunction( void * pvParameters )

#ifdef __cplusplus
}
#endif

#endif /* PORTMACRO_H */
