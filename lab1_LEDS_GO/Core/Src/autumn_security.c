#include "autumn_security.h"

void security(Password* pass){
	size_t level = 0;
	size_t failed = 0;
	while (level != pass->len){
		if (read_press() == pass->pass[level]) {
			blink_led_once(COLOR_YELLOW);
			level++;
		}
		else {
			failed++;
			level = 0;
			if (failed == 3) {
				failed = 0;
				blink_led(COLOR_RED, 10);
			}
			else {
				blink_led_once(COLOR_RED);
			}
		}
	}
	light_led(COLOR_GREEN, 2000);
}
