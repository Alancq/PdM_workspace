/*
 * API_uart.h
 *
 *  Created on: Apr 1, 2023
 *      Author: alan
 */

#ifndef API_INC_API_UART_H_
#define API_INC_API_UART_H_
#include <stdbool.h>
#include <stdint.h>
#include "stm32f7xx_hal.h"
#include "stm32f7xx_hal_uart.h"
#include "string.h"
#include "assert.h"
typedef bool bool_t;

bool_t uartInit();

void uartSendString(uint8_t * pstring);

void uartSendStringSize(uint8_t * pstring, uint16_t size);

void uartReceiveStringSize(uint8_t * pstring, uint16_t size);




#endif /* API_INC_API_UART_H_ */
