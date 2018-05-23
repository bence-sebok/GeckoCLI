/*
 * gpio.h
 *
 *  Created on: May 20, 2018
 *      Author: sebokbence
 */

#ifndef INC_GPIO_H_
#define INC_GPIO_H_

#include "em_gpio.h"
#include "em_device.h"

void initGPIO();
void GPIO_ODD_IRQHandler(void);
void GPIO_EVEN_IRQHandler(void);

#endif /* INC_GPIO_H_ */
