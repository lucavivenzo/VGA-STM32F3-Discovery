/**
  ******************************************************************************
  * @file    Templates/Src/main.c 
  * @author  MCD Application Team
  * @brief   Main program body
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
#include <stdio.h>

/** @addtogroup STM32F3xx_HAL_Examples
  * @{
  */

/** @addtogroup Templates
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
#define  PULSE1_VALUE      144        /* Capture Compare 1 Value - qui ci va l'HSYNC: (SystemCoreClock/13889) / 2  */
#define  PULSE2_VALUE      400        /* Capture Compare 2 Value - qui ci va l'HSYNC + BACKPORCH: (SystemCoreClock/5000) / 2  */

#define  PULSE_TIM2_2       2           /* SYNC PULSE PER TIMER 2 CANALE 2 - V-SYNC */
#define  PULSE_TIM2_3       24          /* SYNC PULSE + BACKPORCH PER TIMER 2 CANALE 3 - V-SYNC + BACKPORCH*/


/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
    

GPIO_InitTypeDef GPIO_InitStruct;

extern U8 _aPlain_0[BYTES_PER_LINE * YSIZE_PHYS]; // Matrice contente i dati dei Pixel. Settata come "extern" perchè serve anche al file di config delle Stemwin
extern GUI_CONST_STORAGE GUI_BITMAP bmstm32logo;
extern GUI_CONST_STORAGE GUI_BITMAP bmeslogo;



/* Timer handler declaration --> serve per inizializzazione timer --> UTILIZZATA PER TIMER*/
TIM_HandleTypeDef    TimHandle1;
TIM_HandleTypeDef    TimHandle2;

//SPI handler declaration
SPI_HandleTypeDef SpiHandle;

/* Timer Output Compare Configuration Structure declaration --> UTILIZZATA PER TIMER*/
TIM_OC_InitTypeDef sConfigTIM;


/* Counter Prescaler value --> serve per il prescaler */
uint32_t uwPrescalerValue = 0;

TIM_MasterConfigTypeDef sMasterConfig; // per Master
TIM_SlaveConfigTypeDef sSlaveConfig; // per Slave


/* Private function prototypes -----------------------------------------------*/
static void SystemClock_Config(void);
static void Error_Handler(void);

void TIMERConfiguration(void);
void SPIConfiguration(void);

void GPIOSetup(void);

void setup_ADC(void);
void enableButton(void);


