/*
 * main.c
 *
 *  Created on: Oct 11, 2019
 *      Author: Randa
 */

#include "uart.h"
#include "lcd.h"


int main(void)
{
	uint8 character = 'a';
	uint8 flag = 0;
	UART_init();
	LCD_init();
	DDRB &= ~(1u << PB2);
	PORTB |= (1u << PB2);
	LCD_clearScreen();
	LCD_displayString("Sending: ");
	while(1)
	{
		if(!(PINB & (1u << PB2)))
		{
			_delay_ms(30);
			if(!(PINB & (1u << PB2)))
			{
				if(flag == 0)
				{
					flag = 1;
					UART_sendByte(character);
					LCD_goToRowColumn(0, 9);
					LCD_displayCharacter(character);
					if(character >= 97 && character < 122)
					{
						character++;
					}
					else
					{
						character = 'a';
					}
				}
			}

		}
		else
		{
			flag = 0;
		}

	}
	return 0;
}
