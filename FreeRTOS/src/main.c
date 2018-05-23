/*
 * Name:
 *     PEP course FreeRTOS homework
 *
 * Created by:
 *     Seres Zsofia and  Sebok Bence
 *
 * Last modified on:
 *     2018-05-07
*/

/* --------------------------------------------------------------------------
   INCLUDES
-------------------------------------------------------------------------- */
// Application specific includes
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <retargetserial.h>
#include <udelay.h>
#include <segmentlcd.h>
#include <em_gpio.h>
#include <em_device.h>
#include "gpiointerrupt.h"
// FreeRTOS includes
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "semphr.h"
// User created headers:
#include "constants.h"
#include "message.h"
#include "gpio.h"
/* --------------------------------------------------------------------------
   VARIABLES
-------------------------------------------------------------------------- */
TaskHandle_t handleMessageTask;
TaskHandle_t handleSetLEDTask0;
TaskHandle_t handleGetLEDTask0;
TaskHandle_t handleSetLEDTask1;
TaskHandle_t handleGetLEDTask1;
TaskHandle_t handleTimer;
SemaphoreHandle_t xSemaphoreUART;
TimerHandle_t x1SecondTimer;
BaseType_t x1SecondTimerStarted;
uint8_t g_messageSize = 0;
uint8_t scrollingSize = 0;
uint8_t scrollingFlag = pdFALSE;
char g_message[MESSAGE_BUFFER_LENGTH];
char gc_LCD_text[LCD_CHARS + 1];
char scrollingText[MESSAGE_BUFFER_LENGTH + 1];
volatile uint8_t g_message_end_flag = 0;
volatile uint8_t giStartPosition = 0;
volatile uint8_t dirRight = 1;
SemaphoreHandle_t semPB0;
SemaphoreHandle_t semPB1;
SemaphoreHandle_t semUART;
BaseType_t xHigherPriorityTaskWoken = pdFALSE;
TaskHandle_t xTaskToNotify;
xQueueHandle xCharQueue;
xQueueHandle xMessageQueue;
volatile char UART_rxChar = 0;
typedef enum {
idSETLED0,
idSETLED1,
idSETLEDS,
idGETLED0,
idGETLED1,
idCLEARLED0,
idCLEARLED1,
idCLEARLEDS,
idCOMMANDS,
idHELP,
idTEXT
} command_type;
/* --------------------------------------------------------------------------
   FUNCTION DECLARATIONS
-------------------------------------------------------------------------- */
void initHardware();
static void prv1SecondTimerCallback(TimerHandle_t xTimer);
/*static void prvTaskSetLED(void *pvLEDn);
static void prvTaskGetLED(void *pvLEDn);
static void vUARTReceiveHandlerTask( void *pvParameters );*/
static void prvTaskPB0(void *pvParam);
static void prvTaskPB1(void *pvParam);
static void prvTaskCharToMessage(void *pvParam);
static void prvTaskCharToMessageDEMUX(void *pvParam);
static void prvTaskUARTRXHandler(void *pvParam);
/* --------------------------------------------------------------------------
   MAIN
-------------------------------------------------------------------------- */

#undef DEBUG

int main(void)
{
	initHardware();
	welcomeText();

	// Initialize FreeRTOS
		// Create semaphores
		semPB0 = xSemaphoreCreateBinary();
		semPB1 = xSemaphoreCreateBinary();
		semUART = xSemaphoreCreateBinary();
		// Create queues
		xCharQueue = xQueueCreate( MESSAGE_BUFFER_LENGTH, sizeof( char ) );
		xMessageQueue = xQueueCreate( MESSAGE_QUEUE_LENGTH, sizeof( uint8_t ) );
		// Create tasks
		xTaskCreate(prvTaskPB0, "", mainTASK_PB0_STACK_SIZE, NULL, mainTASK_PB0_PRIORITY, NULL);
		xTaskCreate(prvTaskPB1, "", mainTASK_PB1_STACK_SIZE, NULL, mainTASK_PB1_PRIORITY, NULL);
		xTaskCreate(prvTaskUARTRXHandler, "", mainTASK_UART_STACK_SIZE, NULL, mainTASK_UART_PRIORITY, NULL);
		xTaskCreate(prvTaskCharToMessage, "", mainTASK_UART_STACK_SIZE, NULL, mainTASK_UART_PRIORITY, NULL);
		xTaskCreate(prvTaskCharToMessageDEMUX, "", mainTASK_UART_STACK_SIZE, NULL, mainTASK_UART_PRIORITY, NULL);
		// Create timer
	    x1SecondTimer = xTimerCreate("1 second auto reload timer", mainTIMER_AUTO_RELOAD_PERIOD, pdTRUE, 0, prv1SecondTimerCallback);
	    // Start scheduler
	    vTaskStartScheduler();
	// Prevent compiler warning
    return 0;
}

