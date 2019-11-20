#include "uart_io.h"

extern int fUART_recieved;
extern char inputMode

uart_ret read_char(){
	uart_ret ret;
	ret.status = HAL_UART_Receive(&huart1, &ret.character, 1, 1);
	fUART_recieved = 0;
	return ret;
}

uart_ret read_char_IT(){
	static char character = 0;
	uart_ret ret;
	while (!fUART_recieved&&inputMode)
		;
	if(inputMode==0){
		ret.character = 255;
		ret.status = 255;
		return ret;
	}
	fUART_recieved = 0;
	ret.character = character;
	ret.status = HAL_UART_Receive_IT(&huart1, &character, 1);
	return ret;
}
