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

uint8 TIMER_init(TIMER_cnfg_t* timerCfg);
uint8 TIMER_stop(uint8 timer);


#endif /* TIMER_H_ */
