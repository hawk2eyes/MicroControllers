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
		clear_screen();
		lcd_write_string("Shift + " + i);
		//wait( 250 );
		_delay_ms(250);
		i++;
	}

}

