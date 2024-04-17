/*
 * debounce.c
 *
 *  Created on: 25 jul. 2023
 *      Author: CEO
 */

#include "hal.h"
#include "delay.h"
#include "debounce.h"

#define DEBOUNCE_PERIOD 40

typedef enum {
    BUTTON_UP,
    BUTTON_FALLING,
    BUTTON_DOWN,
    BUTTON_RAISING,
} debounceState_t;

bool_t pressed;
delay_t delayDebounceFSM;    // Estructura para control de tiempos
debounceState_t actualState; // Variable de estado (global) interna de Maquina de Estados

/**
 * @brief  Inicializa la Maquina de Estado - debounce
 * @param  None
 * @retval None
 */
void debounceFSM_init() {
    actualState = BUTTON_UP;
    BSP_PB_Init(BUTTON_USER, BUTTON_MODE_GPIO);
    delayInit(&delayDebounceFSM, DEBOUNCE_PERIOD); // control de tiempos para debounce
}

/**
 * @brief  Implementacion de la maquia de estado.
 * @param  None
 * @retval None
 */
int debounceFSM_update() {
    switch (actualState) {
    case BUTTON_UP:
        if (BSP_PB_GetState(BUTTON_USER)) {
            actualState = BUTTON_FALLING; // estado siguiente
            delayRead(&delayDebounceFSM); // inicia la cuenta de antirrebote
        }
        return(actualState);
        break;
    case BUTTON_FALLING:
        if (delayRead(&delayDebounceFSM)) // control de tiempo de antirrebote
        { // padado el tiempo de antirebote se controla el estado del pulsador
            if (BSP_PB_GetState(BUTTON_USER)) { // si sigue presionado se pasa al sigte estado
                actualState = BUTTON_DOWN;
                pressed = true; // estado presionado
            } else              // si se detecta estado inestable del pulsador
            {
                actualState = BUTTON_UP; // regreso al estado previo
            }
        }
        return(actualState);
        break;
    case BUTTON_DOWN:
        if (!BSP_PB_GetState(BUTTON_USER)) { // si el pulsador se libera se regresa al estado anterior
            actualState = BUTTON_RAISING;
            delayRead(&delayDebounceFSM);
        }
        return(actualState);
        break;
    case BUTTON_RAISING:
        if (delayRead(&delayDebounceFSM)) // control de tiempo de antirrebote
        { // padado el tiempo de antirebote se controla el estado del pulsador
            if (!BSP_PB_GetState(BUTTON_USER)) { //  si se libera se pasa al sigte estado
                actualState = BUTTON_UP;
                pressed = false;
                ;  // NO presionado
            } else // si se detecta estado inestable del pulsador
            {
                actualState = BUTTON_DOWN; // regreso al estado previo
            }
        }
        return(actualState);
        break;
    default:
        // si se carga algun valor no contemplado, se regresa al estado inicial
        actualState = 99;//BUTTON_UP;
        break;
    }
}

/**
 * @brief  boton presionado
 * @param  None
 * @retval true si se presiono el pulsador
 */
const bool_t readKey() {
    bool_t flag = false;
    if (pressed) {
        flag = true;
        pressed = false;
    }
    return flag;
}
