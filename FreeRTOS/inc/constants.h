/*
 * constants.h
 *
 *  Created on: 2018. máj. 5.
 *      Author: zsofiseres
 */

#ifndef INC_CONSTANTS_H_
#define INC_CONSTANTS_H_

//#define DEBUG_AND_TEST
#define  mainDISPLAY_TASK_PRIORITY    ( tskIDLE_PRIORITY + 2 )
#define  mainDISPLAY_TASK_STACK_SIZE  configMINIMAL_STACK_SIZE
#define  mainDEFAULT_TASK_PRIORITY    ( tskIDLE_PRIORITY + 2 )
#define  mainDEFAULT_TASK_STACK_SIZE  configMINIMAL_STACK_SIZE
#define  mainTIMER_AUTO_RELOAD_PERIOD pdMS_TO_TICKS(1000)
#define  mainTASK_PB0_PRIORITY    ( tskIDLE_PRIORITY + 2 )
#define  mainTASK_PB0_STACK_SIZE  configMINIMAL_STACK_SIZE
#define  mainTASK_PB1_PRIORITY    ( tskIDLE_PRIORITY + 2 )
#define  mainTASK_PB1_STACK_SIZE  configMINIMAL_STACK_SIZE
#define  mainTASK_UART_PRIORITY    ( tskIDLE_PRIORITY + 3 )
#define  mainTASK_UART_STACK_SIZE  configMINIMAL_STACK_SIZE
#define  mainTASK_LED_PRIORITY    ( tskIDLE_PRIORITY + 1 )
#define  mainTASK_LED_STACK_SIZE  configMINIMAL_STACK_SIZE
#define BUTTON_PORT (1)
#define PB0 (9)
#define PB1 (10)

#define MESSAGE_BUFFER_LENGTH (50)
#define LCD_CHARS (7)
#define END_CHAR (13)
#define DELETE_CHAR (127)
#define MESSAGE_QUEUE_LENGTH (5)

// List of commands:
#define SETLED0 "SETLED0"
#define SETLED1 "SETLED1"
#define SETLEDS "SETLEDS"
#define GETLED0 "GETLED0"
#define GETLED1 "GETLED1"
#define CLEARLED0 "CLEARLED0"
#define CLEARLED1 "CLEARLED1"
#define CLEARLEDS "CLEARLEDS"
#define COMMANDS "COMMANDS"
#define HELP "HELP"
#define TEXT "TEXT"

#endif /* INC_CONSTANTS_H_ */
