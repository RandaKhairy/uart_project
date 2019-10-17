/*
 * TIMER.h
 *
 *  Created on: Oct 14, 2019
 *      Author: Randa
 */

#ifndef TIMER_H_
#define TIMER_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include "TIMER_config.h"

#define F_CPU 1000000UL

#define NUMBER_OF_OVERFLOWS_PER_HALF_SECOND 2

typedef enum {NOK, OK} Func_status;

Func_status TIMER_init(TIMER_cnfg_t* timerCfg);
Func_status TIMER_stop(uint8 timer);

extern volatile uint32 g_tick;


#endif /* TIMER_H_ */
