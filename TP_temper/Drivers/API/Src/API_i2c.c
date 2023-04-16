/*
 * API_i2c.c
 *
 *  Created on: Apr 15, 2023
 *      Author: alan
 */
#include "API_i2c.h"

void i2c_init(I2C_HandleTypeDef *hi2c) {
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_I2C1_CLK_ENABLE();

	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = GPIO_PIN_8 | GPIO_PIN_9;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF4_I2C1;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	hi2c->Instance = I2C1;
	hi2c->Init.Timing = 0x00503D5A; // Configuración de Timing para 400 kHz
	hi2c->Init.OwnAddress1 = 0;
	hi2c->Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	hi2c->Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	hi2c->Init.OwnAddress2 = 0;
	hi2c->Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	hi2c->Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
	HAL_I2C_Init(hi2c);
}

uint8_t i2c_check_device(I2C_HandleTypeDef *hi2c, uint8_t addr) {
    return (HAL_I2C_IsDeviceReady(hi2c, addr << 1, 3, 100) == HAL_OK);
}

void i2c_read(I2C_HandleTypeDef *hi2c, uint8_t addr, uint8_t reg, uint8_t *data, uint16_t size) {
    HAL_I2C_Mem_Read(hi2c, addr << 1, reg, I2C_MEMADD_SIZE_8BIT, data, size, 100);
}


