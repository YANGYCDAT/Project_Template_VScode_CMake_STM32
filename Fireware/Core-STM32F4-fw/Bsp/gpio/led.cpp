#include "common_inc.h"
#include "led.h"



void LED::SetPink(bool state) {
    if (state) {
        LED_PINK_ON();
    } else {
        LED_PINK_OFF();
    }
}


void LED::TogglePink(void) {
    LED_PINK_TOGGLE();
}