/*
 * MC2.c
 *
 *  Created on: Oct 11, 2019
 *      Author: Randa
 */

#include "lcd.h"
#include "uart.h"


int main(void)
{
	uint8 receivedChar;
	LCD_init();
	UART_init();
	LCD_clearScreen();
	LCD_displayString("Receiving: ");


	while(1)
	{
		receivedChar = UART_receiveByte();
		LCD_goToRowColumn(0, 10);
		LCD_displayCharacter(receivedChar);
	}
	return 0;
}
