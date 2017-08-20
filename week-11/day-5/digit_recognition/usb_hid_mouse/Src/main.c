/**
 ******************************************************************************
 * @file    USB_Device/HID_Standalone/Src/main.c
 * @author  MCD Application Team
 * @version V1.2.0
 * @date    30-December-2016
 * @brief   USB device HID demo main file
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2016 STMicroelectronics International N.V.
 * All rights reserved.</center></h2>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted, provided that the following conditions are met:
 *
 * 1. Redistribution of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of STMicroelectronics nor the names of other
 *    contributors to this software may be used to endorse or promote products
 *    derived from this software without specific written permission.
 * 4. This software, including modifications and/or derivative works of this
 *    software, must execute solely and exclusively on microcontroller or
 *    microprocessor devices manufactured by or for STMicroelectronics.
 * 5. Redistribution and use of this software other than as permitted under
 *    this license is void and will automatically terminate your rights under
 *    this license.
 *
 * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
 * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT
 * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include <math.h>


/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
//#define DIGIT_TEST		//test stored digit image
#define WEIGHT_THRESHOLD 10
#define MATCH_THRESHOLD 10
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint8_t digit_text[10][2] = {
		"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"
};
uint8_t mode;
uint8_t x_coord;
uint8_t y_coord;
uint8_t ind;

uint8_t digit_im_weights[10][130][130];
uint16_t match_cntr[10];

/* Private function prototypes -----------------------------------------------*/
static void SystemClock_Config(void);
static void Error_Handler(void);
static void CPU_CACHE_Enable(void);
void training_init();
void menu_init();
void recognize_init();
void clear_area(uint16_t x_pos, uint16_t y_pos, uint16_t width, uint16_t height);

/* Private functions ---------------------------------------------------------*/

/**
 * @brief  Main program
 * @param  None
 * @retval None
 */
