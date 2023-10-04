/**
 * @file      FreeRTOSConfig.h
 * @brief     Universal EOOS port configuration of FreeRTOS Kernel V10.5.1 (V202212.01)
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2023, Sergey Baigudin, Baigudin Software
 */
#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

#define configSUPPORT_STATIC_ALLOCATION             ( 1 )
#define configSUPPORT_DYNAMIC_ALLOCATION            ( 0 )

#define configUSE_PORT_OPTIMISED_TASK_SELECTION     ( 0 )

#define configUSE_PREEMPTION		                ( 1 )
#define configUSE_IDLE_HOOK			                ( 0 )
#define configUSE_TICK_HOOK			                ( 0 )
#define configTICK_RATE_HZ			                ( (TickType_t) 1000 )
#define configMAX_PRIORITIES		                ( 5 )
#define configMINIMAL_STACK_SIZE	                ( (unsigned short) 128 )
#define configMAX_TASK_NAME_LEN		                ( 16 )
#define configUSE_TRACE_FACILITY	                ( 1 )
#define configUSE_16_BIT_TICKS		                ( 0 )
#define configIDLE_SHOULD_YIELD		                ( 1 )


#define configUSE_MUTEXES				            ( 1 )
#define configUSE_COUNTING_SEMAPHORES 	            ( 1 )
#define configUSE_ALTERNATIVE_API 		            ( 0 )
#define configCHECK_FOR_STACK_OVERFLOW	            ( 2 )
#define configUSE_RECURSIVE_MUTEXES		            ( 1 )
#define configQUEUE_REGISTRY_SIZE		            ( 0 )
#define configGENERATE_RUN_TIME_STATS	            ( 0 )

#define INCLUDE_vTaskPrioritySet		            ( 1 )
#define INCLUDE_uxTaskPriorityGet		            ( 1 )
#define INCLUDE_vTaskDelete				            ( 1 )
#define INCLUDE_vTaskCleanUpResources	            ( 0 )
#define INCLUDE_vTaskSuspend			            ( 1 )
#define INCLUDE_vTaskDelayUntil			            ( 1 )
#define INCLUDE_vTaskDelay				            ( 1 )

#define configASSERT( x )                           { if( ( x ) == 0 ){ taskDISABLE_INTERRUPTS(); while(1){} } }

#endif /* FREERTOS_CONFIG_H */
