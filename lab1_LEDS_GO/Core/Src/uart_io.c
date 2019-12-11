#include "uart_io.h"

extern uint8_t fUART_received;
extern uint8_t inputMode;

uart_ret read_char() {
	uart_ret ret;
	ret.status = HAL_UART_Receive(&huart1, &ret.character, 1, 1);
	fUART_received = 0;
	return ret;
}

uart_ret read_char_IT() {
	uint8_t character = 0;
	uart_ret ret;
	ret.status = HAL_UART_Receive_IT(&huart1, &character, 1);
	while (!fUART_received && inputMode)
		;
	if (!inputMode) {
		ret.character = 255;
		ret.status = 255;
	} else {
		fUART_received = 0;
		ret.character = character;
	}
	return ret;
}

char read_char_mode() {
	uart_ret ret;
	ret.status = HAL_BUSY;
	uint8_t inp = inputMode;
	while (ret.status != HAL_OK) {
		if (inputMode) {
			ret = read_char_IT();
			if (ret.character == 0) {
				ret = read_char_IT();
			}
		} else {
			ret = read_char();
		}
		if (ret.character == 0x1) {
			ret.character = 0x2;
		}
		if (inp != inputMode) {
			ret.character = 0x1;
			ret.status = HAL_OK;
		}
	}
	return ret.character;
}
