/*
 * Board support package API for GPIO push buttons on STK3700A.
 *
 * Created by:        NASZALY Gabor <naszaly@mit.bme.hu>
 * Date (yyyy-mm-dd): 2017-08-30 
 *
 * Based on the source file "bsp_stk_leds.c" (Board support package API for GPIO
 * leds on STK's, version 5.0.0.), copyright 2015 Silicon Labs, Inc. 
 * http://www.silabs.com
 *
 * IMPORTANT NOTE: the next comment block is only for convenience for a possible
 * future inclusion of this file into the SDK by Silicon Labs, Inc. So this file
 * is not currently licensed under the Silabs License Agreement, but it is a
 * derivative work based on a file (bsp_stk_leds.c) which is licensed under the
 * Silabs License Agreement.
*/


/***************************************************************************//**
 * @file
 * @brief Board support package API for GPIO push buttons on STK's.
 * @version 5.2.2
 *******************************************************************************
 * @section License
 * <b>Copyright 2017 Silicon Labs, Inc. http://www.silabs.com</b>
 *******************************************************************************
 *
 * This file is licensed under the Silabs License Agreement. See the file
 * "Silabs_License_Agreement.txt" for details. Before using this software for
 * any purpose, you must agree to the terms of that agreement.
 *
 ******************************************************************************/



#include "em_device.h"
#include "em_cmu.h"
#include "em_gpio.h"
#include "bsp.h"

#if defined( BSP_GPIO_BUTTONS )
/** @cond DO_NOT_INCLUDE_WITH_DOXYGEN */

typedef struct
{
  GPIO_Port_TypeDef   port;
  unsigned int        pin;
} tBtnArray;

static const tBtnArray btnArray[ BSP_NO_OF_BUTTONS ] = BSP_GPIO_BUTTONARRAY_INIT;

int BSP_ButtonsInit(void)
{
  int i;

  CMU_ClockEnable(cmuClock_HFPER, true);
  CMU_ClockEnable(cmuClock_GPIO, true);
  for ( i=0; i<BSP_NO_OF_BUTTONS; i++ )
  {
    GPIO_PinModeSet(btnArray[i].port, btnArray[i].pin, gpioModeInput, 1);
  }
  return BSP_STATUS_OK;
}

uint32_t BSP_ButtonsGet(void)
{
  int i;
  uint32_t retVal, mask;

  for ( i=0, retVal=0, mask=0x1; i<BSP_NO_OF_BUTTONS; i++, mask <<= 1 )
  {
    if (GPIO_PinInGet(btnArray[i].port, btnArray[i].pin))
      retVal |= mask;
  }
  return retVal;
}

int BSP_ButtonGet(int btnNo)
{
  int retVal = BSP_STATUS_ILLEGAL_PARAM;

  if ((btnNo >= 0) && (btnNo < BSP_NO_OF_BUTTONS))
  {
    retVal = (int)GPIO_PinInGet(btnArray[btnNo].port, btnArray[btnNo].pin);
  }
  return retVal;
}

/** @endcond */
#endif  /* BSP_GPIO_BUTTONS */
