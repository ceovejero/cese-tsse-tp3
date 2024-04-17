/*
 * debounce.h
 *
 *  Created on: 25 jul. 2023
 *      Author: CEO
 */

#ifndef API_INC_API_DEBOUNCE_H_
#define API_INC_API_DEBOUNCE_H_

#include "stdint.h"
#include "stdbool.h"

void debounceFSM_init();   // debe cargar el estado inicial
int debounceFSM_update(); // debe leer las entradas, resolver la logica de
                           // transicion de estados y actualizar las salidas
void buttonPressed();      // debe invertir el estado del LED1
void buttonReleased();     // debe invertir el estado del LED3

/* La función readKey debe leer una variable interna del módulo y devolver true o false si la tecla
 * fue presionada. Si devuelve true, debe resetear (poner en false) el estado de la variable.*/
bool readKey();

#endif /* API_INC_API_DEBOUNCE_H_ */
