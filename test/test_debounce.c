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

/* === Macros definitions =========================================== */

/* === Private data type declarations ==================================== */

// typedef enum {
//     BUTTON_USER = 0,
//     /* Alias */
//     BUTTON_KEY = BUTTON_USER
// } Button_TypeDef;

// typedef enum {
//     BUTTON_MODE_GPIO = 0,
//     /* Alias */
//     BUTTON_MODE_EXTI = 1
// } ButtonMode_TypeDef;

// typedef enum {
//     BUTTON_UP,
//     BUTTON_FALLING,
//     BUTTON_DOWN,
//     BUTTON_RAISING,
// } debounceState_t;

typedef enum {
    BUTTON_RELEASED = 0,
    /* Alias */
    BUTTON_PRESSED = 1
} buttonState_t;

/* === Private variable declarations ====================================== */

// delay_t delayDebounceFSM; // Estructura para control de tiempos
// debounceState_t actualState;
// bool_t pressed;
buttonState_t buttonState;
buttonState_t * p_buttonState = &buttonState;

/* === Private function declarations ====================================== */

/* === Public variable definitions ===========================================*/

/* === Private variable definitions ==========================================*/

/* === Private function implementation ====================================== */

/// @brief Test 1
/// Al inicializar la FSM del mock de Botones actualState debe ser BUTTON_UP
/// .
void test_inicializar_Button_en_UP(void) {

    // BSP_PB_Init(0, 0);
    // BSP_PB_Init_Ignore(BUTTON_USER, BUTTON_MODE_GPIO);
    //   TEST_ASSERT_EQUAL_INT(BUTTON_RELEASED, *p_buttonState);
    TEST_FAIL_MESSAGE("Falla en la prueba de inicialización de la FSM de Botones.");
}

/// @brief Test 2
/// Al inicializar la maquina de estados actualState debe ser BUTTON_UP
/// .
void test_inicializacion_del_antirrebote(void) {
    // debounceFSM_init();
    // TEST_ASSERT_EQUAL_INT(BUTTON_UP, actualState);
    TEST_IGNORE_MESSAGE("TBD Test 2");
}

/// @brief Test 3
/// Al presionar el boton, el estado actual debe cambiar a BUTTON_FALLING
/// .
void test_estado_BUTTON_FALLING_del_antirrebote(void) {

    TEST_IGNORE_MESSAGE("TBD Test 3");
}

/// @brief Test 4
/// Al seguir presionado el boton, el estado actual debe cambiar a BUTTON_DOWN
/// .
void test_estado_BUTTON_DOWN_del_antirrebote(void) {

    TEST_IGNORE_MESSAGE("TBD Test 4");
}

/// @brief Test 5
/// Al liberar el boton, el estado actual debe cambiar a BUTTON_RAISING
/// .
void test_estado_BUTTON_RAISING_del_antirrebote(void) {

    TEST_IGNORE_MESSAGE("TBD Test 5");
}