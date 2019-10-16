/*
 * MC1.c
 *
 *  Created on: Oct 15, 2019
 *      Author: Randa
 */

#include "lcd.h"
#include "keypad.h"
#include "TIMER.h"


int main(void)
{

	DDRB |= (1u << PB0);
	DDRB &= ~((1u << PB2) | (1u << PB3));
	PORTB &= ~(1u << PB0);
	uint8 key;
	TIMER_cnfg_t timer = {TIMER1, OUTCOMP, INTERRUPT_ON, Prescaler_1024, IN_CLK, NA, 0x00, 1000, CHANNEL_A, NA, NA, NA, NA, INITIALISED};
	TIMER_init(&timer);

	LCD_init();
	LCD_clearScreen();
	LCD_displayString("Time ");

	LCD_goToRowColumn(1,0);
	LCD_displayString("Speed: ");


	//key = KeyPad_getPressedKey();
	//LCD_goToRowColumn(1,6);
	//LCD_intgerToString(key);
	//_delay_ms(500);

	while(1)
	{
		key = KeyPad_getPressedKey();
		LCD_goToRowColumn(1,7);
		LCD_intgerToString(key);
		/*
		LCD_goToRowColumn(0, 5);
		LCD_intgerToString(hours / 10);
		LCD_intgerToString(hours % 10);
		LCD_goToRowColumn(0, 7);
		LCD_displayCharacter(':');

		LCD_goToRowColumn(0, 8);
		LCD_intgerToString(minutes / 10);
		LCD_intgerToString(minutes % 10);
		LCD_goToRowColumn(0, 10);
		LCD_displayCharacter(':');

		LCD_goToRowColumn(0, 11);
		LCD_intgerToString(seconds / 10);
		LCD_intgerToString(seconds % 10);
		*/

		if(!(PINB & (1u << PB2)))
		{
			_delay_ms(30);
			if(!(PINB & (1u << PB2)))
			{
				PORTB |= (1u << PB0);
				LCD_goToRowColumn(1,7);
				LCD_intgerToString(++key);
			}
		}
		if(!(PINB & (1u << PB3)))
		{
			_delay_ms(30);
			if(!(PINB & (1u << PB3)))
			{
				key--;
			}
		}
	}
}

