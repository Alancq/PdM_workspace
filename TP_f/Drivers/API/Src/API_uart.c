/*
 * API_uart.c
 *
 *  Created on: Apr 1, 2023
 *      Author: alan
 */
#include "API_uart.h"
#include <string.h>
#include "main.h"
#define BAUD_RATE 115200
#define INIT_MSG "Uart Inicializada (115200)\n\r"

// Función para inicializar la UART

bool_t uartInit()
{
    // Configurar el periférico UART utilizando HAL
    huart.Instance = USARTx;
    huart.Init.BaudRate = BAUD_RATE;//Establece la tasa de baudios
    huart.Init.WordLength = UART_WORDLENGTH_8B;// Establece la longitud de la palabra en 8 bits
    huart.Init.StopBits = UART_STOPBITS_1; // Establece 1 bit de parada
    huart.Init.StopBits = UART_STOPBITS_1;
    huart.Init.Parity = UART_PARITY_NONE;
    huart.Init.Mode = UART_MODE_TX_RX;
    huart.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart.Init.OverSampling = UART_OVERSAMPLING_16;
    if (HAL_UART_Init(&huart) != HAL_OK)
    {
		Error_Handler();
		return false;
    }
    uartSendString((uint8_t *)INIT_MSG);
    return true;
}
// Función para enviar un string a través de la UART
void uartSendString(uint8_t *pstring) {
	assert(pstring != NULL);// Verifica que el puntero no sea nulo
	// Envía el string utilizando HAL_UART_Transmit
    HAL_UART_Transmit(&huart, pstring, strlen((const char *)pstring), HAL_MAX_DELAY);
}
void uartSendStringSize(uint8_t * pstring, uint16_t size) {
	assert(pstring != NULL);// Verifica que el puntero no sea nulo
	assert(size!=0);// Verifica que el tamaño no sea 0
    HAL_UART_Transmit(&huart, pstring, size, HAL_MAX_DELAY);
}

void uartSendFloat(float value) {
    char buffer[32];// Crea un buffer para almacenar el valor como string
    snprintf(buffer, sizeof(buffer), "%.2f", value); // Convierte el valor float en un string con 2 decimales
    uartSendString((uint8_t *)buffer);// Envía el valor convertido en string
}
void uartReceiveStringSize(uint8_t * pstring, uint16_t size) {
	assert(pstring != NULL);// Verifica que el puntero no sea nulo
	assert(size!=0);// Verifica que el tamaño no sea 0
    HAL_UART_Receive(&huart, pstring, size, HAL_MAX_DELAY);
}
bool_t uartReceiveChar(uint8_t *pchar) {
    assert(pchar != NULL);// Verifica que el puntero no sea nulo
    // recibe un carácter utilizando HAL_UART_Receive con un tiempo de espera de 10 ms
    if (HAL_UART_Receive(&huart, pchar, 1, 10) == HAL_OK) {
        return true;
    }
    return false;
}


