/*
 *  Created on: May 10, 2019
 *      Author: Mariam
 */

#ifndef UART_H_
#define UART_H_

#include "std_types.h"
#include "common_macros.h"
#include "micro_config.h"
#include <avr/io.h>

/* UART Driver Baud Rate */
#define USART_BAUDRATE 9600

void UART_init(void);

void UART_sendByte(const uint8 data);

uint8 UART_receiveByte(void);

void UART_sendString(const uint8 *Str);

void UART_receiveString(uint8 *Str); // Receive until #

#endif /* UART_H_ */
