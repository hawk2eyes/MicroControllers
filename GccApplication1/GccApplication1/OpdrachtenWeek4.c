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
#include <avr/interrupt.h>

#include "OpdrachtenHeader.h"
#define BIT(x)    (1 << (x))

void week4_opdrachtB1(){
	DDRF = 0x00;
	DDRA = 0xFF;
	DDRB = 0xFF;
	wipe();
	adcInitB1();
	
	while(1){
		PORTB = ADCL;
		PORTA = ADCH;
		wait(100);
	}
}

void week4_opdrachtB2(){
	DDRF = 0x00;
	DDRA = 0xFF;

	wipe();
	adcInitB2();
	
	while(1){
		PORTA |= BIT(6);
		while ( ADCSRA & BIT(6));
		PORTA = ADCH;
		wait(500);
	}
}


void adcInitB1( void ) {
	 ADMUX = 0b01100001;
	 ADCSRA = 0b11100110;
}

void adcInitB2( void ) {
	ADMUX = 0b11100001;
	ADCSRA = 0b10000110;
}