/*
 * main.c
 *
 *  Created on: Oct 14, 2019
 *      Author: Randa
 */

#include "TIMER.h"

int main(void)
{
	DDRA |= (1u << PA0);
	DDRA |= (1u << PA1);
	PORTA &= ~(1u << PA0);
	TIMER_cnfg_t timer = {TIMER0, OVERFLOW, INTERRUPT_ON, Prescaler_1024, IN_CLK, NA, 0x00, NA, NA, NA, NA, NA, NA, INITIALISED};
	TIMER_init(&timer);
	while(1)
	{

	}
}
