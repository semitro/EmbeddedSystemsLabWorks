#include "simple_io.h"

#define BUTTON GPIOC, GPIO_PIN_15

#define BLINK_TIME 80

void blink_led_once(Color color) {
	HAL_GPIO_WritePin(GPIOD, color, GPIO_PIN_SET);
	HAL_Delay(BLINK_TIME);
	HAL_GPIO_WritePin(GPIOD, color, GPIO_PIN_RESET);
}

void blink_led(Color color, int times) {
	for (int i = 0; i < times; i++) {
		blink_led_once(color);
		HAL_Delay(BLINK_TIME);
	}
}
