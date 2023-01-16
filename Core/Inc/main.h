/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32g0xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LED_GREEN_Pin GPIO_PIN_11
#define LED_GREEN_GPIO_Port GPIOC
#define LED_RED_Pin GPIO_PIN_12
#define LED_RED_GPIO_Port GPIOC
#define CB1_OUT_Pin GPIO_PIN_1
#define CB1_OUT_GPIO_Port GPIOC
#define CB1_OUT_EXTI_IRQn EXTI0_1_IRQn
#define CB2_OUT_Pin GPIO_PIN_2
#define CB2_OUT_GPIO_Port GPIOC
#define CB2_OUT_EXTI_IRQn EXTI2_3_IRQn
#define OE_Pin GPIO_PIN_3
#define OE_GPIO_Port GPIOC
#define S0_Pin GPIO_PIN_0
#define S0_GPIO_Port GPIOA
#define S1_Pin GPIO_PIN_1
#define S1_GPIO_Port GPIOA
#define S2_Pin GPIO_PIN_2
#define S2_GPIO_Port GPIOA
#define S3_Pin GPIO_PIN_3
#define S3_GPIO_Port GPIOA
#define LED_CC_Pin GPIO_PIN_6
#define LED_CC_GPIO_Port GPIOA
#define TIM_CC_Pin GPIO_PIN_7
#define TIM_CC_GPIO_Port GPIOA
#define UART_STLink_TX_Pin GPIO_PIN_4
#define UART_STLink_TX_GPIO_Port GPIOC
#define UART_STLink_RX_Pin GPIO_PIN_5
#define UART_STLink_RX_GPIO_Port GPIOC
#define ADC_Pin GPIO_PIN_0
#define ADC_GPIO_Port GPIOB
#define XSHUT_C1_Pin GPIO_PIN_1
#define XSHUT_C1_GPIO_Port GPIOB
#define GPIO1_C1_Pin GPIO_PIN_2
#define GPIO1_C1_GPIO_Port GPIOB
#define SCL_2_Pin GPIO_PIN_10
#define SCL_2_GPIO_Port GPIOB
#define SDA_2_Pin GPIO_PIN_11
#define SDA_2_GPIO_Port GPIOB
#define XSHUT_C2_Pin GPIO_PIN_12
#define XSHUT_C2_GPIO_Port GPIOB
#define GPIO1_C2_Pin GPIO_PIN_13
#define GPIO1_C2_GPIO_Port GPIOB
#define SCL_1_Pin GPIO_PIN_9
#define SCL_1_GPIO_Port GPIOA
#define SDA_1_Pin GPIO_PIN_10
#define SDA_1_GPIO_Port GPIOA
#define TIM_Encoder1_CH1_Pin GPIO_PIN_8
#define TIM_Encoder1_CH1_GPIO_Port GPIOC
#define UART_XL320_Pin GPIO_PIN_5
#define UART_XL320_GPIO_Port GPIOD
#define TIM_Encoder1_CH2_Pin GPIO_PIN_3
#define TIM_Encoder1_CH2_GPIO_Port GPIOB
#define TIM_Encoder2_CH1_Pin GPIO_PIN_4
#define TIM_Encoder2_CH1_GPIO_Port GPIOB
#define TIM_Encoder2_CH2_Pin GPIO_PIN_5
#define TIM_Encoder2_CH2_GPIO_Port GPIOB
#define TIM_Driver2_CH1N_Pin GPIO_PIN_6
#define TIM_Driver2_CH1N_GPIO_Port GPIOB
#define TIM_Driver1_CH1N_Pin GPIO_PIN_7
#define TIM_Driver1_CH1N_GPIO_Port GPIOB
#define TIM_Driver2_CH1_Pin GPIO_PIN_8
#define TIM_Driver2_CH1_GPIO_Port GPIOB
#define TIM_Driver1_CH1_Pin GPIO_PIN_9
#define TIM_Driver1_CH1_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
