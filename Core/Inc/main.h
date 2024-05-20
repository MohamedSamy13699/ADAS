/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "stm32f3xx_hal.h"

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
#define B1_Pin GPIO_PIN_13
#define B1_GPIO_Port GPIOC
#define PWM_2_Pin GPIO_PIN_4
#define PWM_2_GPIO_Port GPIOA
#define LD2_Pin GPIO_PIN_5
#define LD2_GPIO_Port GPIOA
#define PWM_1_Pin GPIO_PIN_6
#define PWM_1_GPIO_Port GPIOA
#define TRIG_Pin GPIO_PIN_10
#define TRIG_GPIO_Port GPIOB
#define IR_LEFT_Pin GPIO_PIN_11
#define IR_LEFT_GPIO_Port GPIOB
#define IR_RIGHT_Pin GPIO_PIN_12
#define IR_RIGHT_GPIO_Port GPIOB
#define LED_LEFT_Pin GPIO_PIN_13
#define LED_LEFT_GPIO_Port GPIOB
#define LED_RIGHT_Pin GPIO_PIN_14
#define LED_RIGHT_GPIO_Port GPIOB
#define AB_ALARM_Pin GPIO_PIN_15
#define AB_ALARM_GPIO_Port GPIOB
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define MOTOR1_D1_Pin GPIO_PIN_3
#define MOTOR1_D1_GPIO_Port GPIOB
#define MOTOR1_D2_Pin GPIO_PIN_4
#define MOTOR1_D2_GPIO_Port GPIOB
#define LKS_ALARM_Pin GPIO_PIN_5
#define LKS_ALARM_GPIO_Port GPIOB
#define MOTOR2_D1_Pin GPIO_PIN_6
#define MOTOR2_D1_GPIO_Port GPIOB
#define MOTOR2_D2_Pin GPIO_PIN_7
#define MOTOR2_D2_GPIO_Port GPIOB
#define ECHO_Pin GPIO_PIN_8
#define ECHO_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */
#define LEFT_IR 0
#define RIGHT_IR	1
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