/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{
  


  /* STM32F3xx HAL library initialization:
       - Configure the Flash prefetch
       - Systick timer is configured by default as source of time base, but user 
         can eventually implement his proper time base source (a general purpose 
         timer for example or other time source), keeping in mind that Time base 
         duration should be kept 1ms since PPP_TIMEOUT_VALUEs are defined and 
         handled in milliseconds basis.
       - Set NVIC Group Priority to 4
       - Low Level Initialization
     */


  HAL_Init();
  
 

  /* Configure the system clock to have a system clock = 72 Mhz */
  SystemClock_Config();


  /* Add your application code here*/
  
  enableButton();
   

  SPIConfiguration();
  
  TIMERConfiguration ();
  /* Init the STemWin GUI Library */
  GUI_Init(); /* Inizializzazione che richiama le funzioni di configurazione, ad esempio:
  GUI_X_Config(): assegna la memoria a STemWin
  LCD_X_Config(): crea il Display Driver, realizza l'interfacciamento tra libreria e Display Controller
  LCD_X_DisplayDriver(): mette in funzione il display controller
  */
  GUI_SetFont(&GUI_Font32B_1); 
  uint8_t state=0;	  
  int xposizione = -30;
  int yposizione = 150;
  int CountMin =0;
  int CountSec =0;
  int CountMill =0;
	GUI_HMEM qr;

   while(1)
   {
       
	
    if((GPIOA->IDR & GPIO_IDR_0) == GPIO_IDR_0){			// Controllo se il bottone è stato premuto
		while((GPIOA->IDR & GPIO_IDR_0) == GPIO_IDR_0);		// Attendiamo che il bottone venga rilasciato
		GUI_Clear(); //Ripulisce il display
		state=(state+1)%4;
		switch(state){
			
			
			case 0:
			// GUI_DispStringAt(): funzione che disegna una specifica stringa nella posizione indicata
				GUI_DispStringAt("Gruppo 13: ",0,0);
				GUI_DispStringAt("Carmine Marra",0,34);
				GUI_DispStringAt("Francesco Maria Papulino",0,68);
				GUI_DispStringAt("Simone Staiano",0,102);
				GUI_DispStringAt("Luca Vivenzo",0,136);
				
			break;
			case 1:
				for (int i =0; i<20; i++){
				HAL_Delay(10);
				GUI_Clear();
				
				//GUI_DrawBitmap(): disegna uno specifico bitmap
				GUI_DrawBitmap(&bmstm32logo,xposizione,0);
				GUI_DrawBitmap(&bmeslogo,200,yposizione);
				xposizione+=4;
				yposizione-=7;
				}
				xposizione = -30;
				yposizione = 150;
				
				// GUI_FillRect(): disegna un rettangolo pieno
				GUI_FillRect(151,96,241,186);
				GUI_SetColor(GUI_BLACK);
				
				// GUI_QR_Create(): crea un QR Code di tipo bitmap che può essere poi disegnato con GUI_QR_Draw()
				qr = GUI_QR_Create("http://www.naplespu.com/es/index.php?title=Main_Page",2,GUI_QR_ECLEVEL_H,0);
				GUI_QR_Draw(qr,155,100);//41 moduli
				GUI_SetColor(GUI_WHITE);
                               
			break;
            case 2 :   
				GUI_DrawRoundedRect(95,83,273,116,3);
				GUI_DrawRoundedRect(91,79,277,120,4);
				while(!((GPIOA->IDR & GPIO_IDR_0) == GPIO_IDR_0)){

				GUI_DispDecAt(CountMin, 100, 84, 2);
				GUI_DispStringAt(" : ", 140, 84);
				GUI_DispDecAt(CountSec, 170, 84, 2);
				GUI_DispStringAt(" : ", 210, 84);
				GUI_DispDecAt(CountMill, 240, 84, 2);	
				HAL_Delay(5);
				CountMill=(CountMill+1)%100;
				if (CountMill== 0){
					CountSec=(CountSec+1)%60;
					if (CountSec== 0){
						CountMin= (CountMin+1)%60;
                            }
                        }
                            
                         
                          }

                         
			break;  
			case 3 :     
				GUI_DrawRoundedRect(95,83,273,116,3);
				GUI_DrawRoundedRect(91,79,277,120,4);
				GUI_DispDecAt(CountMin, 100, 84, 2);
				GUI_DispStringAt(" : ", 140, 84);
				GUI_DispDecAt(CountSec, 170, 84, 2);
				GUI_DispStringAt(" : ", 210, 84);
				GUI_DispDecAt(CountMill, 240, 84, 2);
				CountMin =0;
				CountSec =0;
				CountMill =0;
			break;	
				
		
		}
	  
  }
}
}


// La funzione enableButton serve a configurare il bottone utilizzato per selezionare le diverse modalità di esecuzione del programma

void enableButton(){
	__HAL_RCC_GPIOA_CLK_ENABLE(); //Enable clock to GPIOA
	GPIO_InitTypeDef PushButton;  // declare a variable of type struct GPIO_InitTypeDef
	PushButton.Mode = GPIO_MODE_INPUT; // set pin mode to input
	PushButton.Pin = GPIO_PIN_0;  // select pin PA0 only
	PushButton.Pull = GPIO_NOPULL; // set no internal pull-up or pull-down resistor
	HAL_GPIO_Init(GPIOA, &PushButton); //  initialize PA0 pins by passing port name and address of BoardLEDs struct
}


/* ----------------------------------------------SEZIONE TIMER----------------------------------------------*/

