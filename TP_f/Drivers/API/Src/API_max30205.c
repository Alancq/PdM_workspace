/*
 * API_max30205.c
 *
 *  Created on: Apr 13, 2023
 *      Author: alan
 */
#include "API_max30205.h"
#include "API_uart.h"
#include "API_delay.h"
#include "API_i2c.h"

// Definiciones de constantes y variables
#define MAX30205_ADDRESS      0x48	/*Dirección I2C del sensor MAX30205 y el registro de temperatura*/
#define MAX30205_TEMP_REG     0x00
#define PTIME 500 //tiempo delay para mandar el mensage QMSG correspondiente a la lectura del sensor max30205
#define QTIME 5000 //tiempo delay para mandar el mensage PMSG correspondiente al mensaje de "'p' para iniciar la lectura"
#define QMSG "Temperatura: "
#define PMSG " 'p' para iniciar la lectura \r\n"
#define PLAY 'p' //caracter de entrada para iniciar y mostrar la lectura
#define QUIT 'q' //caracter para dejar de realizar la lectura y envio de la temperatrua por uart
#define T_CONST 0.00390625f //temperatura constante multiplicador
#define TEMPW 39.0 //

static I2C_HandleTypeDef hi2c;
static float temperature;
// Variables para almacenar información de los tiempos de espera
static delay_t delay;
static delay_t delay2;
static void Warning_LED(){
	BSP_LED_On(LED3);
}
static void Normal_LED(){
	BSP_LED_Off(LED3);
}
// Inicializa la máquina de estados finitos (FSM) de lectura
 void lecturaFSM_init(){
	BSP_LED_Init(LED3);
	i2c_init(&hi2c); //inicialiaza i2c
	currentState = IDLE_STATE; //iniciando el estado default
	delayInit(&delay, PTIME); //asignamos los delays para el mensaje de recepcion de 'q' y para el muestreo de la temperatura
	delayInit(&delay2, QTIME);
	uartSendString((uint8_t *)PMSG); //manda el primer mensaje indicando el caracter para iniciar lectura


}




// Lee la temperatura del sensor MAX30205
static float max30205_read_temperature(I2C_HandleTypeDef *hi2c) {
    uint8_t data[2]; //almacena los datos de temperatura en bruto recibidos del sensor.
    // Lee los datos de temperatura del sensor MAX30205 a través de la comunicación I2C y los guarda en el array "data".
    i2c_read(hi2c, MAX30205_ADDRESS, MAX30205_TEMP_REG, data, 2);
    uint16_t raw_temp = (data[0] << 8) | data[1];	/*Combina el primer y segundo byte para obtener
    												un valor de 16 bits que representa la
    												temperatura en bruto.*/
    return raw_temp * T_CONST; /*Convierte el valor en bruto de la temperatura a grados Celsius y devuelve este valor como un float.*/
}
// Actualiza el estado de la máquina de estados finitos (FSM)
void lecturaFSM_update() {
    switch (currentState) {
        case IDLE_STATE:
            // Espera a que se reciba el comando 'p' para iniciar la lectura
        	if (uartReceiveChar(&receivedChar) ) {
        		if (receivedChar ==PLAY) {
        			currentState = READ_TEMPERATURE_STATE;
        		}
        	}
            //espera 5s y envia el mensaje con la informacion para cambiar de estado
        	if (delayRead(&delay2))uartSendString((uint8_t *)PMSG);
        	break;

        case READ_TEMPERATURE_STATE:
        	if (uartReceiveChar(&receivedChar)) {
        		if (receivedChar == QUIT) { 	//si se recibe el caracter especificado deja de leer y mostrar la temperatura
        			currentState = IDLE_STATE;
        		}
        	} else {

        		temperature = max30205_read_temperature(&hi2c);// Lee la temperatura del sensor MAX30205
        		if(temperature>=TEMPW){//se enciende el led de alerta si hay una temperatura alta
        			Warning_LED();
        		}else{
        			Normal_LED();
        		}
        		currentState=PRINT_TEMPERATURE;

            }
            break;
        case PRINT_TEMPERATURE: //imprime por uart la temperatura
        	if (delayRead(&delay)){
        		uartSendString((uint8_t *)QMSG);
        		uartSendFloat(temperature);
        		uartSendString((uint8_t *)" C\r\n");
        		currentState = READ_TEMPERATURE_STATE;
        	}
        	break;

        default:
        	// Estado por defecto, regresa al estado IDLE_STATE
            currentState = IDLE_STATE;
            break;
    }
}


