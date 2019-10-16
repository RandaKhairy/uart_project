/*
 * TIMER.c
 *
 *  Created on: Oct 14, 2019
 *      Author: Randa
 */
#include "TIMER.h"

volatile uint8 seconds = 0;
volatile uint8 minutes = 0;
volatile uint8 hours = 0;

//Clk set function
static Func_status TIMER_start(uint8 timer, uint8 prescaler, uint8 clock, uint8 clockEdge)
{
	Func_status retval = OK;
	switch (timer)
	{
	case TIMER0:
		if(clock == IN_CLK)
		{
			switch (prescaler)
			{
			case No_Prescaler:
				TCCR0 |= (1u << FOC0 )| (1u << CS00);
				break;
			case Prescaler_8:
				TCCR0 |= (1u << FOC0) |( 1u << CS01);
				break;
			case Prescaler_64:
				TCCR0 |= (1u << FOC0) | (1u << CS01) |( 1u << CS00);
				break;
			case Prescaler_256:
				TCCR0 |= (1u << FOC0) |( 1u << CS02);
				break;
			case Prescaler_1024:
				TCCR0 |= (1u << FOC0 )|( 1u << CS02 )|( 1u << CS00);
				break;
			default:
				retval=NOK;
			}
		}
		else if(clock == EX_CLK)
		{
			if(clockEdge == Falling_edge)
			{
				TCCR0 = (1u << FOC0) |(1u << CS02) | (1u << CS01);
			}
			else if(clockEdge == Rising_edge)
			{
				TCCR0 = (1u << FOC0) | (1u << CS02) | (1u << CS01)|( 1u << CS00);
			}
			else
			{
				retval=NOK;
			}
		}
		else
		{
			retval=NOK;
		}
	break;
	case TIMER1:
		if(clock == IN_CLK)
		{
			switch (prescaler)
			{
			case No_Prescaler:
				TCCR1B |= (1u << CS10);
				break;
			case Prescaler_8:
				TCCR1B |= ( 1u << CS11);
				break;
			case Prescaler_64:
				TCCR1B |= (1u << CS11) |( 1u << CS10);
				break;
			case Prescaler_256:
				TCCR1B |= (1u << CS12);
				break;
			case Prescaler_1024:
				TCCR1B |= (1u << CS12 )|( 1u << CS10);
				break;
			default:
				retval=NOK;
			}
		}
		else if(clock == EX_CLK)
		{
			if(clockEdge == Falling_edge)
			{
				TCCR1B = (1u << CS12) | (1u << CS11);
			}
			else if(clockEdge == Rising_edge)
			{
				TCCR1B = (1u << CS12) | (1u << CS11)|( 1u << CS10);
			}
			else
			{
				retval=NOK;
			}
		}
		else
		{
			retval=NOK;
		}
	break;
	case TIMER2:
		if(clock == IN_CLK)
		{
			switch(prescaler)
			{
			case No_Prescaler:
				TCCR2 |= (1u << FOC2) | (1u << CS20);
			break;
			case Prescaler_8:
				TCCR2 |= (1u << FOC2) | (1u << CS21);
			break;
			case Prescaler_32:
				TCCR2 |= (1u << FOC2) | (1u << CS21) | (1u << CS20);
			break;
			case Prescaler_64:
				TCCR2 |= (1u << FOC2) | (1u << CS22);
			break;
			case Prescaler_128:
				TCCR2 |= (1u << FOC2) | (1u << CS20) | (1u << CS22);
			break;
			case Prescaler_256:
				TCCR2 |= (1u << FOC2) | (1u << CS21) | (1u << CS22);
			break;
			case Prescaler_1024:
				TCCR2 |= (1u << FOC2) | (1u << CS20) | (1u << CS20) | (1u << CS22);
			break;
			default:
				retval = NOK;
			}
		}
		else
		{
			retval = NOK;
		}
	break;
	}
	return retval;
}

