#include "simple_io.h"

#define BUTTON GPIOC, GPIO_PIN_15

#define BLINK_TIME 80

void blink_led_once(Color color) {
	light_led(color, BLINK_TIME);
}

void blink_led(Color color, int times) {
	for (int i = 0; i < times; i++) {
		blink_led_once(color);
		HAL_Delay(BLINK_TIME);
	}
}

void light_led(Color color, int time) {
	HAL_GPIO_WritePin(GPIOD, color, GPIO_PIN_SET);
	HAL_Delay(time);
	HAL_GPIO_WritePin(GPIOD, color, GPIO_PIN_RESET);
}

Press read_press() {
	while(HAL_GPIO_ReadPin(BUTTON) == GPIO_PIN_SET)
		;
	unsigned int counter = 0;
	while(HAL_GPIO_ReadPin(BUTTON) == GPIO_PIN_RESET) {
		counter++;
	}
	if (counter > 300000) {
		return PRESS_LONG;
	}
	return PRESS_SHORT;
}
