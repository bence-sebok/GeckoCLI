/*
 * gpio.c
 *
 *  Created on: May 20, 2018
 *      Author: sebokbence
 */

#include "FreeRTOS.h"
#include "gpio.h"
#include "em_gpio.h"
#include "semphr.h"
#include <stdio.h>
#include "bsp.h"

extern SemaphoreHandle_t semPB0;
extern SemaphoreHandle_t semPB1;

void initGPIO()
{
	// Initialize GPIO
	GPIO_PinModeSet(gpioPortB, 9, gpioModeInput, 0);
	GPIO_ExtIntConfig(gpioPortB, 9, 9, pdFALSE, pdTRUE, pdTRUE);
	GPIO_PinModeSet(gpioPortB, 10, gpioModeInput, 0);
	GPIO_ExtIntConfig(gpioPortB, 10, 10, pdFALSE, pdTRUE, pdTRUE);
	// Initialize NVIC
	NVIC_ClearPendingIRQ(GPIO_ODD_IRQn);
	NVIC_EnableIRQ(GPIO_ODD_IRQn);
	NVIC_SetPriority(GPIO_ODD_IRQn, configMAX_SYSCALL_INTERRUPT_PRIORITY);
	NVIC_ClearPendingIRQ(GPIO_EVEN_IRQn);
	NVIC_EnableIRQ(GPIO_EVEN_IRQn);
	NVIC_SetPriority(GPIO_EVEN_IRQn, configMAX_SYSCALL_INTERRUPT_PRIORITY);
	NVIC_SetPriority(UART0_RX_IRQn, configMAX_SYSCALL_INTERRUPT_PRIORITY);
	NVIC_SetPriorityGrouping(0);
}

/*
 * GPIO (odd) IRQ handler
 */
void GPIO_ODD_IRQHandler(void)
{
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;
	printf("GPIO ODD IRQ handler: PB1\n");
	uint32_t iflags;
	iflags = GPIO_IntGetEnabled() & 0x0000AAAA;
	GPIO_IntClear(iflags);
	BSP_LedToggle(1);
	xSemaphoreGiveFromISR(semPB1, &xHigherPriorityTaskWoken);
	portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}
/*
 * GPIO (even) IRQ handler
 */
void GPIO_EVEN_IRQHandler(void)
{
	uint32_t iflags;
	iflags = GPIO_IntGetEnabled() & 0x00005555;
	GPIO_IntClear(iflags);
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;
	printf("GPIO EVEN IRQ handler: PB0\n");
	BSP_LedToggle(0);
	xSemaphoreGiveFromISR(semPB0, &xHigherPriorityTaskWoken);
	portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}
