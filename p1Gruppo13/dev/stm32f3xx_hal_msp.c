/**
  ******************************************************************************
  * @file    Templates/Src/stm32f3xx_hal_msp.c
  * @author  MCD Application Team
  * @brief   HAL MSP module.
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

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/** @addtogroup STM32F3xx_HAL_Examples
  * @{
  */

/** @addtogroup Templates
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static DMA_HandleTypeDef hdma_tx;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup HAL_MSP_Private_Functions
  * @{
  */

/**
  * @brief  Initializes the Global MSP.
  * @param  None
  * @retval None
  */
void HAL_MspInit(void)
{
   
}

/**
  * @brief  DeInitializes the Global MSP.
  * @param  None  
  * @retval None
  */
void HAL_MspDeInit(void)
{
  
}



void HAL_TIM_OC_MspInit(TIM_HandleTypeDef *htim)
{
  GPIO_InitTypeDef GPIO_InitStruct;
  /*##-1- Enable peripherals and GPIO Clocks #################################*/
  
  /* TIMx and TIMy Peripheral clock enable */
  TIMx_CLK_ENABLE();
  
  TIMy_CLK_ENABLE();
  
  // ENABLE GPIO CHANNEL'S CLOCK
  __HAL_RCC_GPIOA_CLK_ENABLE();
  
  //GPIO
  GPIO_InitStruct.Pin = GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF1_TIM2;

  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  // IL PIN8 è RELATIVO AL TIMER1, PIN1 RELATIVO AL TIMER 2

  GPIO_InitStruct.Pin = GPIO_PIN_8;
  GPIO_InitStruct.Alternate = GPIO_AF6_TIM1;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*##-2- Configure the NVIC for TIMx and TIMy ########################################*/
  
  /* Set Interrupt Group Priority */ 
  
   HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_2);

  HAL_NVIC_SetPriority(TIMx_IRQn, 1, 0);

  /* Enable the TIMx global Interrupt */
  HAL_NVIC_EnableIRQ(TIMx_IRQn);
  
  
  /* Set Interrupt Group Priority */ 
  HAL_NVIC_SetPriority(TIMy_IRQn, 1, 0);

  /* Enable the TIMy global Interrupt */
  HAL_NVIC_EnableIRQ(TIMy_IRQn);
  
}





/* MSP INIT e DEINIT della SPI */

void HAL_SPI_MspInit(SPI_HandleTypeDef *hspi){
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_SPI1_CLK_ENABLE();
	
	__HAL_RCC_DMA1_CLK_ENABLE();
	
	GPIO_InitTypeDef GPIO_InitStruct;
	
	GPIO_InitStruct.Pin = GPIO_PIN_5;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF5_SPI1;

	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	hdma_tx.Instance = DMA1_Channel3;
	hdma_tx.Init.Direction = DMA_MEMORY_TO_PERIPH; // Modalità memoria - periferica
	hdma_tx.Init.PeriphInc = DMA_PINC_DISABLE;
	hdma_tx.Init.MemInc = DMA_MINC_ENABLE; // Incrementa automaticamente il puntatore alla memoria
	hdma_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
	hdma_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
	hdma_tx.Init.Mode = DMA_NORMAL;
	hdma_tx.Init.Priority = DMA_PRIORITY_HIGH;
	
	
	HAL_DMA_Init(&hdma_tx);
	
	__HAL_LINKDMA(hspi, hdmatx, hdma_tx);
	
	HAL_NVIC_SetPriority(DMA1_Channel3_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(DMA1_Channel3_IRQn);
        
	
}

void HAL_SPI_MspDeInit(SPI_HandleTypeDef *hspi){
    
  __HAL_RCC_SPI1_FORCE_RESET();
  __HAL_RCC_SPI1_RELEASE_RESET();

    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_5);
    
    HAL_DMA_Init(&hdma_tx);
    
    HAL_NVIC_DisableIRQ(DMA1_Channel3_IRQn); 
}



/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
