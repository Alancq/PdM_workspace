/*
 * API_debounce.h
 *
 *  Created on: Mar 29, 2023
 *      Author: alan
 */


#ifndef API_INC_API_DEBOUNCE_H_
#define API_INC_API_DEBOUNCE_H_
#include <stdbool.h>

typedef bool bool_t;
void debounceFSM_init();
void debounceFSM_update();
bool_t readKey();
#endif /* API_INC_API_DEBOUNCE_H_ */
