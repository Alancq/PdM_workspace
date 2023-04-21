/*
 * API_delay.c
 *
 *  Created on: Mar 18, 2023
 *      Author: Alan Cornejo
 */
#include "API_delay.h"
// Inicializa el delay con la duración especificada
void delayInit( delay_t * delay, tick_t duration ){
	  delay->duration=duration;
	  delay->running=false;

}
// Lee el estado del delay y actualiza su estado
bool_t delayRead( delay_t * delay ){
	if((delay->running)==false){
		delay->running=true;
		delay->startTime=HAL_GetTick();
	}
	else{
		// Si el tiempo actual menos el tiempo de inicio es mayor o igual a la duración del delay
		if(HAL_GetTick()-delay->startTime>=delay->duration){
			delay->running=false;
			return true;// Retorna verdadero indicando que el delay ha finalizado

		}
	}
	return false;
}
// Establece la duración del delay
void delayWrite( delay_t * delay, tick_t duration ){
	delay->duration=duration;
}
