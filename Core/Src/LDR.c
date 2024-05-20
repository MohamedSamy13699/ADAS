/*
  * @file:       LDR.c
 * @brief:       Source file of the LDR driver.
 * @Created on:  Apr 26, 2024
 *     @Author: samy
 */

#include "main.h"
#include "adc.h"
#include "gpio.h"
#include "LDR.h"


uint8_t flag = 0;

/**
  * @brief  Get the Value measured by LDR sensor.
  * @param  None
  * @retval The LDR value
  */
uint8_t LDR_u8GetValue(void)
{

	uint32_t lux = 0;
	uint8_t LDR_value = 0;
	HAL_ADC_Start(&hadc1);
	HAL_ADC_PollForConversion(&hadc1, 20);
	lux = HAL_ADC_GetValue(&hadc1);
	LDR_value = (lux/4096.0)*100.0;
	return LDR_value;
}


