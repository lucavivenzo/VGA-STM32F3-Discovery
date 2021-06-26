/*********************************************************************
*                SEGGER Microcontroller GmbH & Co. KG                *
*        Solutions for real time microcontroller applications        *
**********************************************************************
*                                                                    *
*        (c) 1996 - 2017  SEGGER Microcontroller GmbH & Co. KG       *
*                                                                    *
*        Internet: www.segger.com    Support:  support@segger.com    *
*                                                                    *
**********************************************************************

** emWin V5.44 - Graphical user interface for embedded applications **
All  Intellectual Property rights  in the Software belongs to  SEGGER.
emWin is protected by  international copyright laws.  Knowledge of the
source code may not be used to write a similar product.  This file may
only be used in accordance with the following terms:

The  software has  been licensed  to STMicroelectronics International
N.V. a Dutch company with a Swiss branch and its headquarters in Plan-
les-Ouates, Geneva, 39 Chemin du Champ des Filles, Switzerland for the
purposes of creating libraries for ARM Cortex-M-based 32-bit microcon_
troller products commercialized by Licensee only, sublicensed and dis_
tributed under the terms and conditions of the End User License Agree_
ment supplied by STMicroelectronics International N.V.
Full source code is available at: www.segger.com

We appreciate your understanding and fairness.
----------------------------------------------------------------------
File        : LCDConf.c
Purpose     : Display controller configuration (single layer)
---------------------------END-OF-HEADER------------------------------
*/

/**
  ******************************************************************************
  * @file    LCDConf_stm32303c_eval.c
  * @author  MCD Application Team
  * @brief   Driver for STM32303C-EVAL RevC board LCD
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2018 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */

#include "GUI.h"
#include "GUIDRV_BitPlains.h"
#include "main.h"


/*********************************************************************
*
*       Layer configuration (to be modified)
*
**********************************************************************
*/

//
// Physical display size messo in main.h
//
//#define XSIZE_PHYS  416
//#define YSIZE_PHYS  200

//#define COLOR_CONVERSION GUICC_1 serve? se lo metti devi cambiare la ifndef sotto

/*********************************************************************
*
*       Configuration checking
*
**********************************************************************
*/
#ifndef   VXSIZE_PHYS
#define VXSIZE_PHYS XSIZE_PHYS
#endif
#ifndef   VYSIZE_PHYS
#define VYSIZE_PHYS YSIZE_PHYS
#endif
#ifndef   XSIZE_PHYS
#error Physical X size of display is not defined!
#endif
#ifndef   YSIZE_PHYS
#error Physical Y size of display is not defined!
#endif
#ifndef   GUICC_1
#error Color conversion not defined!
#endif

/*********************************************************************
*
*       Defines, sfrs
*
**********************************************************************
*/

//
// Number of bytes per line messo in main.h
//
//#define BYTES_PER_LINE ((XSIZE_PHYS + 7) / 8)

//
// Data arrays to be used by the display driver
//
//static U8 _aPlain_0[BYTES_PER_LINE * YSIZE_PHYS];
U8 _aPlain_0 [BYTES_PER_LINE * YSIZE_PHYS];
//
// Structure to be passed to the driver
//
static struct {
  U8 * apVRAM[8];
} _VRAM_Desc = {{
  _aPlain_0,
}};



/*********************************************************************
*
*       Public functions
*
**********************************************************************
*/

/**
  * @brief  Initializes the LCD.
  * @param  None
  * @retval LCD state
  */

/*********************************************************************
*
*       LCD_X_Config
*
* Function description:
*   Called during the initialization process in order to set up the
*   display driver configuration.
*
*/
void LCD_X_Config(void)
{
  GUI_DEVICE *pDevice;
  CONFIG_BITPLAINS *pConfig;
  //pConfig->Mirror=1;
  //
  // Set display driver and color conversion
  //
  pDevice = GUI_DEVICE_CreateAndLink(GUIDRV_BITPLAINS, GUICC_1, 0, 0);
    
  GUIDRV_BitPlains_Config(pDevice, pConfig);
  //
  // Display driver configuration, required for Lin-driver
  //
   if (LCD_GetSwapXY())
  {
    LCD_SetSizeEx (0, YSIZE_PHYS, XSIZE_PHYS);
    LCD_SetVSizeEx(0, YSIZE_PHYS, XSIZE_PHYS);
  }
  else
  {
    LCD_SetSizeEx (0, XSIZE_PHYS, YSIZE_PHYS);
    LCD_SetVSizeEx(0, XSIZE_PHYS, YSIZE_PHYS);
  }
  //
  // Initialize VRAM access off driver
  //
  LCD_SetVRAMAddrEx(0, (void *)&_VRAM_Desc); // a che serve?
}

/*********************************************************************
*
*       LCD_X_DisplayDriver
*
* Function description:
*   This function is called by the display driver for several purposes.
*   To support the according task the routine needs to be adapted to
*   the display controller. Please note that the commands marked with
*   'optional' are not cogently required and should only be adapted if
*   the display controller supports these features.
*
* Parameter:
*   LayerIndex - Index of layer to be configured
*   Cmd        - Please refer to the details in the switch statement below
*   pData      - Pointer to a LCD_X_DATA structure
*
* Return Value:
*   < -1 - Error
*     -1 - Command not handled
*      0 - Ok
*/
int LCD_X_DisplayDriver(unsigned LayerIndex, unsigned Cmd, void *pData)
{
  int r;
  (void) LayerIndex;
  (void) pData;

  switch (Cmd)
  {
    case LCD_X_INITCONTROLLER:
    {

      

      return 0;
    }
    default:
      r = -1;
  }
  return r;
}


/*************************** End of file ****************************/

