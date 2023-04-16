/*
 * API_max30205.h
 *
 *  Created on: Apr 13, 2023
 *      Author: alan
 */

#ifndef API_INC_API_MAX30205_H_
#define API_INC_API_MAX30205_H_

#include "main.h"

float readMax30205Temperature(I2C_HandleTypeDef *hi2c);


#endif /* API_INC_API_MAX30205_H_ */
