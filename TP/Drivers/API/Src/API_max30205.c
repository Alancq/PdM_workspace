/*
 * API_max30205.c
 *
 *  Created on: Apr 13, 2023
 *      Author: alan
 */
#include "API_max30205.h"

#define MAX30205_ADDR (0x90)
#define MAX30205_TEMP_REG (0x00)

float readMax30205Temperature(I2C_HandleTypeDef *hi2c) {
    uint8_t rawData[2];
    float temperature;

    HAL_I2C_Mem_Read(hi2c, MAX30205_ADDR, MAX30205_TEMP_REG, 1, rawData, 2, 100);

    int16_t tempInt = (int16_t)(rawData[0] << 8 | rawData[1]);
    temperature = tempInt * 0.00390625;

    return temperature;
}

