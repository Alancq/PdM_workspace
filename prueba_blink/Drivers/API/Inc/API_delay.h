/*
 * API_delay.h
 *
 *  Created on: Mar 18, 2023
 *      Author: alan
 */

#ifndef API_INC_API_DELAY_H_
#define API_INC_API_DELAY_H_
#include <stdint.h>
#include <stdbool.h>
#include "stm32f7xx_hal.h"  		/* <- HAL include */
#include "stm32f7xx_nucleo_144.h" 	/* <- BSP include */
typedef uint32_t tick_t;
typedef bool bool_t;

typedef struct{
   tick_t startTime;
   tick_t duration;
   bool_t running;
} delay_t;
void delayInit( delay_t * delay, tick_t duration );
bool_t delayRead( delay_t * delay );
void delayWrite( delay_t * delay, tick_t duration );


#endif /* API_INC_API_DELAY_H_ */
