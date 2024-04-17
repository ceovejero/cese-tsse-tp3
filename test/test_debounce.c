/************************************************************************************************
Copyright (c) 2023, Cesar Ovejero <cesarovejero@gmail.com>

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

SPDX-License-Identifier: MIT
*************************************************************************************************/

/** @file test_API_debounce.c
 ** @brief Conjunto de Tests para la API de LEDs.
 **/

/* === Headers files inclusions ===================================== */

#include "unity.h"
#include "debounce.h"
#include "mock_hal.h"
#include "mock_delay.h"
//#include "stdbool.h"

/* === Macros definitions =========================================== */

#define DEBOUNCE_PERIOD 40

/* === Private data type declarations ==================================== */

 typedef enum {
     BUTTON_UP,
     BUTTON_FALLING,
     BUTTON_DOWN,
     BUTTON_RAISING,
 } debounceState_t;


/* === Private variable declarations ====================================== */

extern delay_t delayDebounceFSM;
extern debounceState_t actualState;
extern bool_t pressed;

/* === Private function declarations ====================================== */

/* === Public variable definitions ===========================================*/

/* === Private variable definitions ==========================================*/

/* === Private function implementation ====================================== */

/// @brief Test 1
/// Al inicializar la maquina de estados actualState debe ser BUTTON_UP
/// .
void test_inicializacion_del_antirrebote(void) {
    
    BSP_PB_Init_Expect(BUTTON_USER, BUTTON_MODE_GPIO);
    delayInit_Expect(&delayDebounceFSM, DEBOUNCE_PERIOD);
        
    debounceFSM_init();
    // Se inicializa la FSM - variable actualState = BUTTON_UP
    TEST_ASSERT_EQUAL_INT(BUTTON_UP, actualState);

}

/// @brief Test 2
/// Al presionar el boton, el estado actual debe cambiar a BUTTON_FALLING
/// .
void test_estado_BUTTON_FALLING_del_antirrebote(void) {

    BSP_PB_Init_Expect(BUTTON_USER, BUTTON_MODE_GPIO);
    delayInit_Expect(&delayDebounceFSM, DEBOUNCE_PERIOD);

    debounceFSM_init();
    // Se inicializa la FSM - variable actualState = BUTTON_UP
        
    BSP_PB_GetState_ExpectAndReturn(BUTTON_USER, true);
    delayRead_ExpectAndReturn(&delayDebounceFSM, true);

    debounceFSM_update();
    // Se actualiza la FSM - variable actualState = BUTTON_FALLING

    TEST_ASSERT_EQUAL_INT(BUTTON_FALLING, actualState);
}

/// @brief Test 3
/// Al seguir presionado el boton, el estado actual debe cambiar a BUTTON_DOWN
/// .
void test_estado_BUTTON_DOWN_del_antirrebote(void) {

    BSP_PB_Init_Expect(BUTTON_USER, BUTTON_MODE_GPIO);
    delayInit_Expect(&delayDebounceFSM, DEBOUNCE_PERIOD);

    debounceFSM_init();
    // Se inicializa la FSM - variable actualState = BUTTON_UP
        
    BSP_PB_GetState_ExpectAndReturn(BUTTON_USER, true);
    delayRead_ExpectAndReturn(&delayDebounceFSM, true);

    debounceFSM_update();
    // Se actualiza la FSM - variable actualState = BUTTON_FALLING

    delayRead_ExpectAndReturn(&delayDebounceFSM, true);
    BSP_PB_GetState_ExpectAndReturn(BUTTON_USER, true);

    debounceFSM_update();
    // Se actualiza la FSM - variable actualState = BUTTON_DOWN

    TEST_ASSERT_EQUAL_INT(BUTTON_DOWN, actualState);
}

