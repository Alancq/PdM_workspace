/*
 * API_max30205.h
 *
 *  Created on: Apr 13, 2023
 *      Author: alan
 */

#ifndef API_INC_API_MAX30205_H_
#define API_INC_API_MAX30205_H_


#include <stdint.h>
#include "API_i2c.h"

#define MAX30205_ADDRESS      0x48
#define MAX30205_TEMP_REG     0x00

uint8_t max30205_init(I2C_HandleTypeDef *hi2c);
float max30205_read_temperature(I2C_HandleTypeDef *hi2c);





#endif /* API_INC_API_MAX30205_H_ */
