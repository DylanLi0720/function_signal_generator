/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
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
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "delay.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
unsigned int sin_dat[360]=
{0x80,0x82,0x84,0x86,0x88,0x8b,0x8d,0x8f,0x91,0x94,0x96,0x98,
0x9a,0x9c,0x9e,0xa1,0xa3,0xa5,0xa7,0xa9,0xab,0xad,0xaf,0xb1,
0xb4,0xb6,0xb8,0xba,0xbc,0xbe,0xbf,0xc1,0xc3,0xc5,0xc7,0xc9,
0xcb,0xcc,0xce,0xd0,0xd2,0xd3,0xd5,0xd7,0xd8,0xda,0xdc,0xdd,
0xdf,0xe0,0xe2,0xe3,0xe4,0xe6,0xe7,0xe8,0xea,0xeb,0xec,0xed,
0xee,0xef,0xf0,0xf2,0xf3,0xf3,0xf4,0xf5,0xf6,0xf7,0xf8,0xf9,
0xf9,0xfa,0xfb,0xfb,0xfc,0xfc,0xfd,0xfd,0xfe,0xfe,0xfe,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0xfe,0xfe,0xfe,0xfd,0xfd,0xfc,0xfc,0xfb,0xfb,0xfa,
0xf9,0xf9,0xf8,0xf7,0xf6,0xf5,0xf4,0xf4,0xf3,0xf2,0xf1,0xf0,
0xee,0xed,0xec,0xeb,0xea,0xe8,0xe7,0xe6,0xe4,0xe3,0xe2,0xe0,
0xdf,0xdd,0xdc,0xda,0xd9,0xd7,0xd5,0xd4,0xd2,0xd0,0xce,0xcd,
0xcb,0xc9,0xc7,0xc5,0xc3,0xc2,0xc0,0xbe,0xbc,0xba,0xb8,0xb6,
0xb4,0xb2,0xb0,0xae,0xab,0xa9,0xa7,0xa5,0xa3,0xa1,0x9f,0x9c,
0x9a,0x98,0x96,0x94,0x92,0x8f,0x8d,0x8b,0x89,0x86,0x84,0x82,
0x80,0x7d,0x7b,0x79,0x77,0x75,0x72,0x70,0x6e,0x6c,0x69,0x67,
0x65,0x63,0x61,0x5f,0x5c,0x5a,0x58,0x56,0x54,0x52,0x50,0x4e,
0x4c,0x4a,0x48,0x46,0x44,0x42,0x40,0x3e,0x3c,0x3a,0x38,0x36,
0x34,0x33,0x31,0x2f,0x2d,0x2c,0x2a,0x28,0x27,0x25,0x24,0x22,
0x21,0x1f,0x1e,0x1c,0x1b,0x19,0x18,0x17,0x16,0x14,0x13,0x12,
0x11,0x10,0x0f,0x0e,0x0d,0x0c,0x0b,0x0a,0x09,0x08,0x07,0x07,
0x06,0x5,0x5,0x4,0x3,0x3,0x2,0x2,0x1,0x1,0x1,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1,0x1,0x1,0x2,
0x2,0x3,0x3,0x4,0x4,0x5,0x6,0x6,0x7,0x8,0x9,0xa,0xa,0xb,0xc,
0xd,0xe,0xf,0x10,0x12,0x13,0x14,0x15,0x16,0x18,0x19,0x1a,0x1c,
0x1d,0x1f,0x20,0x22,0x23,0x25,0x26,0x28,0x2a,0x2b,0x2d,0x2f,
0x30,0x32,0x34,0x36,0x38,0x39,0x3b,0x3d,0x3f,0x41,0x43,0x45,
0x47,0x49,0x4b,0x4d,0x4f,0x51,0x53,0x55,0x58,0x5a,0x5c,0x5e,
0x60,0x62,0x65,0x67,0x69,0x6b,0x6d,0x70,0x72,0x74,0x76,0x78,
0x7b,0x7d};// 正弦信号产生数组	   超过128字节需要将数据放到rom当中

void writeGPIO(uint32_t data)
{
    HAL_GPIO_WritePin(A0_GPIO_Port, A0_Pin, (data & 0x01) == 0x01 ? GPIO_PIN_SET: GPIO_PIN_RESET);
    HAL_GPIO_WritePin(A1_GPIO_Port, A1_Pin, (data & 0x02) == 0x02 ? GPIO_PIN_SET: GPIO_PIN_RESET);
    HAL_GPIO_WritePin(A2_GPIO_Port, A2_Pin, (data & 0x04) == 0x04 ? GPIO_PIN_SET: GPIO_PIN_RESET);
    HAL_GPIO_WritePin(A3_GPIO_Port, A3_Pin, (data & 0x08) == 0x08 ? GPIO_PIN_SET: GPIO_PIN_RESET);
    HAL_GPIO_WritePin(A4_GPIO_Port, A4_Pin, (data & 0x10) == 0x10 ? GPIO_PIN_SET: GPIO_PIN_RESET);
    HAL_GPIO_WritePin(A5_GPIO_Port, A5_Pin, (data & 0x20) == 0x20 ? GPIO_PIN_SET: GPIO_PIN_RESET);
    HAL_GPIO_WritePin(A6_GPIO_Port, A6_Pin, (data & 0x40) == 0x40 ? GPIO_PIN_SET: GPIO_PIN_RESET);
    HAL_GPIO_WritePin(A7_GPIO_Port, A7_Pin, (data & 0x80) == 0x80 ? GPIO_PIN_SET: GPIO_PIN_RESET);
}
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

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
int main(void)
{
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
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
      
      for(uint16_t i=0; i < 360; i++)//以下为0832驱动程序		
		{
			writeGPIO(sin_dat[i]);
           // delay_us(30);
	   	}
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
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
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
