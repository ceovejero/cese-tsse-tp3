

#include "stdint.h"
#include "stdbool.h"

typedef enum {
    BUTTON_USER = 0,
    /* Alias */
    BUTTON_KEY = BUTTON_USER
} Button_TypeDef;

typedef enum {
    BUTTON_MODE_GPIO = 0,
    /* Alias */
    BUTTON_MODE_EXTI = 1
} ButtonMode_TypeDef;

void BSP_PB_Init(Button_TypeDef Button, ButtonMode_TypeDef ButtonMode);

bool BSP_PB_GetState(Button_TypeDef Button);