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
#define QMSG "Temperatura: " //primera parte del mensaje para mostrar la temperatura
#define PMSG " 'p' para iniciar la lectura \r\n" // mensaje de espera para el caracter p para iniciar la lectura
#define PLAY 'p' //caracter de entrada para iniciar y mostrar la lectura
#define QUIT 'q' //caracter para dejar de realizar la lectura y envio de la temperatrua por uart
#define T_CONST 0.00390625f //temperatura constante multiplicador
I2C_HandleTypeDef hi2c;


// Variables para almacenar información de los tiempos de espera
static delay_t delay;
static delay_t delay2;

// Inicializa la máquina de estados finitos (FSM) de lectura
void lecturaFSM_init(){
	i2c_init(&hi2c); //inicialiaza i2c
	currentState = IDLE_STATE; //iniciando el estado default
	delayInit(&delay, PTIME); //asignamos los delays para el mensaje de recepcion de 'q' y para el muestreo de la temperatura
	delayInit(&delay2, QTIME);
	uartSendString((uint8_t *)PMSG); //manda el primer mensaje indicando el caracter para iniciar lectura

}

// Inicializa el sensor MAX30205
uint8_t max30205_init(I2C_HandleTypeDef *hi2c) {
    return i2c_check_device(hi2c, MAX30205_ADDRESS);
}

// Lee la temperatura del sensor MAX30205
float max30205_read_temperature(I2C_HandleTypeDef *hi2c) {
    uint8_t data[2]; //array para almacenar los datos de temperatura en bruto recibidos del sensor.
    i2c_read(hi2c, MAX30205_ADDRESS, MAX30205_TEMP_REG, data, 2);	/*Se llama a la función i2c_read, que lee los datos de temperatura del
    																sensor MAX30205 utilizando la comunicación I2C. Los argumentos que se pasan a la función son:
																	hi2c: Un puntero a la estructura que maneja la comunicación I2C.
																	MAX30205_ADDRESS: La dirección I2C del sensor MAX30205.
																	MAX30205_TEMP_REG: El registro de temperatura dentro del sensor.
																	data: El array en el que se almacenarán los datos leídos.
																	2: La cantidad de bytes a leer (en este caso, 2 bytes).*/
    uint16_t raw_temp = (data[0] << 8) | data[1];	/*Se crea una variable uint16_t llamada raw_temp y se combina el primer byte (data[0])
     	 	 	 	 	 	 	 	 	 	 	 	 y el segundo byte (data[1]) para obtener un valor de 16 bits. El primer byte se desplaza
     	 	 	 	 	 	 	 	 	 	 	 	 8 bits hacia la izquierda (multiplicado por 2^8) y se realiza una operación OR bit a bit
     	 	 	 	 	 	 	 	 	 	 	 	 con el segundo byte.*/
    return raw_temp * T_CONST; /*se multiplica por la resolución del sensor (0.00390625 grados Celsius por bit),
     	 	 	 	 	 	 	 convirtiendo el valor en bruto en una temperatura en ºC y devuelve este valor como un float*/
}
// Actualiza el estado de la máquina de estados finitos (FSM)
void lecturaFSM_update() {
    // Cambia entre los estados de la máquina de estados finitos
    switch (currentState) {
        case IDLE_STATE:
            // Espera a que se reciba el comando 'p' para iniciar la lectura
        	if (uartReceiveChar(&receivedChar)) {
        		if (receivedChar ==PLAY) { //si el caracter ingresado es 'q' se va al estado READ_TEMPERATURE_STATE
        			currentState = READ_TEMPERATURE_STATE;
        		}
        	}
            //espera 5s y Envía un mensaje de PMSG ("'q' para iniciar la lectura" )
        	if (delayRead(&delay2))uartSendString((uint8_t *)PMSG);
        	break;

        case READ_TEMPERATURE_STATE:
        	if (uartReceiveChar(&receivedChar)) { //si se ingresa un caracter por uart
        		if (receivedChar == QUIT) { 	//si se recibe el caracter QUIT 'q' retorna al primer estado IDLE_STATE
        			currentState = IDLE_STATE;
        		}
            } else {
            	if (delayRead(&delay)){
            		float temperature = max30205_read_temperature(&hi2c);// Lee la temperatura del sensor MAX30205
            		uartSendString((uint8_t *)QMSG);// Envía el mensaje "QMSG" por UART
            		uartSendFloat(temperature);// Envía la temperatura por UART
            		uartSendString((uint8_t *)" C\r\n");
            	}
            }
            break;

        default:
        	// Estado por defecto, regresa al estado IDLE_STATE
            currentState = IDLE_STATE;
            break;
    }
}


