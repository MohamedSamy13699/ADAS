
/*
 * @file:        IRSensor.h
 * @brief:       Header file of the IR Sensor driver.
 * @Created on:  Apr 25, 2024
 * @author:
 */

#ifndef INC_IRSENSOR_H_
#define INC_IRSENSOR_H_


/**
  * @brief  read the return value of ir sensor to detect if there is an obstacle behind it   .
  * @param  Select which IR you need to get it's state
  * @retval return the value of IR sensor
  */

uint8_t IRSensor_Read(uint8_t IRSensor);
#endif /* INC_IRSENSOR_H_ */
