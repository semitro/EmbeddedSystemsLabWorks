#include "uart_io.h"

extern int fUART_recieved;

uart_ret read_char(){
	uart_ret ret;
	ret.status = HAL_UART_Receive(huart1, &ret.character, 1, 1);
	fUART_recieved = 0;
	return ret;
}

uart_ret read_char_IT(){
	static char character = 0;
	while (!fUART_recieved)
		;
	fUART_recieved = 0;
	uart_ret ret;
	ret.character = character;
	ret.status = HAL_UART_Receive_IT(huart1, &character, 1);
	return ret;
}