/// @brief Test 4
/// Al liberar el boton, el estado actual debe cambiar a BUTTON_RAISING
/// .
void test_estado_BUTTON_RAISING_del_antirrebote(void) {

    BSP_PB_Init_Expect(BUTTON_USER, BUTTON_MODE_GPIO);
    delayInit_Expect(&delayDebounceFSM, DEBOUNCE_PERIOD);

    debounceFSM_init();
    // Se inicializa la FSM - variable actualState = BUTTON_UP
        
    BSP_PB_GetState_ExpectAndReturn(BUTTON_USER, true);
    delayRead_ExpectAndReturn(&delayDebounceFSM, true);

    debounceFSM_update();
    // Se actualiza la FSM - variable actualState = BUTTON_FALLING

    delayRead_ExpectAndReturn(&delayDebounceFSM, true);
    BSP_PB_GetState_ExpectAndReturn(BUTTON_USER, true);

    debounceFSM_update();
    // Se actualiza la FSM - variable actualState = BUTTON_DOWN

    BSP_PB_GetState_ExpectAndReturn(BUTTON_USER, false);
    delayRead_ExpectAndReturn(&delayDebounceFSM, false);

    debounceFSM_update();
    // Se actualiza la FSM - variable actualState = BUTTON_RAISING

    TEST_ASSERT_EQUAL_INT(BUTTON_RAISING, actualState);

}

/// @brief Test 5
/// Al liberar el boton, el estado actual debe cambiar a BUTTON_UP
/// .
void test_estado_BUTTON_UP_luego_de_RAISING (void) {

    BSP_PB_Init_Expect(BUTTON_USER, BUTTON_MODE_GPIO);
    delayInit_Expect(&delayDebounceFSM, DEBOUNCE_PERIOD);

    debounceFSM_init();
    // Se inicializa la FSM - variable actualState = BUTTON_UP
        
    BSP_PB_GetState_ExpectAndReturn(BUTTON_USER, true);
    delayRead_ExpectAndReturn(&delayDebounceFSM, true);

    debounceFSM_update();
    // Se actualiza la FSM - variable actualState = BUTTON_FALLING

    delayRead_ExpectAndReturn(&delayDebounceFSM, true);
    BSP_PB_GetState_ExpectAndReturn(BUTTON_USER, true);

    debounceFSM_update();
    // Se actualiza la FSM - variable actualState = BUTTON_DOWN

    BSP_PB_GetState_ExpectAndReturn(BUTTON_USER, false);
    delayRead_ExpectAndReturn(&delayDebounceFSM, false);

    debounceFSM_update();
    // Se actualiza la FSM - variable actualState = BUTTON_RAISING

    delayRead_ExpectAndReturn(&delayDebounceFSM, true);
    BSP_PB_GetState_ExpectAndReturn(BUTTON_USER, false);

    debounceFSM_update();
    // Se actualiza la FSM - variable actualState = BUTTON_UP

    TEST_ASSERT_EQUAL_INT(BUTTON_UP, actualState);
}

/// @brief Test 6
/// Al presionar el boton, el estado actual debe cambiar a BUTTON_FALLING
/// .
void test_Button_Pressed_del_antirrebote(void) {

    BSP_PB_Init_Expect(BUTTON_USER, BUTTON_MODE_GPIO);
    delayInit_Expect(&delayDebounceFSM, DEBOUNCE_PERIOD);

    debounceFSM_init();
    // Se inicializa la FSM - variable actualState = BUTTON_UP
        
    BSP_PB_GetState_ExpectAndReturn(BUTTON_USER, true);
    delayRead_ExpectAndReturn(&delayDebounceFSM, true);

    debounceFSM_update();
    // Se actualiza la FSM - variable actualState = BUTTON_FALLING

    delayRead_ExpectAndReturn(&delayDebounceFSM, true);
    BSP_PB_GetState_ExpectAndReturn(BUTTON_USER, true);

    debounceFSM_update();
    // Se actualiza la FSM - variable actualState = BUTTON_DOWN

    TEST_ASSERT_EQUAL_INT(1, pressed);
}

