/*
 * @file:        motor.h
 * @brief:       Header file of the motor driver.
 * @Created on:  Apr 24, 2024
 * @author:
 */

#ifndef INC_MOTOR_H_
#define INC_MOTOR_H_


/**
  * @brief  Initializes motor's pins.
  * @param  None
  * @retval None
  */
void Motor_voidInit(void);
/**
  * @brief  Give Duty cycle to the motor to can move it by the speed which you need  .
  * @param  DutyCycle value of Duty cycle (0-->100) for PWM signal
  * @retval None
  */
void Motor_voidControlSpeed(uint16_t DutyCycle);
/**
  * @brief  Move motor forward.
  * @param  None
  * @retval None
  */
void Motor_voidMoveForward(uint16_t DutyCycle);
/**
  * @brief Move motor backward.
  * @param  None
  * @retval None
  */
void Motor_voidMoveBackward(uint16_t DutyCycle);
/**
  * @brief Move motor Right.
  * @param  None
  * @retval None
  */
void Motor_voidMoveRight(uint16_t DutyCycle);
/**
  * @brief Move motor Left.
  * @param  None
  * @retval None
  */
void Motor_voidMoveLeft(uint16_t DutyCycle);
/**
  * @brief Stop motor.
  * @param  None
  * @retval None
  */
void Motor_voidStop(void);

#endif /* INC_MOTOR_H_ */
