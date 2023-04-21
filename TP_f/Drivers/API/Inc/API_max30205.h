/*
 * API_max30205.h
 *
 *  Created on: Apr 13, 2023
 *      Author: alan
 */

#ifndef API_INC_API_MAX30205_H_
#define API_INC_API_MAX30205_H_

#include "main.h"



// Declaraciones de funciones para inicializar el sensor MAX30205 y leer la temperatura
uint8_t max30205_init(I2C_HandleTypeDef *hi2c);
float max30205_read_temperature(I2C_HandleTypeDef *hi2c);

// Declaraciones de funciones y variables para la MEF(FiniteStateMachine) de lectura
void lecturaFSM_init();
typedef enum {
    IDLE_STATE,
    READ_TEMPERATURE_STATE
} lecturaFSM_state_t;

// Variables estáticas para almacenar el estado actual de la FSM y el carácter recibido
static lecturaFSM_state_t currentState ;
static uint8_t receivedChar = 0;

// Declaraciones de funciones de I2C
void i2c_init(I2C_HandleTypeDef *hi2c);
void i2c_read(I2C_HandleTypeDef *hi2c, uint8_t addr, uint8_t reg, uint8_t *data, uint16_t size);

#endif /* API_INC_API_MAX30205_H_ */
