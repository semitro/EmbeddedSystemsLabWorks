/*
 * uart_io.h
 *
 *  Created on: 6 но€б. 2019 г.
 *      Author: zhenya
 */

#ifndef INC_UART_IO_H_
#define INC_UART_IO_H_

typedef struct {
	char character;
	char status;
} uart_ret;

uart_ret read_char();

#endif /* INC_UART_IO_H_ */
