#include "autumn_security.h"

int8_t security(uint8_t pass[], int8_t level, int8_t max_lvl, uint8_t character) {
	static uint8_t failed = 0;
	if (level < 0) {
		level = 0;
	}
	if (character == pass[level]) {
		blink_led_once(COLOR_YELLOW);
		level++;
		if (level == max_lvl) {
			light_led(COLOR_GREEN, 500);
			return 0;
		}
	} else {
		failed++;
		if (failed == 3) {
			failed = 0;
			blink_led(COLOR_RED, 10);
			level = -2;
		} else {
			blink_led_once(COLOR_RED);
			level = -1;
		}
	}
	return level;
}
