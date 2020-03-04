/*
 * OpdrachtenWeek3.c
 *
 * Created: 13/02/2020 11:02:57
 *  Author: jelmer
 */ 

#define F_CPU 8e6

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/interrupt.h>

#include "OpdrachtenHeader.h"
#include "lcd.h"

int tenthValue = 1;
char buffer[100];

ISR( TIMER2_OVF_vect )
{
	TCNT2 = -10; // Preset value
	tenthValue++; // Increment counter
    itoa(tenthValue, buffer, 10);
	clear_screen();
	char text[] = "value:";
	strncat(text, buffer, 3);
	display_text(text);
	
}

void week3_opdrachtB1()
{
	init();
	clear_screen();
	display_text("value:1");
	DDRD &= ~(1<<7); // set PORTD.7 for input
	DDRA = 0xFF; // set PORTA for output (shows countregister)
	DDRB = 0xFF; // set PORTB for output (shows tenthvalue)
	TCNT2 = -10; // Preset value of counter 2
	TIMSK |= 1<<6; // T2 overflow interrupt enable
	TCCR2 = 0x07; // Initialize T2: ext.counting, rising edge, run
	sei(); // turn_on intr all
	
	while (1)
	{
		PORTA = TCNT2; // show value counter 2
		PORTB = tenthValue; // show value tenth counter
		wait(10); // every 10 ms
	}
}
