/*
 * API_i2c.h
 *
 *  Created on: Apr 21, 2023
 *      Author: alan
 */

#ifndef API_INC_API_I2C_H_
#define API_INC_API_I2C_H_

#include "main.h"
// Declaraciones de funciones de I2C
void i2c_init(I2C_HandleTypeDef *hi2c);
void i2c_read(I2C_HandleTypeDef *hi2c, uint8_t addr, uint8_t reg, uint8_t *data, uint16_t size);

#endif /* API_INC_API_I2C_H_ */
