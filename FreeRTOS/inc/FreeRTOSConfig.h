/*
 *  FreeRTOS V7.4.2 - Copyright (C) 2013 Real Time Engineers Ltd.
 *
 *  FEATURES AND PORTS ARE ADDED TO FREERTOS ALL THE TIME.  PLEASE VISIT
 *  http://www.FreeRTOS.org TO ENSURE YOU ARE USING THE LATEST VERSION.
 *
 ***************************************************************************
 *                                                                       *
 *    FreeRTOS tutorial books are available in pdf and paperback.        *
 *    Complete, revised, and edited pdf reference manuals are also       *
 *    available.                                                         *
 *                                                                       *
 *    Purchasing FreeRTOS documentation will not only help you, by       *
 *    ensuring you get running as quickly as possible and with an        *
 *    in-depth knowledge of how to use FreeRTOS, it will also help       *
 *    the FreeRTOS project to continue with its mission of providing     *
 *    professional grade, cross platform, de facto standard solutions    *
 *    for microcontrollers - completely free of charge!                  *
 *                                                                       *
 *    >>> See http://www.FreeRTOS.org/Documentation for details. <<<     *
 *                                                                       *
 *    Thank you for using FreeRTOS, and thank you for your support!      *
 *                                                                       *
 ***************************************************************************
 *
 *
 *  This file is part of the FreeRTOS distribution.
 *
 *  FreeRTOS is free software; you can redistribute it and/or modify it under
 *  the terms of the GNU General Public License (version 2) as published by the
 *  Free Software Foundation AND MODIFIED BY the FreeRTOS exception.
 *
 *  >>>>>>NOTE<<<<<< The modification to the GPL is included to allow you to
 *  distribute a combined work that includes FreeRTOS without being obliged to
 *  provide the source code for proprietary components outside of the FreeRTOS
 *  kernel.
 *
 *  FreeRTOS is distributed in the hope that it will be useful, but WITHOUT ANY
 *  WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 *  FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 *  details. You should have received a copy of the GNU General Public License
 *  and the FreeRTOS license exception along with FreeRTOS; if not it can be
 *  viewed here: http://www.freertos.org/a00114.html and also obtained by
 *  writing to Real Time Engineers Ltd., contact details for whom are available
 *  on the FreeRTOS WEB site.
 *
 *  1 tab == 4 spaces!
 *
 ***************************************************************************
 *                                                                       *
 *    Having a problem?  Start by reading the FAQ "My application does   *
 *    not run, what could be wrong?"                                     *
 *                                                                       *
 *    http://www.FreeRTOS.org/FAQHelp.html                               *
 *                                                                       *
 ***************************************************************************
 *
 *
 *  http://www.FreeRTOS.org - Documentation, books, training, latest versions,
 *  license and Real Time Engineers Ltd. contact details.
 *
 *  http://www.FreeRTOS.org/plus - A selection of FreeRTOS ecosystem products,
 *  including FreeRTOS+Trace - an indispensable productivity tool, and our new
 *  fully thread aware and reentrant UDP/IP stack.
 *
 *  http://www.OpenRTOS.com - Real Time Engineers ltd license FreeRTOS to High
 *  Integrity Systems, who sell the code with commercial support,
 *  indemnification and middleware, under the OpenRTOS brand.
 *
 *  http://www.SafeRTOS.com - High Integrity Systems also provide a safety
 *  engineered and independently SIL3 certified version for use in safety and
 *  mission critical applications that require provable dependability.
 */

/*
 * Modified by Gabor Naszaly <naszaly@mit.bme.hu> @ 14th of March, 2017
 */


#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

#include "em_assert.h"

