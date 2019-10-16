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

extern volatile uint8 seconds;
extern volatile uint8 minutes;
extern volatile uint8 hours;

Func_status TIMER_init(TIMER_cnfg_t* timerCfg);
Func_status TIMER_stop(uint8 timer);


#endif /* TIMER_H_ */
