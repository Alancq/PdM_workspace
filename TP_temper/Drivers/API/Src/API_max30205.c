/*
 * API_max30205.c
 *
 *  Created on: Apr 13, 2023
 *      Author: alan
 */
#include "API_max30205.h"

uint8_t max30205_init(I2C_HandleTypeDef *hi2c) {
    return i2c_check_device(hi2c, MAX30205_ADDRESS);
}

float max30205_read_temperature(I2C_HandleTypeDef *hi2c) {
    uint8_t data[2];
    i2c_read(hi2c, MAX30205_ADDRESS, MAX30205_TEMP_REG, data, 2);
    uint16_t raw_temp = (data[0] << 8) | data[1];
    return raw_temp * 0.00390625f;
}
