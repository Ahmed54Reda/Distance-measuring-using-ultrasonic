/*
 * ultrasonic.c
 *
 *  Created on: Jul 23, 2024
 *      Author: Redaa
 */

#include "ultrasonic.h"
#include "gpio.h"
#include<avr/io.h>
#include "util/delay.h"


uint8 g_edgeCount = 0;
uint16 g_timeHigh = 0;



void Ultrasonic_init(void){
	GPIO_setupPinDirection(TRIGGER_PORT_ID,TRIGGER_PIN_ID,PIN_OUTPUT);
//	GPIO_setupPinDirection(ECHO_PORT_ID,ECHO_PIN_ID,PIN_INPUT);
	ICU_ConfigType ICU_Configurations = {F_CPU_8,RAISING};
	ICU_setCallBack(Ultrasonic_edgeProcessing);
	ICU_init(&ICU_Configurations);

}

void Ultrasonic_Trigger(void){

	GPIO_writePin(TRIGGER_PORT_ID,TRIGGER_PIN_ID,LOGIC_HIGH);
	_delay_us(10);
	GPIO_writePin(TRIGGER_PORT_ID,TRIGGER_PIN_ID,LOGIC_LOW);

}


uint16 Ultrasonic_readDistance(void){
	uint16 distancee = 0;
	Ultrasonic_Trigger();
	if(g_edgeCount==2){
//	ICU_deInit(); /* Disable ICU Driver */
	g_edgeCount = 0;
	 distancee= (float)(g_timeHigh/58.8);
	}
	return distancee;

}



void Ultrasonic_edgeProcessing(void){

	g_edgeCount++;
	if(g_edgeCount == 1)
	{
		/*
		 * Clear the timer counter register to start measurements from the
		 * first detected rising edge
		 */
		ICU_clearTimerValue();
		/* Detect falling edge */
		ICU_setEdgeDetectionType(FALLING);
	}
	else if(g_edgeCount == 2)
	{
		/* Store the High time value */
		g_timeHigh = ICU_getInputCaptureValue();
		/* Clear the timer counter register to start measurements again */
		ICU_clearTimerValue();
		/* Detect rising edge */
		ICU_setEdgeDetectionType(RAISING);
	}
	}