void TIMERConfiguration (){
  
  uwPrescalerValue = 0; 
  
  /*##-1- Configure the TIM peripheral #######################################*/ 
  /* Initialize TIM1 peripheral as follow:
       + Prescaler = 0; 
       + Period = 2048 ---> 72 MHz * 28.44 µs = 2048 colpi
       + ClockDivision = 0
       + Counter direction = Up
  */
  TimHandle1.Instance = TIM1;
  
  TimHandle1.Init.Period        = 2048;
  TimHandle1.Init.Prescaler     = uwPrescalerValue;
  TimHandle1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1; // impostata a 0
  TimHandle1.Init.CounterMode   = TIM_COUNTERMODE_UP; // modalità di conteggio verso incrementale
  TimHandle1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  TimHandle1.Init.RepetitionCounter = 0;
  
  HAL_TIM_OC_Init(&TimHandle1); // Inizializzazione della modalità OUTPUT COMPARE per il TIM1
  
  /*##-2- Configure the Output Compare channels #########################################*/ 
  /* Common configuration for all channels */
  //Vanno configurati il canale 1 e il canale 2 sia del TIM1 (MASTER) che TIM2 (SLAVE)
  
  sConfigTIM.OCMode     = TIM_OCMODE_PWM2; // Con la modalità PWM2 il canale rimane inattivo finchè il valore di CR è inferiore a quello di CCR
  sConfigTIM.OCPolarity = TIM_OCPOLARITY_LOW; // Polarità bassa
  
  /* Set the pulse (delay1)  value for channel 1 */
  sConfigTIM.Pulse = PULSE1_VALUE; // Si setta il valore del CCR pari a 144 (canale 1: H-SYNC)

  sConfigTIM.OCNPolarity = TIM_OCNPOLARITY_LOW; 
  sConfigTIM.OCIdleState = TIM_OCIDLESTATE_RESET; 
  sConfigTIM.OCNIdleState = TIM_OCNIDLESTATE_RESET; 
  
  
  HAL_TIM_OC_ConfigChannel(&TimHandle1, &sConfigTIM, TIM_CHANNEL_1); // Configurazione channel 1
  
  /* Set the pulse (delay2)  value for channel 2 */
  
  sConfigTIM.Pulse = PULSE2_VALUE;  // Si setta il valore del CCR pari a 400 (canale 2: H-SYNC + BACKPORCH)
  HAL_TIM_OC_ConfigChannel(&TimHandle1, &sConfigTIM, TIM_CHANNEL_2); // Configurazione channel 2

  
  // #### CONFIGURAZIONE MASTER ####
  
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_ENABLE; // Selezione modalità MASTER
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE; // Attivazione trigger di output che andrà in ingresso al TIM2
  HAL_TIMEx_MasterConfigSynchronization(&TimHandle1, &sMasterConfig); // Configurazione MASTER

  // #### CONFIGURAZIONE TIM2 ####
  
  TimHandle2.Instance = TIM2;
  
   /*##-1- Configure the TIM peripheral #######################################*/ 
  /* Initialize TIM2 peripheral as follow:
       + Prescaler = 0; 
       + Period = 625 ---> l'abilitazione arriva dal TIM1 (channel 1), 625 sono le righe da trasmettere
       + ClockDivision = 0
       + Counter direction = Up
  */
  
  TimHandle2.Init.Period        = 625;
  TimHandle2.Init.Prescaler     = 0;
  TimHandle2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1; // impostata di 0
  TimHandle2.Init.CounterMode   = TIM_COUNTERMODE_UP; // modalità di conteggio incrementale
  TimHandle2.Init.RepetitionCounter = 0; 
  
  HAL_TIM_OC_Init(&TimHandle2); // Inizializzazione della modalità OUTPUT COMPARE per il TIM2
  
  /* La struttura sConfigTIM mantiene ancora le impostazioni precedenti, come ad esempio la
  modalità PWM2 e la POLARITY_LOW */
  
  /* Set the pulse value for channel 2 */
  sConfigTIM.Pulse = PULSE_TIM2_2; // Si setta il valore del CCR pari a 2, ovvero la durata di V-SYNC in funzione delle righe (canale 2: V-SYNC) 
    
  HAL_TIM_OC_ConfigChannel(&TimHandle2, &sConfigTIM, TIM_CHANNEL_2); // Configurazione channel 2
  
  // #### ADESSO CANALE 3 ####
  
  sConfigTIM.OCMode = TIM_OCMODE_INACTIVE;
  sConfigTIM.Pulse = PULSE_TIM2_3; // Si setta il valore del CCR pari a 24 (canale 3: V-SYNC +  BACKPORCH) 
  
  HAL_TIM_OC_ConfigChannel(&TimHandle2, &sConfigTIM, TIM_CHANNEL_3); // Configurazione channel 3
  
  sSlaveConfig.SlaveMode = TIM_SLAVEMODE_GATED; // Selezione modalità SLAVE
  sSlaveConfig.InputTrigger = TIM_TS_ITR0; // Si attiva il trigger interno in input, così da sfruttare il trigger in uscita dal TIM1
  
  HAL_TIM_SlaveConfigSynchro(&TimHandle2, &sSlaveConfig); // Configurazione SLAVE
  
  
 //TEROICAMENTE SI DOVREBBERO UTILIZZARE START SENZA IT PER I CANALI CHE NON LANCIANO INTERRUZIONI
  TimHandle1.Instance = TIM1;
  HAL_TIM_OC_Start(&TimHandle1, TIM_CHANNEL_1);
  TimHandle1.Instance = TIM1;
  HAL_TIM_OC_Start_IT(&TimHandle1, TIM_CHANNEL_2);
  
  TimHandle2.Instance = TIM2;
  HAL_TIM_OC_Start(&TimHandle2, TIM_CHANNEL_2);
  TimHandle2.Instance = TIM2;
  HAL_TIM_OC_Start_IT(&TimHandle2, TIM_CHANNEL_3);
  
  
}



  

