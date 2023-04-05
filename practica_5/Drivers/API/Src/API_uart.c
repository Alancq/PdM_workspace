/*
 * API_uart.c
 *
 *  Created on: Apr 1, 2023
 *      Author: alan
 */
#include "API_uart.h"
#include <string.h>
#include "main.h"
#define BAUD_RATE 9600
static UART_HandleTypeDef uartHandle;
bool_t uartInit() {
	// Inicializo UART
	uartHandle.Instance = USARTx;
	uartHandle.Init.BaudRate = BAUD_RATE;
	uartHandle.Init.WordLength = UART_WORDLENGTH_8B;
	uartHandle.Init.StopBits = UART_STOPBITS_1;
	uartHandle.Init.Parity = UART_PARITY_NONE;
	uartHandle.Init.Mode = UART_MODE_TX_RX;
	uartHandle.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	uartHandle.Init.OverSampling = UART_OVERSAMPLING_16;

	if(HAL_UART_Init(&uartHandle) != HAL_OK) {
		return false;
	}



	return true;
}

void uartSendString(uint8_t *pstring) {
	assert(pstring != NULL);
	HAL_UART_Transmit(&uartHandle, pstring, strlen(pstring),0xFFFF);
}
void uartSendStringSize(uint8_t * pstring, uint16_t size) {
	assert(pstring != NULL);
	assert(size!=0);
	HAL_UART_Transmit(&uartHandle, pstring, size, 0xFFFF);
}


void uartReceiveStringSize(uint8_t * pstring, uint16_t size) {
	assert(pstring != NULL);
	assert(size!=0);
	HAL_UART_Receive(&uartHandle, pstring, size, 0xFFFF); // Recibo datos
}

