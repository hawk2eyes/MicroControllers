/*
 * OpdrachtenWeek2.c
 *
 * Created: 5-2-2020 10:48:41
 *  Author: thijz
 */ 
#define F_CPU 8e6

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/interrupt.h>

#include "OpdrachtenHeader.h"



/******************************************************************/


/******************************************************************/
ISR( INT0_vect )
{
    PORTD |= (1<<5);		
}

/******************************************************************/
ISR( INT1_vect )
{
    PORTD &= ~(1<<5);		
}

/******************************************************************/
void week2_opdracht1()
{
	// Init I/O
	DDRD = 0xF0;			// PORTD(7:4) output, PORTD(3:0) input	

	// Init Interrupt hardware
	EICRA |= 0x0B;			// INT1 falling edge, INT0 rising edge
	EIMSK |= 0x03;			// Enable INT1 & INT0
	
	// Enable global interrupt system
	//SREG = 0x80;			// Of direct via SREG of via wrapper
	sei();				

	while (1)
	{
		PORTD ^= (1<<7);	// Toggle PORTD.7
		wait( 500 );								
	}
}

