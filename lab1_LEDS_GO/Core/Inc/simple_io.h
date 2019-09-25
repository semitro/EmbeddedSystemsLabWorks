#ifndef SIMPLE_IO_H
#define SIMPLE_IO_H

#include "stm32f4xx_hal.h"

typedef enum Color {
	COLOR_RED = GPIO_PIN_15,
	COLOR_GREEN = GPIO_PIN_13,
	COLOR_YELLOW = GPIO_PIN_14
} Color;

typedef enum Press {
	PRESS_SHORT, PRESS_LONG
} Press;

void blink_led_once(Color);
void blink_led(Color, int times);

Press read_press();

#endif // SIMPLE_IO_H
