#pragma once
#include "stm32f4xx_hal_gpio.h"

#define  LED_PINK_ON()      	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_15, GPIO_PIN_RESET)
#define  LED_PINK_OFF()     	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_15, GPIO_PIN_SET)
#define  LED_PINK_TOGGLE()  	HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_15)

#define  LED_BLUE_ON()      	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_14, GPIO_PIN_RESET)
#define  LED_BLUE_OFF()     	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_14, GPIO_PIN_SET)
#define  LED_BLUE_TOGGLE()  	HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_14)

#define  LED_GREEN_ON()      	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_13, GPIO_PIN_RESET)
#define  LED_GREEN_OFF()     	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_13, GPIO_PIN_SET)
#define  LED_GREEN_TOGGLE()  	HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_13)

#define  LED_RED_ON()      		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, GPIO_PIN_RESET)
#define  LED_RED_OFF()     		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, GPIO_PIN_SET)
#define  LED_RED_TOGGLE()  		HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_12)

#define  LED_ORANGE_ON()      	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11, GPIO_PIN_RESET)
#define  LED_ORANGE_OFF()     	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11, GPIO_PIN_SET)
#define  LED_ORANGE_TOGGLE()  	HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_11)



class Led {
public:
    void SetPink(bool state);
    void TogglePink(void);
};