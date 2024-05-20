/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * File Name          : freertos.c
 * Description        : Code for freertos applications
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

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "motor.h"
#include "IRSensor.h"
#include "bluetooth.h"
#include "LDR.h"
#include "usart.h"
#include "Ultrasonic.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
typedef enum{
	T_OFF,
	T_ON
}TURN_SIGNAL_MODES;
typedef enum{

	LKS_OFF,
	LKS_ON,
	LKS_STANDARD,
	LKS_ADAPTIVE
}LKS_MODES;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define WHITE   1
#define BLACK   0
#define MIN_DISTANCE		5
#define DEFAULT_DISTANCE    20
#define MAX_SPEED  			80
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
uint8_t  ACC_Flag 		  = 0;
uint8_t  LKS_Flag 		  = 0;
uint8_t  Left_IR 		  = 0;
uint8_t  Right_IR 		  = 0;
TURN_SIGNAL_MODES	 Turn_Flag		  = T_OFF;
LKS_MODES  LKS_mode  = LKS_STANDARD;
uint8_t	 speed 			  = 0;
uint8_t rxData			  = 0;
uint16_t Current_Distance = 0;
uint8_t AB_Flag	=0;
uint8_t Return_flag =0;
uint8_t debug			=0;
uint8_t tx_buffer[20] = "Welcome to USB";

