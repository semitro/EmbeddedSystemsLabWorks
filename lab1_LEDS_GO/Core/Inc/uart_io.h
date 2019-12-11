/*
 * uart_io.h
 *
 *  Created on: 6 но€б. 2019 г.
 *      Author: zhenya
 */

#ifndef INC_UART_IO_H_
#define INC_UART_IO_H_

#include <stdint.h>
#include <usart.h>

typedef struct {
	uint8_t character;
	uint8_t status;
} uart_ret;

uart_ret read_char();
uart_ret read_char_IT();
char get_char_mode();
#endif /* INC_UART_IO_H_ */