void initHardware()
{
	RETARGET_SerialInit();   // Use the serial interface as the standard I/O
	RETARGET_SerialCrLf(1);  // A "\r" or "\n" will be supplemented to "\r\n"
	UDELAY_Calibrate();      // Calibrate software delay loops
	BSP_LedsInit();
	initGPIO();
	SegmentLCD_Init(false);
}

static void prvTaskCharToMessageDEMUX(void * pvParam)
{
	static uint8_t messageID;
	while(pdTRUE)
	{
		xQueueReceive( xMessageQueue, &messageID, portMAX_DELAY );
		#ifdef DEBUG
			printf("prvTaskCharToMessageDEMUX: %d\n", messageID);
		#endif

		printf("\n");
		printf(">>");

		if(messageID == idSETLED0)
		{
			#ifdef DEBUG
				printf("idSETLED0\n");
			#endif
			BSP_LedSet(0);
		}
		else if(messageID == idSETLED1)
		{
			#ifdef DEBUG
				printf("idSETLED1\n");
			#endif
			BSP_LedSet(1);
		}
		else if(messageID == idSETLEDS)
		{
			#ifdef DEBUG
				printf("idSETLEDS\n");
			#endif
			BSP_LedSet(0);
			BSP_LedSet(1);
		}
		else if(messageID == idCLEARLED0)
		{
			#ifdef DEBUG
				printf("idCLEARLED0\n");
			#endif
			BSP_LedClear(0);
		}
		else if(messageID == idCLEARLED1)
		{
			#ifdef DEBUG
				printf("idCLEARLED1\n");
			#endif
			BSP_LedClear(1);
		}
		else if(messageID == idCLEARLEDS)
		{
			#ifdef DEBUG
				printf("idCLEARLEDS\n");
			#endif
			BSP_LedClear(0);
			BSP_LedClear(1);
		}
		else if(messageID == idGETLED0)
		{
			#ifdef DEBUG
				printf("idGETLED0\n");
			#endif
			printf("LED0 is %d\n", BSP_LedGet(0));
		}
		else if(messageID == idGETLED1)
		{
			#ifdef DEBUG
				printf("idGETLED1\n");
			#endif
			printf("LED1 is %d\n", BSP_LedGet(1));
		}
		else if(messageID == idHELP)
		{
			#ifdef DEBUG
				printf("idHELP\n");
			#endif
			print_commands();
		}
		else if(messageID == idTEXT)
		{
			// empty else if case
		}
		else
		{
			printf("Invalid command. :-(\n");
		}

		if(messageID == idTEXT)
		{
			if(xTimerIsTimerActive(x1SecondTimer) == pdFALSE)
			{
				xTimerStart(x1SecondTimer, 0);
			}
			if(eTaskGetState(prv1SecondTimerCallback) == eSuspended)
			{
				vTaskResume(prv1SecondTimerCallback);
			}
		}
		/*
		else
		{
			if(xTimerIsTimerActive(x1SecondTimer) != pdFALSE)
			{
				xTimerStop(x1SecondTimer, 0);
			}
			if(eTaskGetState(prv1SecondTimerCallback) == eRunning)
			{
				vTaskSuspend(prv1SecondTimerCallback);
			}
			memcpy(gc_LCD_text, "CLI   ", LCD_CHARS);
			gc_LCD_text[LCD_CHARS] = '\0';
			SegmentLCD_Write(gc_LCD_text);
		}
		*/
	}
}

// CALLBACK FUNCTION: 1 second auto reload timer
void prv1SecondTimerCallback(TimerHandle_t xTimer)
{
	#ifdef DEBUG_AND_TEST
		printf("prv1SecondTimerCallback\n");
	#endif
	memset(gc_LCD_text, 0, LCD_CHARS + 1);
	if(strlen(scrollingText) > LCD_CHARS)
	{
		memcpy(gc_LCD_text, scrollingText + giStartPosition, LCD_CHARS);
		gc_LCD_text[LCD_CHARS] = '\0';
		SegmentLCD_Write(gc_LCD_text);
		if (giStartPosition >= (strlen(scrollingText) - LCD_CHARS))
		{
			dirRight = 0;
		}
		else if(giStartPosition == 0)
		{
			dirRight = 1;
		}

		if(dirRight == 1)
		{
			giStartPosition++;
		}
		else
		{
			giStartPosition--;
		}
	}
	else
	{
		memcpy(gc_LCD_text, scrollingText, LCD_CHARS);
		gc_LCD_text[LCD_CHARS] = '\0';
		SegmentLCD_Write(gc_LCD_text);
	}

	#ifdef DEBUG_AND_TEST
		printf("Current tick count: %lu\n", xTaskGetTickCount());
	#endif
}

