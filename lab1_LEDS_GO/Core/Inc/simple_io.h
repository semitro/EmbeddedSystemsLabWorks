#ifndef SIMPLE_IO_H
#define SIMPLE_IO_H

#include "stm32f4xx_hal.h"

typedef enum Color {
	RED = GPIO_PIN_15,
	GREEN = GPIO_PIN_13,
	YELLOW = GPIO_PIN_14
} Color;

typedef enum Press {
	SHORT, LONG
} Press;

void blink_led_once(Color);
void blink_led(Color, int times);

Press read_press();

#endif // SIMPLE_IO_H
