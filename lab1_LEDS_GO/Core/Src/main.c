/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "uart_io.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint8_t inputMode = 0;
uint8_t fUART_received = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void) {
	/* USER CODE BEGIN 1 */
	/* USER CODE END 1 */

	/* MCU Configuration--------------------------------------------------------*/

	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

	/* USER CODE BEGIN Init */

	/* USER CODE END Init */

	/* Configure the system clock */
	SystemClock_Config();

	/* USER CODE BEGIN SysInit */

	/* USER CODE END SysInit */

	/* Initialize all configured peripherals */
	MX_GPIO_Init();
	MX_UART4_Init();
	MX_USART1_UART_Init();
	/* USER CODE BEGIN 2 */
	uint8_t pass[9] = "QWERTY";
	int8_t level = 0;
	int8_t max_level = sizeof("QWERTY") - 1;
	uint8_t character;
	uint8_t new_pass[9];
	uint8_t passwordMode = 0;
	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while (1) {
		if (passwordMode == 0) {
			HAL_UART_Transmit(&huart1, "\r\nPress some keys: ",
					sizeof("\r\nPress some keys: ") - 1, 10);
			passwordMode = 1;
		}
		character = read_char_mode();
		if (character == 0x1) {
			if (inputMode) {
				HAL_UART_Transmit(&huart1, "\r\nEntering Interrupt mode",
						sizeof("\r\nEntering Interrupt mode") - 1, 10);
			} else {
				HAL_UART_Transmit(&huart1, "\r\nEntering NonInterrupt mode",
						sizeof("\r\nEntering NonInterrupt mode") - 1, 10);
			}
			if (passwordMode == 1) {
				HAL_UART_Transmit(&huart1, "\r\nPress some keys: ",
						sizeof("\r\nPress some keys: ") - 1, 10);
			}
			else {
				HAL_UART_Transmit(&huart1, "\r\nEnter new password: ",
						sizeof("\r\nEnter new password: ") - 1, 10);
			}
			for (int j = 0; j < level; j++) {
				HAL_UART_Transmit(&huart1, "*", 1, 10);
			}
		}
		if (character == '+' && passwordMode == 1) {
			HAL_UART_Transmit(&huart1, "+", 1, 10);
			HAL_UART_Transmit(&huart1, "\r\nEnter new password: ",
					sizeof("\r\nEnter new password: ") - 1, 10);
			passwordMode = 2;
			level = 0;
			continue;
		} else if (character == '\b' || character == '\x7F') {
			if (level > 0) {
				HAL_UART_Transmit(&huart1, "\b \b", 3, 10);
				level--;
			}
		} else {
			if (character >= 'a' && character <= 'z') {
				character -= 'a' - 'A';
			}
			if ((character >= '0' && character <= '9')
					|| (character >= 'A' && character <= 'Z')
					|| character == '\r') {
				if (character != '\r') {
					HAL_UART_Transmit(&huart1, "*", 1, 10);
				}
				// Entering security password
				if (passwordMode == 1) {
					if (character == '\r') {
						continue;
					}
					level = security(pass, level, max_level, character);
					if (level <= 0) {
						HAL_UART_Transmit(&huart1, "\r\n", 2, 10);
						passwordMode = 0;
					}
					if (level == 0) {
						HAL_UART_Transmit(&huart1, "SUCC\r\n", 6, 10);
					} else if (level < 0) {
						if (level == -2) {
							HAL_UART_Transmit(&huart1, "SUPRA ", 6, 10);
						}
						HAL_UART_Transmit(&huart1, "FAIL\r\n", 6, 10);
					}
				}
				// Entering new password
				else {
					if (character != '\r' && level < 8) {
						new_pass[level++] = character;
					}
					if (character == '\r' || level == 8) {
						if (level != 0) {
							HAL_UART_Transmit(&huart1, "\r\n", 2, 10);
							new_pass[level] = 0;
							HAL_UART_Transmit(&huart1,
									"Confirm password change by pressing 'y'\r\n",
									sizeof("Confirm password change by pressing 'y'\r\n")
											- 1, 10);
							if (read_char_mode() == 'y') {
								HAL_UART_Transmit(&huart1,
										"Password changed qwerty123\r\n",
										sizeof("Password changed qwerty123\r\n")
												- 1, 10);
								for (int j = 0; j < sizeof(pass); j++) {
									pass[j] = new_pass[j];
								}
								max_level = level;
							} else {
								HAL_UART_Transmit(&huart1,
										"Password change aborted\r\n",
										sizeof("Password change aborted\r\n")
												- 1, 10);
							}
							level = 0;
						} else {
							HAL_UART_Transmit(&huart1,
									"Password change aborted\r\n",
									sizeof("Password change aborted\r\n") - 1,
									10);
						}
						passwordMode = 0;
					}
				}
			}
		}
	}
	/* USER CODE END WHILE */

	/* USER CODE BEGIN 3 */
	/* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void) {
	RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };

	/** Configure the main internal regulator output voltage
	 */
	__HAL_RCC_PWR_CLK_ENABLE()
	;
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
	/** Initializes the CPU, AHB and APB busses clocks
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		Error_Handler();
	}
	/** Initializes the CPU, AHB and APB busses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
			| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK) {
		Error_Handler();
	}
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void) {
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */

	/* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t *file, uint32_t line)
{
	/* USER CODE BEGIN 6 */
	/* User can add his own implementation to report the file name and line number,
	 tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
	/* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