/* --------------------------------------------------------------------------
   FUNCTION DEFINITIONS
-------------------------------------------------------------------------- */
void prvTaskUARTRXHandler(void *pvParam)
{
    while (1)
    {
    	xSemaphoreTake( semUART, portMAX_DELAY );
		#ifdef DEBUG
    		static uint32_t cntrUART = 0;
			printf("prvTaskUARTRXHandler received %c character on position: %lu\n", UART_rxChar, ++cntrUART);
		#endif
			taskENTER_CRITICAL();
				xQueueSendToBack(xCharQueue, (void*)&UART_rxChar, portMAX_DELAY);
			taskEXIT_CRITICAL();
    }
}
/* ----------------------------------------------------------------------- */
void prvTaskCharToMessage(void *pvParam)
{
	static char rxChar;
	static uint8_t command_id = idHELP;
    while (1)
    {
    	/* Block on the queue to wait for data to arrive. */
    	 xQueueReceive( xCharQueue, &rxChar, portMAX_DELAY );
    	 if(rxChar == END_CHAR)
    	 {
			g_message[g_messageSize] = '\0';
			g_messageSize = 0;
			if(strcmp(g_message, SETLED0) == 0)
			{
				command_id = idSETLED0;
			}
			else if(strcmp(g_message, SETLED1) == 0)
			{
				command_id = idSETLED1;
			}
			else if(strcmp(g_message, GETLED0) == 0)
			{
				command_id = idGETLED0;
			}
			else if(strcmp(g_message, GETLED1) == 0)
			{
				command_id = idGETLED1;
			}
			else if(strcmp(g_message, SETLEDS) == 0)
			{
				command_id = idSETLEDS;
			}
			else if(strcmp(g_message, CLEARLED0) == 0)
			{
				command_id = idCLEARLED0;
			}
			else if(strcmp(g_message, CLEARLED1) == 0)
			{
				command_id = idCLEARLED1;
			}
			else if(strcmp(g_message, CLEARLEDS) == 0)
			{
				command_id = idCLEARLEDS;
			}
			else if(strcmp(g_message, GETLED0) == 0)
			{
				command_id = idGETLED0;
			}
			else if(strcmp(g_message, GETLED1) == 0)
			{
				command_id = idGETLED1;
			}
			else if(strcmp(g_message, COMMANDS) == 0 || strcmp(g_message, HELP) == 0)
			{
				command_id = idHELP;
			}
			else
			{
				int i;
				char cArray[5];
				//scrollingFlag = pdFALSE;
				for(i = 0; i < strlen(TEXT); i++)
				{
					cArray[i] = g_message[i];
				}
				cArray[i] = '\0';
				if(strcmp(cArray, TEXT) == 0)
				{
					memset(scrollingText, 0, MESSAGE_BUFFER_LENGTH + 1);
					memcpy(scrollingText, g_message + strlen(TEXT) + 1, strlen(g_message) - strlen(TEXT) - 1);
					printf("\nScroling text command is found with length %d: %s", strlen(g_message) - strlen(TEXT) - 1, scrollingText);
					//scrollingFlag = pdTRUE;
					command_id = idTEXT;
				}
				else
				{
					command_id = 15;
					/*
					memcpy(gc_LCD_text, "CLI   ", LCD_CHARS);
					gc_LCD_text[LCD_CHARS] = '\0';
					SegmentLCD_Write(gc_LCD_text);
					*/
				}
			}
			taskENTER_CRITICAL();
				xQueueSendToBack( xMessageQueue, &command_id, portMAX_DELAY);
			taskEXIT_CRITICAL();
    	 }
    	 else if(rxChar == DELETE_CHAR)
    	 {
    		 if(g_messageSize > 0)
    		 {
    			 g_messageSize--;
    		 }
    	 }
    	 else
    	 {
			#ifdef DEBUG
    		 	 printf("prvTaskCharToMessage received character: %c\n", rxChar);
			#endif
			g_message[g_messageSize] = rxChar;
			g_messageSize++;
    	 }
    }
}
/* ----------------------------------------------------------------------- */
void prvTaskPB0(void *pvParam)
{
static uint32_t cntrPB0 = 0;
    while (1)
    {
    	xSemaphoreTake( semPB0, portMAX_DELAY );
    	printf("PB0 pressed: %lu\n", ++cntrPB0);
    }
}
/* ----------------------------------------------------------------------- */
void prvTaskPB1(void *pvParam)
{
static uint32_t cntrPB1 = 0;
    while (1)
    {
    	xSemaphoreTake(semPB1, portMAX_DELAY);
        printf("PB1 pressed: %lu\n", ++cntrPB1);
    }
}
/* ----------------------------------------------------------------------- */
