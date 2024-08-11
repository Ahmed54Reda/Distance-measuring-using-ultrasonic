/*
 * ultrasonic.h
 *
 *  Created on: Jul 23, 2024
 *      Author: Redaa
 */

#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

#include "icu.h"

#define TRIGGER_PORT_ID PORTB_ID
#define ECHO_PORT_ID PORTD_ID
#define TRIGGER_PIN_ID PIN5_ID
#define ECHO_PIN_ID PIN6_ID

void Ultrasonic_init(void);


void Ultrasonic_Trigger(void);


uint16 Ultrasonic_readDistance(void);


void Ultrasonic_edgeProcessing(void);


#endif /* ULTRASONIC_H_ */