/* ---------------------------------------------FINE SEZIONE TIMER----------------------------------------------*/
 
/*---------------------------------SEZIONE SPI-------------------------------------------*/

void SPIConfiguration(){
  
  // Inizializzazione della struttura relativa alla configurazione dell'SPI
  
  SpiHandle.Instance = SPI1; 
  SpiHandle.Init.Direction = SPI_DIRECTION_1LINE; // Selezione della modalità HALF-DUPLEX. Considerando che il bit RXONLY non viene modificato, sarà sempre il master ad inviare
  SpiHandle.Init.Mode = SPI_MODE_MASTER; // Selezione della modalità MASTER 
  SpiHandle.Init.DataSize = SPI_DATASIZE_8BIT; 
  SpiHandle.Init.CLKPolarity = SPI_POLARITY_LOW; //  Imposta CPOL a 0. Il clock, nel suo stato di riposo, si porta a livello logico basso
  SpiHandle.Init.CLKPhase = SPI_PHASE_2EDGE;  //Imposta CPHA ad 1, campionando sul fronte di discesa del clock (poichè CPOL = 0)
  SpiHandle.Init.NSS = SPI_NSS_SOFT; // Con questa configurazione, il segnale NSS è pilotato internamente. Bisogna tener presente che l'SPI è configurato in modalità Master.
  SpiHandle.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4; // Divide la frequenza di 1/4, passando da 72MHz a 18MHz. Inviando due pixel uguali alla volta, è come
  															 // se si avesse in realtà una frequenza di 36MHz, come indicato dallo standard adottato.
  SpiHandle.Init.FirstBit = SPI_FIRSTBIT_MSB; // Il primo bit trasmesso è il MSB
  SpiHandle.Init.CRCPolynomial = 7; 
  SpiHandle.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE; // Calcolo CRC disabilitato

  HAL_SPI_Init(&SpiHandle);
  
  SPI1->CR2 |= 3; 
  
  // Avvia la trasmissione con il DMA
  
  HAL_SPI_Transmit_DMA(&SpiHandle,(uint8_t *)&_aPlain_0[0], VTOTAL); 
  
  DMA1_Channel3->CCR &= ~1; // Come indicato sul Datasheet, è possibile collegare l'SPI1 con il canale 3 del DMA1
  
}

/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow : 
  *            System Clock source            = PLL (HSE)
  *            SYSCLK(Hz)                     = 72000000
  *            HCLK(Hz)                       = 72000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 2
  *            APB2 Prescaler                 = 1
  *            HSE Frequency(Hz)              = 8000000
  *            HSE PREDIV                     = 1
  *            PLLMUL                         = RCC_PLL_MUL9 (9)
  *            Flash Latency(WS)              = 2
  * @param  None
  * @retval None
  */
static void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;
  
  //Enable HSE Oscillator and activate PLL with HSE as source 
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct)!= HAL_OK)
  {
    Error_Handler();
  }

  //Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 
   //  clocks dividers 
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;  
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2)!= HAL_OK)
  {
    Error_Handler();
  }
}

static void Error_Handler(void)
{
  /* User may add here some code to deal with this error */
 while(1)
  {
    //BSP_LED_Toggle(LED4); 
    HAL_Delay(1000);
    
  }
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
 
  }
}
#endif



/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
