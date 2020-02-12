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

void week2_opdracht1()
{
	wipe();
	// Init I/O
	DDRD = 0xFF;			// PORTD(7) output, PORTD(6:0) input

	// Init LCD
	init_4bits_mode();

	// Write sample string
	lcd_write_string("Shift");
	
	int i = 1;
	// Loop forever
	while (1)
	{
		PORTD ^= (1<<7);	// Toggle PORTD.7
		move_to_right();
		wait( 1000 );
		i++;
	}

}

void week2_opdrachtb2() {
	// Init I/O
	DDRA = 0xFF;			// PORTD(7:4) output, PORTD(3:0) input
	DDRD = 0x06;


	PORTA = 0x01;
	// Init Interrupt hardware
	EICRA |= 0x2C;			// INT2 falling edge, INT1 rising edge 0b00101100
	EIMSK |= 0x06;			// Enable INT1 & INT2
	
	// Enable global interrupt system
	//SREG = 0x80;			// Of direct via SREG of via wrapper
	sei();
	
	while(1) {
		wait(1);
	}
}

ISR( INT1_vect )
{
	PORTA = (PORTA>>1);
	//PORTA = 0xFF;
}

ISR( INT2_vect )
{
	PORTA = (PORTA<<1);
	//PORTA = 0x00;
}

void ioisrMain()
{
	// Init I/O
	DDRD = 0xF0;			// PORTD(7:4) output, PORTD(3:0) input

	// Init Interrupt hardware
	EICRA |= 0x0F;			// INT1 falling edge, INT0 rising edge 0b00001111
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

