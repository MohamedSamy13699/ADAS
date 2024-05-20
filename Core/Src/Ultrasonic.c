/**********************************************
 * @SWC: Ultrasonic.c
 * @date: May 2, 2024
 * @author:Hossam Emad 
************************************************/
#include "cmsis_os2.h"
#include "Ultrasonic.h"
#include "main.h"
/*edit timer*/
extern TIM_HandleTypeDef htim4;
/*edit timer*/
void delay (uint16_t time)
{
	/*edit timer*/
	__HAL_TIM_SET_COUNTER(&htim4, 0);
	while (__HAL_TIM_GET_COUNTER (&htim4) < time);
}

static Ultrasonic_t HCSR04_sensor;

//The callback function
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	/*		edit tim 									edit channel	*/
	if (   (htim == &htim4)  && htim->Channel == HAL_TIM_ACTIVE_CHANNEL_3)  // if the interrupt source is channel1
	{
		if (HCSR04_sensor.Is_First_Captured==0) // if the first value is not captured
		{
			/*														edit channel	*/
			HCSR04_sensor.IC_Val1 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_3); // read the first value
			HCSR04_sensor.Is_First_Captured = 1;  // set the first captured as true
			// Now change the polarity to falling edge
			/*									edit channel	*/
			__HAL_TIM_SET_CAPTUREPOLARITY(htim, TIM_CHANNEL_3, TIM_INPUTCHANNELPOLARITY_FALLING);
		}

		else if (HCSR04_sensor.Is_First_Captured==1)   // if the first is already captured
		{
			/*														edit channel	*/
			HCSR04_sensor.IC_Val2 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_3);  // read second value
			__HAL_TIM_SET_COUNTER(htim, 0);  // reset the counter

			if (HCSR04_sensor.IC_Val2 > HCSR04_sensor.IC_Val1)
			{
				HCSR04_sensor.Difference = HCSR04_sensor.IC_Val2-HCSR04_sensor.IC_Val1;
			}

			else if (HCSR04_sensor.IC_Val1 > HCSR04_sensor.IC_Val2)
			{
				HCSR04_sensor.Difference = (0xffff - HCSR04_sensor.IC_Val1) + HCSR04_sensor.IC_Val2;
			}

			HCSR04_sensor.Distance = HCSR04_sensor.Difference * .034/2;
			HCSR04_sensor.Is_First_Captured = 0; // set it back to false

			// set polarity to rising edge
			/*									edit channel	*/
			__HAL_TIM_SET_CAPTUREPOLARITY(htim, TIM_CHANNEL_3, TIM_INPUTCHANNELPOLARITY_RISING);
			/*		    	edit  timer    channel	*/
			__HAL_TIM_DISABLE_IT(&htim4, TIM_IT_CC3);
		}
	}
}

/*This function to start the timer*/
void HCSR04_Init(void)
{
	/*				edit  timer		channel  */
	HAL_TIM_IC_Start_IT(&htim4, TIM_CHANNEL_3);
}

void HCSR04_Read1 (void)
{

	HAL_GPIO_WritePin(TRIG_GPIO_Port, TRIG_Pin, GPIO_PIN_SET);  // pull the TRIG pin HIGH
	delay(10);  // wait for 10 us
	HAL_GPIO_WritePin(TRIG_GPIO_Port, TRIG_Pin, GPIO_PIN_RESET);  // pull the TRIG pin low
	/*edit 				timer    channel */
	__HAL_TIM_ENABLE_IT(&htim4, TIM_IT_CC3);
}

uint8_t Get_Distance(void)
{
	HCSR04_Read1();
	osDelay(100);
	return (HCSR04_sensor.Distance);
}
