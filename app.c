/*
 * app.c
 *
 *  Created on: Jul 23, 2024
 *      Author: Redaa
 */
#include"lcd.h"
#include "ultrasonic.h"
#include"avr/io.h"
#include"util/delay.h"
int main(){
	SREG |= (1<<7);
	Ultrasonic_init();
	LCD_init();
	LCD_clearScreen();
	LCD_displayString("Distance= ");
	_delay_ms(5);
	uint16 distance=0;
	while(1){
		LCD_moveCursor(0,9);
		distance = Ultrasonic_readDistance();
		LCD_intgerToString(distance);
		_delay_ms(5);
		LCD_displayString(" cm");
		_delay_ms(5);
	}
}

