/*
 * API_delay.c
 *
 *  Created on: Mar 18, 2023
 *      Author: Alan Cornejo
 */
#include "API_delay.h"
void delayInit( delay_t * delay, tick_t duration ){
	  delay->duration=duration;
	  delay->running=false;

}
bool_t delayRead( delay_t * delay ){
	if((delay->running)==false){
		delay->running=true;
		delay->startTime=HAL_GetTick();
	}
	else{
		if(HAL_GetTick()-delay->startTime>=delay->duration){
			delay->running=false;
			return true;
		}
	}
	return false;
}
void delayWrite( delay_t * delay, tick_t duration ){
	delay->duration=duration;
}