int main(void) {
	/* Enable the CPU Cache */
	CPU_CACHE_Enable();

	/* STM32F7xx HAL library initialization:
	 - Configure the Flash ART accelerator on ITCM interface
	 - Configure the Systick to generate an interrupt each 1 msec
	 - Set NVIC Group Priority to 4
	 - Low Level Initialization
	 */
	HAL_Init();

	/* Configure the System clock to have a frequency of 216 MHz */
	SystemClock_Config();

	/* Configure LED1 */
	BSP_LED_Init(LED1);

	/* Initialize LCD screen */
	BSP_LCD_Init();
	BSP_LCD_LayerDefaultInit(1, LCD_FB_START_ADDRESS);
	BSP_LCD_SelectLayer(1);
	BSP_LCD_DisplayOn();

	/* Initialize touchscreen */
	BSP_TS_Init(480, 272);

	/* Initialize push button */
	BSP_PB_Init(BUTTON_KEY, BUTTON_MODE_GPIO);

	//set stored image structures to 0
	for (int s = 0; s < 10; s++) {
		for(int i = 0; i < 130; i++) {
			for (int j = 0; j < 130; j++) {
				digit_im_weights[s][i][j] = 0;
			}
		}
	}
	menu_init();
	mode = 0;
	while (1) {
		TS_StateTypeDef TS_State;
		BSP_TS_GetState(&TS_State);
		HAL_Delay(10);

		if (mode == 0) {
			if (TS_State.touchX[0] >= 154 && TS_State.touchX[0] <= 326 &&
													TS_State.touchY[0] >= 40 && TS_State.touchY[0] <= 126) {
				mode = 1;																			//train mode
				training_init();
			} else 	if (TS_State.touchX[0] >= 154 && TS_State.touchX[0] <= 326 &&
															TS_State.touchY[0] >= 146 && TS_State.touchY[0] <= 232) {
				mode = 2;																		//recognize mode
				recognize_init();
			}
		}
		BSP_TS_GetState(&TS_State);


		//IF IN "TRAIN" MODE
		if (mode == 1) {
			//if push button is pressed
			if (BSP_PB_GetState(BUTTON_KEY) == 1) {
				HAL_Delay(100);
				menu_init();
				mode = 0;
			}
			//if "0" selected
			if (TS_State.touchX[0] >= 301 && TS_State.touchX[0] <= 451 &&
									TS_State.touchY[0] >= 80 && TS_State.touchY[0] <= 110) {
				ind = 0;
			}
			//if "1" selected
			if (TS_State.touchX[0] >= 301 && TS_State.touchX[0] <= 351 &&
									TS_State.touchY[0] >= 110 && TS_State.touchY[0] <= 160) {
				ind = 1;
			}
			//if "2" selected
			if (TS_State.touchX[0] >= 351 && TS_State.touchX[0] <= 401 &&
									TS_State.touchY[0] >= 110 && TS_State.touchY[0] <= 160) {
				ind = 2;
			}
			//if "3" selected
			if (TS_State.touchX[0] >= 401 && TS_State.touchX[0] <= 451 &&
									TS_State.touchY[0] >= 110 && TS_State.touchY[0] <= 160) {
				ind = 3;
			}
			//if "4" selected
			if (TS_State.touchX[0] >= 301 && TS_State.touchX[0] <= 351 &&
									TS_State.touchY[0] >= 160 && TS_State.touchY[0] <= 210) {
				ind = 4;
			}
			//if "5" selected
			if (TS_State.touchX[0] >= 351 && TS_State.touchX[0] <= 401 &&
									TS_State.touchY[0] >= 160 && TS_State.touchY[0] <= 210) {
				ind = 5;
			}
			//if "6" selected
			if (TS_State.touchX[0] >= 401 && TS_State.touchX[0] <= 451 &&
									TS_State.touchY[0] >= 160 && TS_State.touchY[0] <= 210) {
				ind = 6;
				}
			//if "7" selected
			if (TS_State.touchX[0] >= 301 && TS_State.touchX[0] <= 351 &&
									TS_State.touchY[0] >= 210 && TS_State.touchY[0] <= 260) {
				ind = 7;
			}
			//if "8" selected
			if (TS_State.touchX[0] >= 351 && TS_State.touchX[0] <= 401 &&
									TS_State.touchY[0] >= 210 && TS_State.touchY[0] <= 260) {
				ind = 8;
			}
			//if "9" selected
			if (TS_State.touchX[0] >= 401 && TS_State.touchX[0] <= 451 &&
									TS_State.touchY[0] >= 210 && TS_State.touchY[0] <= 260) {
				ind = 9;
			}


			//display selected digit
			BSP_LCD_DisplayStringAt(124, 40, digit_text[ind], LEFT_MODE);

			//if touch is within drawing area, draw ellipse and save coordinates
			if (TS_State.touchX[0] >= 76 && TS_State.touchX[0] <= 196 &&
					TS_State.touchY[0] >= 76 && TS_State.touchY[0] <= 196) {
				BSP_LCD_FillEllipse(TS_State.touchX[0], TS_State.touchY[0], 5, 5);
				//save coordinates to structure
				x_coord = (uint8_t)TS_State.touchX[0] - 71;
				y_coord = (uint8_t)TS_State.touchY[0] - 71;
				digit_im_weights[ind][x_coord][y_coord]++;
			}

			//if TRAIN is selected
			if (TS_State.touchX[0] >= 331 && TS_State.touchX[0] <= 421 &&
					TS_State.touchY[0] >= 20 && TS_State.touchY[0] <= 70) {
				//clear drawing area
				clear_area(72, 72, 129, 129);
			}

		}
			//IF IN "RECOGNIZE" MODE
		if (mode == 2) {
			//if push button is pressed
			if (BSP_PB_GetState(BUTTON_KEY) == 1) {
				HAL_Delay(100);
				menu_init();
				mode = 0;
			}
			//if touch is within drawing area, draw ellipse and save coordinates
			if (TS_State.touchX[0] >= 76 && TS_State.touchX[0] <= 196 &&
						TS_State.touchY[0] >= 76 && TS_State.touchY[0] <= 196) {
				BSP_LCD_FillEllipse(TS_State.touchX[0], TS_State.touchY[0], 5, 5);
				x_coord = (uint8_t)TS_State.touchX[0] - 71;
				y_coord = (uint8_t)TS_State.touchY[0] - 71;
				for (int s = 0; s < 10; s++) {
					if (digit_im_weights[s][x_coord][y_coord] > WEIGHT_THRESHOLD)
						match_cntr[s]++;
					}
				}

			//if RECOGNIZE is selected
			if (TS_State.touchX[0] >= 301 && TS_State.touchX[0] <= 461 &&
					TS_State.touchY[0] >= 20 && TS_State.touchY[0] <= 70) {
				//TEST: draw image based on stored coordinates and set weights
#ifdef DIGIT_TEST
				for (int i = 0; i < 130; i++) {
						for (int j = 0; j < 130; j++) {
									if (digit_im_weights[1][i][j] > 0) {
												BSP_LCD_FillEllipse(i + 71, j + 71, 5, 5);
									}
						}
				}
#endif
				uint8_t max_match = 0;
				int max_ind = 0;
				for (int i = 0; i < 10; i++) {
					if (match_cntr[i] > max_match) {
						max_match = match_cntr[i];
						max_ind = i;
					}
				}
				if (max_match > MATCH_THRESHOLD) {
					switch(max_ind) {
					case 0:
						BSP_LCD_DisplayStringAt(310, 120, digit_text[0], LEFT_MODE);
						break;
					case 1:
						BSP_LCD_DisplayStringAt(310, 120, digit_text[1], LEFT_MODE);
						break;
					case 2:
						BSP_LCD_DisplayStringAt(310, 120, digit_text[2], LEFT_MODE);
						break;
					case 3:
						BSP_LCD_DisplayStringAt(310, 120, digit_text[3], LEFT_MODE);
						break;
					case 4:
						BSP_LCD_DisplayStringAt(310, 120, digit_text[4], LEFT_MODE);
						break;
					case 5:
						BSP_LCD_DisplayStringAt(310, 120, digit_text[5], LEFT_MODE);
						break;
					case 6:
						BSP_LCD_DisplayStringAt(310, 120, digit_text[6], LEFT_MODE);
						break;
					case 7:
						BSP_LCD_DisplayStringAt(310, 120, digit_text[7], LEFT_MODE);
						break;
					case 8:
						BSP_LCD_DisplayStringAt(310, 120, digit_text[8], LEFT_MODE);
						break;
					case 9:
						BSP_LCD_DisplayStringAt(310, 120, digit_text[9], LEFT_MODE);
						break;
					}
				} else {
					BSP_LCD_SetFont(&Font12);
					uint8_t notrec_text[15] = "Not recognized";
					BSP_LCD_DisplayStringAt(326, 130, notrec_text, LEFT_MODE);
				}
			}

			//if CLEAR is selected
			if (TS_State.touchX[0] >= 301 && TS_State.touchX[0] <= 451 &&
								TS_State.touchY[0] >= 200 && TS_State.touchY[0] <= 250) {
				//clear drawing area
				clear_area(72, 72, 129, 129);
				//clear match counters
				for (uint8_t i = 0; i < 10; i++) {
					match_cntr[i] = 0;
				}
				//clear Result table
				clear_area(302, 111, 148, 48);
			}
	} //recognize mode
}	//while(1)

} //Main


