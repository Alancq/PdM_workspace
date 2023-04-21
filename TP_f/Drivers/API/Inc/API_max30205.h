/*
 * API_max30205.h
 *
 *  Created on: Apr 13, 2023
 *      Author: alan
 */

#ifndef API_INC_API_MAX30205_H_
#define API_INC_API_MAX30205_H_

#include "main.h"
#include "stm32f7xx_nucleo_144.h"



static float max30205_read_temperature(I2C_HandleTypeDef *hi2c);
// Declaraciones de funciones y variables para la MEF(FiniteStateMachine) de lectura
void lecturaFSM_init();
typedef enum {
    IDLE_STATE,
    READ_TEMPERATURE_STATE,
	PRINT_TEMPERATURE
} lecturaFSM_state_t;

// Variables estáticas para almacenar el estado actual de la FSM y el carácter recibido
static lecturaFSM_state_t currentState ;
static uint8_t receivedChar = 0;
static void Warning_LED();
static void Normal_LED();

#endif /* API_INC_API_MAX30205_H_ */
