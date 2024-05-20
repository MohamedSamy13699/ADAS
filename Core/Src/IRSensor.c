/*
 * IRSensor.c
 *
 *  Created on: Apr 26, 2024
 *      Author: samy
 */
/*
  * @file:      IRSensor.c
 * @brief:       Source file of the IRSensor driver.
 * @Created on:  Apr 25, 2024
 *      Author: samy
 */

/* USER CODE BEGIN Includes */
#include "main.h"
#include "gpio.h"
#include "IRSensor.h"
/* USER CODE END Includes */


/**
 * @brief  read the return value of ir sensor to detect if there is an obstacle behind it   .
 * @param  Select which IR you need to get it's state
 * @retval return the value of IR sensor
 */

uint8_t IRSensor_Read(uint8_t IRSensor)
{
	uint8_t Local_IRSensorReturnValue = 1;
	switch(IRSensor)
	{
	case LEFT_IR:
		Local_IRSensorReturnValue = HAL_GPIO_ReadPin(IR_LEFT_GPIO_Port, IR_LEFT_Pin);
		break;
	case RIGHT_IR:
		Local_IRSensorReturnValue = HAL_GPIO_ReadPin(IR_RIGHT_GPIO_Port, IR_RIGHT_Pin);
		break;
	default:
		break;
	}
	return Local_IRSensorReturnValue;
}
