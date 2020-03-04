/*
 * OpdrachtenWeek4.c
 *
 * Created: 04/03/2020 13:18:20
 *  Author: jelmer
 */ 

#define F_CPU 8e6

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>

#include "OpdrachtenHeader.h"

void week4_opdrachtB1(){
	DDRF = 0x00;
	DDRA = 0xFF;
	DDRB = 0xFF;
	//wipe();
	adcInit();
	
	while(1){
		PORTB = ADCL;
		PORTA = ADCH;
		wait(100);
	}
}

void adcInit( void ) {
	 ADMUX = 0b01100001;
	 ADCSRA = 0b11100110;
}