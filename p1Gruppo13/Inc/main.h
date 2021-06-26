/**
  ******************************************************************************
  * @file    Templates/Inc/main.h 
  * @author  MCD Application Team
  * @brief   Header for main.c module
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2016 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f3xx_hal.h"
#include "stm32f3_discovery.h"
#include "GUI.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/* Definition for TIMx clock resources ############## MASTER ############## */
#define TIMx                           TIM1
#define TIMx_CLK_ENABLE()              __HAL_RCC_TIM1_CLK_ENABLE()


/* Definition for TIMy clock resources ############## SLAVE ############## */
#define TIMy                           TIM2
#define TIMy_CLK_ENABLE()              __HAL_RCC_TIM2_CLK_ENABLE()

// -----------------------------

/* Definition for DACx clock resources */
#define DACx                            DAC1
#define DACx_CHANNEL_GPIO_CLK_ENABLE()  __HAL_RCC_GPIOA_CLK_ENABLE()

#define DACx_CLK_ENABLE()               __HAL_RCC_DAC1_CLK_ENABLE()
#define DACx_FORCE_RESET()              __HAL_RCC_DAC1_FORCE_RESET()
#define DACx_RELEASE_RESET()            __HAL_RCC_DAC1_RELEASE_RESET()

/* Definition for DACx Channel Pin */
#define DACx_CHANNEL_PIN                GPIO_PIN_4
#define DACx_CHANNEL_GPIO_PORT          GPIOA

/* Definition for DACx's Channel */
#define DACx_CHANNEL                    DAC_CHANNEL_1



/* Definition for TIMx's NVIC */
#define TIMx_IRQn                      TIM1_CC_IRQn
#define TIMx_IRQHandler                TIM1_CC_IRQHandler

/* Definition for TIMy's NVIC */
#define TIMy_IRQn                      TIM2_IRQn
#define TIMy_IRQHandler                TIM2_IRQHandler

//define DMA
//#define	VID_HSIZE		50		// Horizontal resolution (in bytes)
#define	VID_HSIZE		50		// Horizontal resolution (in bytes)
#define	VID_VSIZE		200		// Vertical resolution (in lines)

#define	VID_PIXELS_X	(VID_HSIZE * 8)
#define	VID_PIXELS_Y	VID_VSIZE
#define	VID_PIXELS_XR	(VID_PIXELS_X + 16)
#define	VID_HSIZE_R		(VID_HSIZE + 2)
#define	VTOTAL		(VID_HSIZE + 2)



/* Definition for TIMx Channel Pins 
#define TIMx_CHANNEL_GPIO_PORT         __HAL_RCC_GPIOA_CLK_ENABLE();
#define TIMx_GPIO_PORT_CHANNEL1        GPIOE
#define TIMx_GPIO_PORT_CHANNEL2        GPIOE
#define TIMx_GPIO_PORT_CHANNEL3        GPIOE
#define TIMx_GPIO_PORT_CHANNEL4        GPIOE
#define TIMx_GPIO_PIN_CHANNEL1         GPIO_PIN_9
#define TIMx_GPIO_PIN_CHANNEL2         GPIO_PIN_11
#define TIMx_GPIO_PIN_CHANNEL3         GPIO_PIN_13
#define TIMx_GPIO_PIN_CHANNEL4         GPIO_PIN_14
#define TIMx_GPIO_AF_CHANNEL1          GPIO_AF2_TIM1
#define TIMx_GPIO_AF_CHANNEL2          GPIO_AF2_TIM1
#define TIMx_GPIO_AF_CHANNEL3          GPIO_AF2_TIM1
#define TIMx_GPIO_AF_CHANNEL4          GPIO_AF2_TIM1
*/

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

#define XSIZE_PHYS  416
#define YSIZE_PHYS  200
#define BYTES_PER_LINE ((XSIZE_PHYS + 7) / 8)




#endif /* __MAIN_H */




/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
