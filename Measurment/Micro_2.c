/*
 * Micro_2.c
 *
 *  Created on: Oct 15, 2019
 *      Author: Mariam Taha
 */

#include "lcd.h"
#include "uart.h"
#include "TIMER.h"

TIMER_cnfg_t Timer_confg={TIMER1,OUTCOMP,INTERRUPT_ON,Prescaler_1024,IN_CLK,NA,0X00,1000,CHANNEL_A,NA,NA,NA,NA,INITIALISED};

#define start 0x01

int main(void)
{
	uint64 distance=0;
	uint8 speed=0;
	uint8 start_flag=0;

	UART_init();
	LCD_init();

	DDRC &=~(1<<PC0);
	PORTC |=(1<<PC0);
	DDRC &=~(1<<PC1);
	PORTC |=(1<<PC1);

	LCD_clearScreen();
	LCD_displayString("Distance= ");
	LCD_goToRowColumn(0,15);
	LCD_displayCharacter('m');

	while(UART_recieveByte()!=start);
	TIMER_init(&Timer_confg);

	while(1)
	{
		speed = UART_recieveByte();

		if(!(PINC & (1<<PC0)))
		{
			_delay_ms(30);
			if(!(PINC & (1<<PC0)))
			{
				start_flag=1;
			}
		}


		if(!(PINC & (1<<PC1)))
		{
			_delay_ms(30);
			if(!(PINC & (1<<PC1)))
			{
				start_flag=0;
			}
		}


		if(start_flag==1)
		{
			distance = (speed*g_tick);
			LCD_goToRowColumn(0,9);
			LCD_intgerToString(distance);
		}

	}

	return 0;
}