#ifdef __cplusplus
extern "C" {
#endif

/********************** Configuration of FreeRTOS ****************************/
  
/* Implement FreeRTOS configASSERT as emlib assert */
#define configASSERT( x )                         EFM_ASSERT( x )

/* Modes of operations of operation system*/
#define configUSE_PREEMPTION                      ( 1 )
#define configUSE_TICKLESS_IDLE                   ( 0 )

/* The frequency of the RTOS tick interrupt */
#define configTICK_RATE_HZ                        ( 1000 )

/* Default value of CPU clock (RC)*/
#define configCPU_CLOCK_HZ                        (( unsigned long ) 14000000)

/* Main functions*/
#define configMAX_PRIORITIES                      ( 6 )
#define configMINIMAL_STACK_SIZE                  (( unsigned short ) 140)
#define configTOTAL_HEAP_SIZE                     (( size_t )(9000))
#define configMAX_TASK_NAME_LEN                   ( 10 )
#define configUSE_TRACE_FACILITY                  ( 0 )
#define configUSE_16_BIT_TICKS                    ( 0 )
#define configIDLE_SHOULD_YIELD                   ( 0 )
#define configUSE_MUTEXES                         ( 1 )
#define configUSE_RECURSIVE_MUTEXES               ( 0 )
#define configUSE_COUNTING_SEMAPHORES             ( 0 )
#define configUSE_ALTERNATIVE_API                 ( 0 )/* Deprecated! */
#define configQUEUE_REGISTRY_SIZE                 ( 10 )
#define configUSE_QUEUE_SETS                      ( 0 )

/* Hook function related definitions. */
#define configUSE_TICK_HOOK                       ( 0 )
#define configCHECK_FOR_STACK_OVERFLOW            ( 0 )
#define configUSE_MALLOC_FAILED_HOOK              ( 0 )
#define configUSE_IDLE_HOOK                       ( 0 )

/* Run time stats gathering related definitions. */
#define configGENERATE_RUN_TIME_STATS             ( 0 )

/* Co-routine related definitions. */
#define configUSE_CO_ROUTINES                     ( 0 )
#define configMAX_CO_ROUTINE_PRIORITIES           ( 1 )

/* Software timer related definitions. */
#define configUSE_TIMERS                          ( 1 )
#define configTIMER_TASK_PRIORITY                 ( configMAX_PRIORITIES - 1 ) /* Highest priority */
#define configTIMER_QUEUE_LENGTH                  ( 10 )
#define configTIMER_TASK_STACK_DEPTH              ( configMINIMAL_STACK_SIZE )

/* Interrupt nesting behavior configuration. */
#define configKERNEL_INTERRUPT_PRIORITY           ( 255 ) 
#define configMAX_SYSCALL_INTERRUPT_PRIORITY      ( 191 ) /* equivalent to 0xa0, or priority 5. */

/* Optional functions - most linkers will remove unused functions anyway. */
#define INCLUDE_vTaskPrioritySet                  ( 1 )
#define INCLUDE_uxTaskPriorityGet                 ( 1 )
#define INCLUDE_vTaskDelete                       ( 1 )
#define INCLUDE_vTaskSuspend                      ( 1 )
#define INCLUDE_xResumeFromISR                    ( 1 )
#define INCLUDE_vTaskDelayUntil                   ( 1 )
#define INCLUDE_vTaskDelay                        ( 1 )
#define INCLUDE_xTaskGetSchedulerState            ( 1 )
#define INCLUDE_xTaskGetCurrentTaskHandle         ( 1 )
#define INCLUDE_uxTaskGetStackHighWaterMark       ( 0 )
#define INCLUDE_xTaskGetIdleTaskHandle            ( 0 )
#define INCLUDE_xTimerGetTimerDaemonTaskHandle    ( 0 )
#define INCLUDE_pcTaskGetTaskName                 ( 0 )
#define INCLUDE_eTaskGetState                     ( 1 )

/*-----------------------------------------------------------*/


/* Definitions that map the FreeRTOS port interrupt handlers to their CMSIS
 * standard names. */
#define vPortSVCHandler        SVC_Handler
#define xPortPendSVHandler     PendSV_Handler
#define xPortSysTickHandler    SysTick_Handler


#ifdef __cplusplus
}
#endif
#endif /* FREERTOS_CONFIG_H */