//Timer modes initialization function
Func_status TIMER_init(TIMER_cnfg_t* timerCfg)
{

	Func_status status = OK;
	switch(timerCfg->timer)
	{
	case TIMER0:
		TCNT0 = timerCfg->Timer_initial;
		switch(timerCfg->mode)
		{
		case OVERFLOW:
			if(timerCfg->interrupt_flag == INTERRUPT_ON)
			{
				SREG  |= (1 << 7);
				TIMSK |= (1u << TOIE0);
			}
			else if(timerCfg->interrupt_flag == NA)
			{
				TIMSK &= ~(1u << TOIE0);
			}
		break;
		case OUTCOMP:
			TCCR0 = (1u << FOC0 | 1u << WGM01);
			OCR0 = (uint8)timerCfg->Compare_reg;
			if(timerCfg->interrupt_flag == INTERRUPT_ON)
			{
				SREG  |= (1 << 7);
				TIMSK |= (1u << OCIE0);
			}
			else if(timerCfg->interrupt_flag == NA)
			{
				TIMSK &= ~(1u << OCIE0);
			}
		break;
		default:
			status = NOK;
			timerCfg->is_configured = UNINITIALISED;
		}
		TIMER_start(TIMER0, timerCfg->prescalar, timerCfg->clk_Oscillator, timerCfg->EX_clk_edge);
	break;
	case TIMER1:
		TCNT1 = timerCfg->Timer_initial;
		switch(timerCfg->mode)
		{
		case OVERFLOW:
			TCCR1A = (1u << FOC1A) | (1u << FOC1B);
			if(timerCfg->interrupt_flag == INTERRUPT_ON)
			{
				SREG  |= (1 << 7);
				TIMSK |= (1u << TOIE1);
			}
			else if(timerCfg->interrupt_flag == NA)
			{
				TIMSK &= ~(1u << TOIE1);
			}
		break;
		case OUTCOMP:
			TCCR1A = (1u << FOC1A) | (1u << FOC1B);
			if(timerCfg->Timer1_channel == CHANNEL_A)
			{
				OCR1A = timerCfg->Compare_reg;
				TCCR1B = (1 << WGM12);
				if(timerCfg->interrupt_flag == INTERRUPT_ON)
				{
					SREG  |= (1u << 7);
					TIMSK |= (1u << OCIE1A);
				}
				else if(timerCfg->interrupt_flag == NA)
				{
					TIMSK &= ~(1u << OCIE1A);
				}
			}
			else if(timerCfg->Timer1_channel == CHANNEL_B)
			{
				OCR1B = timerCfg->Compare_reg;
				if(timerCfg->interrupt_flag == INTERRUPT_ON)
				{
					SREG  |= (1u << 7);
					TIMSK |= (1u << OCIE1B);
				}
				else if(timerCfg->interrupt_flag == NA)
				{
					TIMSK &= ~(1u << OCIE1B);
				}
			}
			else
			{
				timerCfg->is_configured = UNINITIALISED;
				status = NOK;
			}

		break;
		default:
			timerCfg->is_configured = UNINITIALISED;
			status = NOK;
		}
		TIMER_start(TIMER1, timerCfg->prescalar, timerCfg->clk_Oscillator, timerCfg->EX_clk_edge);
	break;
	case TIMER2:
		TCNT2 = timerCfg->Timer_initial;
		switch(timerCfg->mode)
		{
		case OVERFLOW:
			if(timerCfg->interrupt_flag == INTERRUPT_ON)
			{
				SREG  |= (1 << 7);
				TIMSK |= (1u << TOIE2);
			}
			else if(timerCfg->interrupt_flag == NA)
			{
				TIMSK &= ~(1u << TOIE2);
			}
		break;
		case OUTCOMP:
			TCCR2 = (1u << FOC2 | 1u << WGM21);
			OCR2 = (uint8)timerCfg->Compare_reg;
			if(timerCfg->interrupt_flag == INTERRUPT_ON)
			{
				SREG  |= (1 << 7);
				TIMSK |= (1u << OCIE2);
			}
			else if(timerCfg->interrupt_flag == NA)
			{
				TIMSK &= ~(1u << OCIE2);
			}
		break;
		default:
			status = NOK;
			timerCfg->is_configured = UNINITIALISED;
		}
		TIMER_start(TIMER2, timerCfg->prescalar, timerCfg->clk_Oscillator, timerCfg->EX_clk_edge);
	break;
	default:
		timerCfg->is_configured = UNINITIALISED;
		status = NOK;
	}
	return status;
}

Func_status TIMER_stop(uint8 timer)
{
	Func_status status = OK;
	switch (timer)
	{
	case TIMER0:
		TCCR0 &= ~((1u << CS02 ) | (1u << CS01) | (1u << CS00));
	break;
	case TIMER1:
		TCCR1B &= ~((1u << CS12 ) | (1u << CS11) | (1u << CS10));
	break;
	case TIMER2:
		TCCR2 &= ~((1u << CS22 ) | (1u << CS21) | (1u << CS20));
	break;
	default:
		status = NOK;
	}
	return status;
}

ISR(TIMER1_COMPA_vect)
{
	PORTB |= (1u << PB0);
	if (seconds < 60)
	{
		seconds++;
	}
	else if (seconds == 60)
	{
		if (minutes < 60)
		{
			minutes++;
		}
		seconds=0;
	}
	if (minutes == 60)
	{
		if (hours < 24)
		{
			hours++;
		}
		minutes=0;
	}
	if (hours == 24)
	{
		hours=0;
	}
}
