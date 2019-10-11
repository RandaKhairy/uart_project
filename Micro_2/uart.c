/*
 * uart.c
 *
 *  Created on: May 5, 2019
 *      Author: Randa
 */

#include "uart.h"


void UART_init(void)
{
	UCSRA = (1 << U2X);
	UCSRB = (1 << TXEN) | (1 << RXEN);
	UCSRC = (1 << URSEL) | (1 << UCSZ1) | (1 << UCSZ0);
	UBRRH = (BAUD_PRESCALAR >> 8);
	UBRRL = BAUD_PRESCALAR;
}

void  UART_sendByte(const uint8 data)
{
	while(!(UCSRA & (1 << UDRE)));
	UDR = data;
}

void UART_sendString(const uint8* str)
{
	uint8 i = 0;
	while(str[i] != '\0')
	{
		UART_sendByte(str[i]);
		i++;
	}
}

uint8 UART_receiveByte(void)
{
	while(!(UCSRA & (1 << RXC)));
	return UDR;
}

void UART_receiveString(uint8* str)
{
	uint8 i = 0;
	str[i] = UART_receiveByte();
	while(str[i] != '\0')
	{
		i++;
		str[i] = UART_receiveByte();
	}
	str[i] = '\0';
}