uint8_t pData =0;
extern Ultrasonic_t HCSR04_sensor[1];
/* USER CODE END Variables */
/* Definitions for LKS_ */
osThreadId_t LKS_Handle;
const osThreadAttr_t LKS__attributes = {
		.name = "LKS_",
		.stack_size = 128 * 4,
		.priority = (osPriority_t) osPriorityAboveNormal,
};
/* Definitions for ACC_ */
osThreadId_t ACC_Handle;
const osThreadAttr_t ACC__attributes = {
		.name = "ACC_",
		.stack_size = 128 * 4,
		.priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for AB_ */
osThreadId_t AB_Handle;
const osThreadAttr_t AB__attributes = {
		.name = "AB_",
		.stack_size = 128 * 4,
		.priority = (osPriority_t) osPriorityHigh,
};
/* Definitions for BLUETOOTH_ */
osThreadId_t BLUETOOTH_Handle;
const osThreadAttr_t BLUETOOTH__attributes = {
		.name = "BLUETOOTH_",
		.stack_size = 128 * 4,
		.priority = (osPriority_t) osPriorityLow,
};
/* Definitions for ALC_ */
osThreadId_t ALC_Handle;
const osThreadAttr_t ALC__attributes = {
		.name = "ALC_",
		.stack_size = 128 * 4,
		.priority = (osPriority_t) osPriorityLow1,
};
/* Definitions for LKS_semaphore */
osSemaphoreId_t LKS_semaphoreHandle;
const osSemaphoreAttr_t LKS_semaphore_attributes = {
		.name = "LKS_semaphore"
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void LKS_TASK(void *argument);
void ACC_TASK(void *argument);
void AB_TASK(void *argument);
void BLUETOOTH_TASK(void *argument);
void ALC_TASK(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
 * @brief  FreeRTOS initialization
 * @param  None
 * @retval None
 */
void MX_FREERTOS_Init(void) {
	/* USER CODE BEGIN Init */

	/* USER CODE END Init */

	/* USER CODE BEGIN RTOS_MUTEX */
	/* add mutexes, ... */
	/* USER CODE END RTOS_MUTEX */

	/* Create the semaphores(s) */
	/* creation of LKS_semaphore */
	LKS_semaphoreHandle = osSemaphoreNew(1, 0, &LKS_semaphore_attributes);

	/* USER CODE BEGIN RTOS_SEMAPHORES */
	/* add semaphores, ... */
	/* USER CODE END RTOS_SEMAPHORES */

	/* USER CODE BEGIN RTOS_TIMERS */
	/* start timers, add new ones, ... */
	/* USER CODE END RTOS_TIMERS */

	/* USER CODE BEGIN RTOS_QUEUES */
	/* add queues, ... */
	/* USER CODE END RTOS_QUEUES */

	/* Create the thread(s) */
	/* creation of LKS_ */
	LKS_Handle = osThreadNew(LKS_TASK, NULL, &LKS__attributes);

	/* creation of ACC_ */
	ACC_Handle = osThreadNew(ACC_TASK, NULL, &ACC__attributes);

	/* creation of AB_ */
	AB_Handle = osThreadNew(AB_TASK, NULL, &AB__attributes);

	/* creation of BLUETOOTH_ */
	BLUETOOTH_Handle = osThreadNew(BLUETOOTH_TASK, NULL, &BLUETOOTH__attributes);

	/* creation of ALC_ */
	ALC_Handle = osThreadNew(ALC_TASK, NULL, &ALC__attributes);

	/* USER CODE BEGIN RTOS_THREADS */
	/* add threads, ... */
	/* USER CODE END RTOS_THREADS */

	/* USER CODE BEGIN RTOS_EVENTS */
	/* add events, ... */
	/* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_LKS_TASK */
/**
 * @brief  Function implementing the LKS_ thread.
 * @param  argument: Not used
 * @retval None
 */
/* USER CODE END Header_LKS_TASK */
void LKS_TASK(void *argument)
{
	/* USER CODE BEGIN LKS_TASK */
	/* Infinite loop */
	for(;;)

	{

		HAL_GPIO_TogglePin(LED_LEFT_GPIO_Port, LED_LEFT_Pin);
		/* if the driver do not turn on the turn signsl */
		if(Turn_Flag == T_OFF && speed > 20 &&  LKS_mode ==  LKS_ADAPTIVE  && (!AB_Flag))
		{
			HAL_GPIO_WritePin(LKS_ALARM_GPIO_Port, LKS_ALARM_Pin, GPIO_PIN_RESET);
			Left_IR = IRSensor_Read(LEFT_IR);
			Right_IR = IRSensor_Read(RIGHT_IR);
			/* If the car is inside the lane / No lane markings are detected on both sides */
			if ((Left_IR == BLACK) && (Right_IR == BLACK) )
			{

				if(Return_flag==1)
				{
					Motor_voidMoveForward(speed);
				}else
				{
					Motor_voidMoveBackward(speed);
				}
				/* Reset (Lane Keeping Status) Flag */
				LKS_Flag = 0;

			}
			/* If the car drifts to the right / Lane markings are detected on the right side */
			else if (Left_IR == BLACK && Right_IR == WHITE)
			{
				/* Set (Lane Keeping Status) Flag */
				LKS_Flag = 1;
				// Steer the car to the left
				Motor_voidMoveLeft(speed);

			}
			/* If the car drifts to the left / Lane markings are detected on the left side */
			else if (Left_IR == WHITE && Right_IR == BLACK)
			{
				/* Set (Lane Keeping Status) Flag */
				LKS_Flag = 1;

				// Steer the car to the right
				Motor_voidMoveRight(speed);
			}
			else
			{/* Nothing */}
		}else if(Turn_Flag == T_OFF && speed > 20 &&  LKS_mode == LKS_STANDARD && (!AB_Flag))
		{

			Left_IR = IRSensor_Read(LEFT_IR);
			Right_IR = IRSensor_Read(RIGHT_IR);
			/* If the car is inside the lane / No lane markings are detected on both sides */
			if ((Left_IR == BLACK) && (Right_IR == BLACK) )
			{
				HAL_GPIO_WritePin(LKS_ALARM_GPIO_Port, LKS_ALARM_Pin, GPIO_PIN_RESET);

				LKS_Flag = 0;

			}
			/* If the car drifts to the right / Lane markings are detected on the right side */
			else if (Left_IR == BLACK && Right_IR == WHITE)
			{
				/* Set (Lane Keeping Status) Flag */
				LKS_Flag = 1;

				// Indication led
				HAL_GPIO_WritePin(LKS_ALARM_GPIO_Port, LKS_ALARM_Pin, GPIO_PIN_SET);
			}
			/* If the car drifts to the left / Lane markings are detected on the left side */
			else if (Left_IR == WHITE && Right_IR == BLACK)
			{
				/* Set (Lane Keeping Status) Flag */
				LKS_Flag = 1;

				// Indication led
				HAL_GPIO_WritePin(LKS_ALARM_GPIO_Port, LKS_ALARM_Pin, GPIO_PIN_SET);
			}
			else
			{/* Nothing */}
		}

		osDelay(100);
	}
	/* USER CODE END LKS_TASK */
}

/* USER CODE BEGIN Header_ACC_TASK */
/**
 * @brief Function implementing the ACC_ thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_ACC_TASK */
void ACC_TASK(void *argument)
{
	/* USER CODE BEGIN ACC_TASK */

	uint8_t distance =0;
	/* Infinite loop */
	for(;;)
	{


		distance = Get_Distance();
		if((!LKS_Flag) && (ACC_Flag) && speed > 20 && (!AB_Flag))
		{
			if(rxData==speed_0 || rxData==speed_1 ||rxData==speed_2 ||rxData==speed_3 ||rxData==speed_4 ||rxData==speed_5 ||rxData==speed_6 ||rxData==speed_7 ||rxData==speed_8 ||rxData==speed_9 ||rxData==speed_10 )
			{
				ACC_Flag=0;
			}
			else
			{
				if ((distance < DEFAULT_DISTANCE) && (distance > MIN_DISTANCE))
				{
					/* Calculate Adaptive Speed */
					HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin,GPIO_PIN_SET);
					speed = MAX_SPEED - 2*(DEFAULT_DISTANCE - distance) ;
					Motor_voidMoveForward(speed);
				}
				else if (distance <= MIN_DISTANCE)
				{
					/* very low distance < 20 --> car stop */
					Motor_voidStop();
					speed = 0;
				}
				else if (distance >= DEFAULT_DISTANCE)
				{
					HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin,GPIO_PIN_RESET);
					speed = MAX_SPEED;
					Motor_voidMoveForward(speed);
				}
				else{/* nothing */}
			}



		}
		else{/* Nothing */}
		osDelay(100);
	}
	/* USER CODE END ACC_TASK */
}

/* USER CODE BEGIN Header_AB_TASK */
/**
 * @brief Function implementing the AB_ thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_AB_TASK */
void AB_TASK(void *argument)
{
	/* USER CODE BEGIN AB_TASK */

	uint8_t distance =0;
	/* Infinite loop */

	for(;;)
	{
		distance = Get_Distance();
		HAL_GPIO_TogglePin(LED_RIGHT_GPIO_Port, LED_RIGHT_Pin);
		if (distance > 10 )
		{
			AB_Flag =0;
			HAL_GPIO_WritePin(AB_ALARM_GPIO_Port,AB_ALARM_Pin,GPIO_PIN_RESET);
		}
		else
		{
			AB_Flag =1;
			HAL_GPIO_WritePin(AB_ALARM_GPIO_Port,AB_ALARM_Pin,GPIO_PIN_SET);
			Motor_voidStop();
		}


	}
	/* USER CODE END AB_TASK */
}

/* USER CODE BEGIN Header_BLUETOOTH_TASK */
/**
 * @brief Function implementing the BLUETOOTH_ thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_BLUETOOTH_TASK */
void BLUETOOTH_TASK(void *argument)
{
	/* USER CODE BEGIN BLUETOOTH_TASK */
	/* Infinite loop */
	for(;;)
	{



		HAL_UART_Receive(&huart1,&rxData,1,50);
		if(!AB_Flag)
		{


			/* USER CODE END WHILE */
			switch (rxData) {

			case MOVE_FORWARD:
				Motor_voidMoveForward(speed); // motor forward  (e.g., motor control)
				Return_flag=1;
				break;
			case MOVE_LEFT:
				Motor_voidMoveLeft(speed); // motor move left (e.g., motor control)
				break;
			case MOVE_BACKWARD:
				Motor_voidMoveBackward(speed); // motor backward
				Return_flag=0;
				break;
			case MOVE_RIGHT:
				Motor_voidMoveRight(speed); // motor move right
				break;
			case LANE_KEEP_ASSIST_STANDARD:
				LKS_mode = LKS_STANDARD;

				break;
			case LANE_KEEP_ASSIST_ADAPTIVE:
				LKS_mode = LKS_ADAPTIVE;

				break;
			case CRUISE_CONTROL_ON:
				ACC_Flag = 1;

				break;
			case CRUISE_CONTROL_OFF:
				ACC_Flag =0;

				break;
			case SIGNAL_ON:
				Turn_Flag = T_ON;
				break;
			case SIGNAL_OFF:
				Turn_Flag = T_OFF;
				break;

			case speed_0:  //
				speed = 0;
				Motor_voidControlSpeed(0);
				break;
			case speed_1:
				speed = 10;
				Motor_voidControlSpeed(10);
				break;
			case speed_2:  // Assuming 120 is the code for standard mode
				speed = 20;
				Motor_voidControlSpeed(20);
				break;
			case speed_3:
				speed = 30;
				Motor_voidControlSpeed(30);
				break;
			case speed_4:
				speed = 40;
				Motor_voidControlSpeed(40);
				break;
			case speed_5:
				speed = 50;
				Motor_voidControlSpeed(50);
				break;
			case speed_6:
				speed = 60;
				Motor_voidControlSpeed(60);
				break;
			case speed_7:
				speed = 70;
				Motor_voidControlSpeed(70);
				break;
			case speed_8:
				speed = 80;
				Motor_voidControlSpeed(80);
				break;
			case speed_9:
				speed = 90;
				Motor_voidControlSpeed(90);
				break;
			case speed_10:
				speed = 100;
				Motor_voidControlSpeed(100);
				break;
			default:
				// Handle unexpected data (optional)
				// You might want to print an error message or take some action here.
				break;

			}

		}
		osDelay(1);
	}
	/* USER CODE END BLUETOOTH_TASK */
}

/* USER CODE BEGIN Header_ALC_TASK */
/**
 * @brief Function implementing the ALC_ thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_ALC_TASK */
void ALC_TASK(void *argument)
{
	/* USER CODE BEGIN ALC_TASK */
	uint8_t LDR_Value = 0;
	/* Infinite loop */
	for(;;)
	{
		LDR_Value = LDR_u8GetValue();
		if(LDR_Value >= 93)
		{
			/* front Lead with Max lighting */
			TIM3->CCR3 = 98 ;
		}
		else if(LDR_Value < 93 || LDR_Value >= 80)
		{
			/* front Led with adaptive lighting*/
			TIM3->CCR3 =  LDR_Value;
		}
		else if(LDR_Value < 80 || LDR_Value > 10)
		{
			/* front Led with Low lighting */
			TIM3->CCR3 =  (LDR_Value ) / 2 ;
		}
		else
		{
			/* front Led Off*/
			TIM3->CCR3 =  0 ;
		}
		osDelay(500);
	}
	/* USER CODE END ALC_TASK */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

