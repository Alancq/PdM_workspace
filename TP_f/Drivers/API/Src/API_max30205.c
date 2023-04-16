/*
 * API_max30205.c
 *
 *  Created on: Apr 13, 2023
 *      Author: alan
 */
#include "API_max30205.h"
#include "API_uart.h"
#include "API_delay.h"
#define PTIME 500
#define QTIME 5000
I2C_HandleTypeDef hi2c;
#define QMSG "Temperatura: "
#define PMSG " 'p' para iniciar la lectura \r\n"
#define PLAY 'p'
#define QUIT 'q'

static delay_t delay;
static delay_t delay2;
void lecturaFSM_init(){
	i2c_init(&hi2c);
	/* pone el estado inicial a BUTTON UP*/
	currentState = IDLE_STATE;
	/*configura la estructura del delay*/
	delayInit(&delay, PTIME);
	delayInit(&delay2, QTIME);

}

uint8_t max30205_init(I2C_HandleTypeDef *hi2c) {
    return i2c_check_device(hi2c, MAX30205_ADDRESS);
}

float max30205_read_temperature(I2C_HandleTypeDef *hi2c) {
    uint8_t data[2];
    i2c_read(hi2c, MAX30205_ADDRESS, MAX30205_TEMP_REG, data, 2);
    uint16_t raw_temp = (data[0] << 8) | data[1];
    return raw_temp * 0.00390625f;
}
void lecturaFSM_update() {
    switch (currentState) {
        case IDLE_STATE:
        	if (uartReceiveChar(&receivedChar)) {
        		if (receivedChar ==PLAY) {
        			currentState = READ_TEMPERATURE_STATE;
        		}
        	}
        	if (delayRead(&delay2))uartSendString((uint8_t *)PMSG);
        	break;

        case READ_TEMPERATURE_STATE:
        	if (uartReceiveChar(&receivedChar)) {
        		if (receivedChar == QUIT) {
        			currentState = IDLE_STATE;
        		}
            } else {
            	if (delayRead(&delay)){
            		float temperature = max30205_read_temperature(&hi2c);
            		uartSendString((uint8_t *)QMSG);
            		//uartSendString((uint8_t *)"Temperature: ");
            		uartSendFloat(temperature);
            		uartSendString((uint8_t *)" C\r\n");
            	}
            }
            break;

        default:
            currentState = IDLE_STATE;
            break;
    }
}
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
void i2c_read(I2C_HandleTypeDef *hi2c, uint8_t addr, uint8_t reg, uint8_t *data, uint16_t size) {
    HAL_I2C_Mem_Read(hi2c, addr << 1, reg, I2C_MEMADD_SIZE_8BIT, data, size, 100);
}