/*****FUNCTIONS*******/
void clear_area(uint16_t x_pos, uint16_t y_pos, uint16_t width, uint16_t height)
{
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	BSP_LCD_FillRect(x_pos, y_pos, width, height);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
}





void training_init()
{
	BSP_LCD_Clear(LCD_COLOR_WHITE);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_SetFont(&Font20);
	BSP_LCD_DrawRect(71, 71, 130, 130);		//drawing area
	BSP_LCD_DrawRect(71, 29, 130, 36);		//currently learning display
	BSP_LCD_DrawLine(272, 0, 272, 272);		//area separator
	BSP_LCD_DrawRect(301, 20, 150, 50); 	//TRAIN button
	BSP_LCD_DrawRect(301, 80, 150, 180); 	//selection table
	uint8_t train_text[6] = "TRAIN";
	BSP_LCD_DisplayStringAt(338, 35, train_text, LEFT_MODE);
	uint8_t learning_text[9] = "LEARNING";
	BSP_LCD_DisplayStringAt(79, 7, learning_text, LEFT_MODE);
	BSP_LCD_DrawLine(301, 110, 451, 110);	//horizontal line top
	BSP_LCD_DrawLine(301, 160, 451, 160);	//horizontal line middle
	BSP_LCD_DrawLine(301, 210, 451, 210);	//horizontal line bottom
	BSP_LCD_DrawLine(351, 110, 351, 260);	//vertical line left
	BSP_LCD_DrawLine(401, 110, 401, 260);	//vertical line right

	BSP_LCD_DisplayStringAt(368, 86, digit_text[0], LEFT_MODE);
	BSP_LCD_DisplayStringAt(316, 125, digit_text[1], LEFT_MODE);
	BSP_LCD_DisplayStringAt(366, 125, digit_text[2], LEFT_MODE);
	BSP_LCD_DisplayStringAt(416, 125, digit_text[3], LEFT_MODE);
	BSP_LCD_DisplayStringAt(316, 175, digit_text[4], LEFT_MODE);
	BSP_LCD_DisplayStringAt(366, 175, digit_text[5], LEFT_MODE);
	BSP_LCD_DisplayStringAt(416, 175, digit_text[6], LEFT_MODE);
	BSP_LCD_DisplayStringAt(316, 225, digit_text[7], LEFT_MODE);
	BSP_LCD_DisplayStringAt(366, 225, digit_text[8], LEFT_MODE);
	BSP_LCD_DisplayStringAt(419, 225, digit_text[9], LEFT_MODE);
}



