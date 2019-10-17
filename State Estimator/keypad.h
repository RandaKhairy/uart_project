/*
 *  Created on: Sep 20, 2019
 *      Author: Randa
 */

#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "std_types.h"
#include "micro_config.h"
#include "common_macros.h"


/* Keypad configurations for number of rows and columns */
#define N_col 3
#define N_row 3

/* Keypad Port Configurations */
#define KEYPAD_PORT_OUT PORTC
#define KEYPAD_PORT_IN  PINC
#define KEYPAD_PORT_DIR DDRC

/*
 * Function responsible for getting the pressed keypad key
 */
uint8 KeyPad_getPressedKey(void);

#endif /* KEYPAD_H_ */
