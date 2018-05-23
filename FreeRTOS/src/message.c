/*
 * message.c
 *
 *  Created on: May 20, 2018
 *      Author: sebokbence
 */

#include <stdio.h>
#include "message.h"
#include "constants.h"
#include "gpioInterrupt.h"
#include "em_gpio.h"
#include "bsp.h"
#include <segmentlcd.h>

void print_commands(void)
{
	printf("List of commands:\n");
	printf("%s: listing available commands.\n", COMMANDS);
	printf("%s: listing available commands.\n", HELP);
	printf("%s: setting LED0\n", SETLED0);
	printf("%s: setting LED1\n", SETLED1);
	printf("%s: setting LED0 and LED1\n", SETLEDS);
	printf("%s: getting the value of LED0\n", GETLED0);
	printf("%s: getting the value of LED1\n", GETLED1);
	printf("%s: clearing LED0\n", CLEARLED0);
	printf("%s: clearing LED1\n", CLEARLED1);
	printf("%s: clearing all the LEDS\n", CLEARLEDS);
	printf("%s <scrolling text>: scrolling <scrolling text> on LCD every seconds\n", TEXT);
}

void welcomeText(void)
{
    SegmentLCD_Write("CLI"); // Welcome message on LCD
    printf("PEP hazi feladat FreeRTOS - CLI\n");
    printf("Seres Zsofia, Sebok Bence\n");
    print_commands();
	printf(">>");
}

void gpioCallback(uint8_t pin)
{
  if (pin == 9)
  {
    BSP_LedToggle(1);
    printf("PB0 is pressed.\n");
  }
  else if (pin == 10)
  {
    BSP_LedToggle(0);
    printf("PB1 is pressed.\n");
  }
}
