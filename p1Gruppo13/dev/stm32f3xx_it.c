/**
  ******************************************************************************
  * @file    Templates/Src/stm32f3xx_it.c
  * @author  MCD Application Team
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
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
#include "stm32f3xx_it.h"
#include <stdio.h>
    
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
extern TIM_HandleTypeDef    TimHandle1;
extern TIM_HandleTypeDef    TimHandle2;

// per l'SPI e DMA
extern SPI_HandleTypeDef	SpiHandle;

static volatile uint16_t vline = 0;				/* The current line being drawn */
static volatile uint32_t vflag = 0;				/* When 1, the SPI DMA request can draw on the screen */
static volatile uint32_t vdraw = 0;				/* Used to increment vline every 3 drawn lines */
extern U8 _aPlain_0[52 * 200];

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/




/******************************************************************************/
/*            Cortex-M4 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief   This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
  HAL_IncTick();
}

/******************************************************************************/
/*                 STM32F3xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) , for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f3xx.s).                                               */
/******************************************************************************/


/**
  * @brief  This function handles TIM interrupt request.
  * @param  None
  * @retval None
  */


/* Interruzioni DMA1 Canale 3 */

void DMA1_Channel3_IRQHandler(void){
	
	/* Abbassiamo bit dell'interruzizione e disabilitiamo il DMA
	successivamente inseriamo il numero totale di byte da trasferire */
	
  DMA1->IFCR |= DMA_IFCR_CTCIF3; // Clear Transfer Complete Interrupt Flag del canale 3
  DMA1_Channel3->CCR = 0x92;

  DMA1_Channel3->CNDTR = VTOTAL; // Indica il numero di trasferimenti da effettuare, ovvero il numero di byte contenuti nella riga 
  vdraw++;
	
	if (vdraw == 3)			// stampiamo 3 volte la stessa riga
	{
		vdraw = 0;

		vline++;			// incremento numero di linee inviate
		
		/* Se il numero di righe inviate è pari al totale delle righe del frame, allora abbiamo inviato un intero frame */
		
		if (vline == VID_VSIZE)
		{
			vdraw = vline = vflag = 0;
			DMA1_Channel3->CMAR = (uint32_t) &_aPlain_0[0]; // Matrice contenente i dati dei pixel -> si ricomincia dalla locazione iniziale (0) del frame buffer
		} else {
			DMA1_Channel3->CMAR += VTOTAL;
		}
	}
	
}

/* Interruzioni TIM1 e TIM2 */

void TIMx_IRQHandler(void)
{
	// Questa interruzione viene richiamata al termine della back porch orizzontale
if(vflag){
   		 // Se non ci si trova nella regione di blanking verticale -> viene abilitato il DMA
          DMA1_Channel3->CCR |= 0x93;  // abilitazione DMA

		}
		
  TIM1->SR &= ~TIM_SR_CC2IF;		// abbassa flag interruzione

}

void TIMy_IRQHandler(void)
{
  // Questa interruzione si attiva al termine della back porch verticale
vflag= 1;						// indica il termine della regione di blanking
TIM2->SR &= ~TIM_SR_CC3IF;		// abbassa flag interruzione

}



/**
  * @}
  */ 

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
