/*
 * API_uart.c
 *
 *  Created on: Apr 1, 2023
 *      Author: alan
 */
#include "API_uart.h"
#include <string.h>
#include "main.h"
#include "API_uart.h"
#include "stm32f7xx_hal.h"


static UART_HandleTypeDef huart;

// Prototipos de funciones privadas
static void uartErrorCallback(UART_HandleTypeDef *huart);

bool_t uartInit()
{
    // Configurar y habilitar el periférico UART utilizando HAL
    huart.Instance = USART3; // Utilizar USART2 para la comunicación a través del ST-Link
    huart.Init.BaudRate = 115200;
    huart.Init.WordLength = UART_WORDLENGTH_8B;
    huart.Init.StopBits = UART_STOPBITS_1;
    huart.Init.Parity = UART_PARITY_NONE;
    huart.Init.Mode = UART_MODE_TX_RX;
    huart.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart.Init.OverSampling = UART_OVERSAMPLING_16;
    //HAL_UART_MspInit(&huart);
    if (HAL_UART_Init(&huart) != HAL_OK)
    {
        return false;
    }

    //HAL_UART_RegisterCallback(&huart, HAL_UART_ERROR_CB_ID, uartErrorCallback);

    return true;
}

void uartSendString(uint8_t *pstring)
{
    HAL_UART_Transmit(&huart, pstring, strlen(pstring), HAL_MAX_DELAY);
	//uint16_t length = strlen((const char *)pstring); // CAlculo el largo del string a enviar
		//HAL_UART_Transmit(&huart, pstring, length, ((length+10)*10000)/huart.Init.BaudRate); // Envio datos
}

void uartSendStringSize(uint8_t *pstring, uint16_t size)
{
    HAL_UART_Transmit(&huart, pstring, size, HAL_MAX_DELAY);
	//HAL_UART_Transmit(&huart, pstring, size, ((size+10)*10000)/huart.Init.BaudRate); // Envio datos
}

void uartReceiveStringSize(uint8_t *pstring, uint16_t size)
{
    HAL_UART_Receive(&huart, pstring, size, HAL_MAX_DELAY);
	//HAL_UART_Receive(&huart, pstring, size, ((size+10)*10000)/huart.Init.BaudRate); // Recibo datos

}

// Implementación de funciones privadas
static void uartErrorCallback(UART_HandleTypeDef *huart)
{
    // Manejar errores de UART aquí, si es necesario
}
