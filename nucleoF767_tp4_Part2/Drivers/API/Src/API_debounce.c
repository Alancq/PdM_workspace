/*
 * API_debounce.c
 *
 *  Created on: Mar 29, 2023
 *      Author: alan
 */
#include "API_debounce.h"
#include "API_delay.h"
#define DEBOUNCE_TIME 40
/* Private functions ---------------------------------------------------------*/
/* ################ Button state definitions ################ */
/* This typedef can not be declared as static or private variable because it is on a .c file*/

typedef enum{
	BUTTON_UP,
	BUTTON_FALLING,
	BUTTON_DOWN,
	BUTTON_RISING,
} debounceState_t;

static delay_t delay;
static debounceState_t buttonDebounce;
static bool_t buttonPressed;


void debounceFSM_init(){
	/* pone el estado inicial a BUTTON UP*/
	buttonDebounce = BUTTON_UP;
	/*configura la estructura del delay*/
	delayInit(&delay, DEBOUNCE_TIME);
}


void debounceFSM_update(){
	switch(buttonDebounce){
	/* checkea si el boton fue apretado , y despues del delay pasa al estado falling*/
	case BUTTON_UP:
		if(BSP_PB_GetState(BUTTON_USER)){
			/* Update to next state */
			buttonDebounce = BUTTON_FALLING;
			/* Start the delay count */
			delayRead(&delay);
		}
		break;

	case BUTTON_FALLING:

		if(delayRead(&delay)){

			if(BSP_PB_GetState(BUTTON_USER)) {

				buttonDebounce = BUTTON_DOWN;

				buttonPressed = true;
			}
			else{
				/* en caso de ruido volver al estado anterior*/
				buttonDebounce = BUTTON_UP;
			}
		}
		break;

	case BUTTON_DOWN:
		if(!BSP_PB_GetState(BUTTON_USER)){
			buttonDebounce = BUTTON_RISING;
			delayRead(&delay);
		}
		break;

	case BUTTON_RISING:
		/* ve si el boton fue soltado*/
		if(delayRead(&delay)){
			if(!BSP_PB_GetState(BUTTON_USER)){
				buttonDebounce = BUTTON_UP;
				buttonPressed = false;
			}
			else{
				/* en caso de ruido volver al estado anterior*/
				buttonDebounce = BUTTON_DOWN;
			}
		}
		break;
	default:
		buttonDebounce = BUTTON_UP;
		break;
	}

}

//agarra la variable booleana buttonPressed generar una bandera
bool_t readKey(){
	bool_t flag = false;
	if (buttonPressed) {
		flag = true;
		buttonPressed = false;
	}
	return flag;
}
