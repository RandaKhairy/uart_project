/*
 * uart.h
 *
 *  Created on: May 5, 2019
 *      Author: Randa
 */

#ifndef UART_H_
#define UART_H_

#include "std_types.h"
#include "common_macros.h"
#include "micro_config.h"

#define UART_BAUDRATE 9600
#define BAUD_PRESCALAR ((F_CPU / (8 * UART_BAUDRATE)) - 1)

void UART_init(void);
void UART_sendByte(const uint8 data);
void UART_sendString(const uint8* str);
uint8 UART_receiveByte(void);
void UART_receiveString(uint8* str);



#endif /* UART_H_ */