void recognize_init()
{
	BSP_LCD_Clear(LCD_COLOR_WHITE);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_SetFont(&Font20);
	BSP_LCD_DrawRect(71, 71, 130, 130);		//drawing area
	BSP_LCD_DrawRect(71, 29, 130, 36);		//Correct marker button
	BSP_LCD_DrawLine(272, 0, 272, 272);		//vertical separator line
	BSP_LCD_DrawRect(301, 20, 150, 50); 	//RECOGNIZE button
	BSP_LCD_SetFont(&Font20);
	uint8_t recognize_text[10] = "RECOGNIZE";
	uint8_t correct_text[9] = "CORRECT!";
	BSP_LCD_DisplayStringAt(315, 33, recognize_text, LEFT_MODE);
	BSP_LCD_DisplayStringAt(80, 41, correct_text, LEFT_MODE);
	BSP_LCD_DrawRect(301, 80, 150, 80); 	//result table
	BSP_LCD_DrawLine(301, 110, 451, 110);	//line below "Result:"
	uint8_t result_text[7] = "RESULT";
	BSP_LCD_DisplayStringAt(335, 86, result_text, LEFT_MODE);
	BSP_LCD_DrawRect(301, 200, 150, 50);	//clear button
	uint8_t clear_text[6] = "CLEAR";
	BSP_LCD_DisplayStringAt(340, 218, clear_text, LEFT_MODE);
}





void menu_init()
{
	BSP_LCD_Clear(LCD_COLOR_BLACK);
	BSP_LCD_SetFont(&Font24);
	//display TRAIN button
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	BSP_LCD_FillRect(154, 40, 172, 86);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	char train_text[6] = "TRAIN";
	BSP_LCD_DisplayStringAt(200, 70, train_text, LEFT_MODE);

	//display RECOGNIZE button
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	BSP_LCD_FillRect(154, 146, 172, 86);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	char recognize_text[11] = "RECOGNIZE";
	BSP_LCD_DisplayStringAt(164, 176, recognize_text, LEFT_MODE);
}


















/**
 * @brief This function provides accurate delay (in milliseconds) based
 *        on SysTick counter flag.
 * @note This function is declared as __weak to be overwritten in case of other
 *       implementations in user file.
 * @param Delay: specifies the delay time length, in milliseconds.
 * @retval None
 */

void HAL_Delay(__IO uint32_t Delay) {
	while (Delay) {
		if (SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) {
			Delay--;
		}
	}
}

/**
 * @brief  System Clock Configuration
 *         The system Clock is configured as follow :
 *            System Clock source            = PLL (HSE)
 *            SYSCLK(Hz)                     = 216000000
 *            HCLK(Hz)                       = 216000000
 *            AHB Prescaler                  = 1
 *            APB1 Prescaler                 = 4
 *            APB2 Prescaler                 = 2
 *            HSE Frequency(Hz)              = 25000000
 *            PLL_M                          = 25
 *            PLL_N                          = 432
 *            PLL_P                          = 2
 *            VDD(V)                         = 3.3
 *            Main regulator output voltage  = Scale1 mode
 *            Flash Latency(WS)              = 7
 * @param  None
 * @retval None
 */
void SystemClock_Config(void) {
	RCC_ClkInitTypeDef RCC_ClkInitStruct;
	RCC_OscInitTypeDef RCC_OscInitStruct;

	/* Enable HSE Oscillator and activate PLL with HSE as source */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	RCC_OscInitStruct.HSIState = RCC_HSI_OFF;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLM = 25;
	RCC_OscInitStruct.PLL.PLLN = 432;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
	RCC_OscInitStruct.PLL.PLLQ = 9;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		Error_Handler();
	}

	/* Activate the OverDrive to reach the 216 Mhz Frequency */
	if (HAL_PWREx_EnableOverDrive() != HAL_OK) {
		Error_Handler();
	}

	/* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
	 clocks dividers */
	RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK |
	RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7) != HAL_OK) {
		Error_Handler();
	}
}
//end

/**
 * @brief  This function is executed in case of error occurrence.
 * @param  None
 * @retval None
 */

static void Error_Handler(void) {
	/* User may add here some code to deal with this error */
	while (1) {
	}
}

/**
 * @brief  CPU L1-Cache enable.
 * @param  None
 * @retval None
 */

static void CPU_CACHE_Enable(void) {
	/* Enable I-Cache */
	SCB_EnableICache();

	/* Enable D-Cache */
	SCB_EnableDCache();
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
