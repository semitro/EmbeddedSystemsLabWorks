#include "autumn_security.h"

int security(char pass[], size_t level, size_t max_lvl, char character){
	static char failed = 0;
	if(level == max_lvl){
		light_led(COLOR_GREEN, 2000);
		return 0;
	}
	if (character == pass[level]) {
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
	return level;
}
