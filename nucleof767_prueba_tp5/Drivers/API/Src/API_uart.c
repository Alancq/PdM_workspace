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
#define INIT_MSG "Uart Inicializada (115200 8N1)\n\r"
static UART_HandleTypeDef huart;
bool_t uartInit()
{
    // Configurar y habilitar el periférico UART utilizando HAL
    huart.Instance = USARTx; // Reemplazar USARTx por el USART utilizado
    huart.Init.BaudRate = 115200;
    huart.Init.WordLength = UART_WORDLENGTH_8B;
    huart.Init.StopBits = UART_STOPBITS_1;
    huart.Init.Parity = UART_PARITY_NONE;
    huart.Init.Mode = UART_MODE_TX_RX;
    huart.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart.Init.OverSampling = UART_OVERSAMPLING_16;
    if (HAL_UART_Init(&huart) != HAL_OK)
    {
        return false;
    }
    uartSendString((uint8_t *)INIT_MSG);
    return true;
}

void uartSendString(uint8_t *pstring) {
	assert(pstring != NULL);
	//HAL_UART_Transmit(&uartHandle, pstring, strlen(pstring),0xFFFF);
    //HAL_UART_Transmit(&huart, pstring, strlen((const char *)pstring), HAL_MAX_DELAY);
	uint16_t length = strlen((const char *)pstring); // CAlculo el largo del string a enviar
	HAL_UART_Transmit(&huart, pstring, length, ((length+10)*10000)/huart.Init.BaudRate); // Envio datos
}
void uartSendStringSize(uint8_t * pstring, uint16_t size) {
	assert(pstring != NULL);
	assert(size!=0);
	//HAL_UART_Transmit(&uartHandle, pstring, size, 0xFFFF);
    //HAL_UART_Transmit(&huart, pstring, size, HAL_MAX_DELAY);
	HAL_UART_Transmit(&huart, pstring, size, ((size+10)*10000)/huart.Init.BaudRate); // Envio datos
}


void uartReceiveStringSize(uint8_t * pstring, uint16_t size) {
	assert(pstring != NULL);
	assert(size!=0);
	//HAL_UART_Receive(&uartHandle, pstring, size, 0xFFFF); // Recibo datos
    //HAL_UART_Receive(&huart, pstring, size, HAL_MAX_DELAY);
	HAL_UART_Receive(&huart, pstring, size, ((size+10)*10000)/huart.Init.BaudRate); // Recibo datos
}

