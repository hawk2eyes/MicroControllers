/*
 * OpdrachtenWeek1.c
 *
 * Created: 30/01/2020 10:53:39
 *  Author: jelmer
 */ 
#define F_CPU 8e6

#include <avr/io.h>
#include <util/delay.h>

#include "OpdrachtenWeek1.h"

void wait( int ms )
{
	for (int i=0; i<ms; i++)
	{
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

void opdracht_1()
{
	wipe(); // turns all leds off
	
	DDRD = 0b11111111;
	
	while (1)
	{
		PORTD = 0xAA;			// Write 10101010b PORTD
		wait( 500 );
		PORTD = 0x55;			// Write 01010101b PORTD
		wait( 500 );
	}
}

void opdracht_2()
{
	wipe(); // turns all leds off
	
	DDRD = 0b11111111;
	PINC = 0x01;
	
	while (1)
	{
		if (PINC & 0x01)
		{
			PORTD = 0b10000000;
			wait(500);
			PORTD = 0x00;
			wait(500);
		}
		else 
		{
			PORTD = 0x00;
		}
	}
}

void opdracht_3()
{
	wipe(); // turns all leds off
	
	DDRD = 0xFF;
	
	while (1)
	{
		for (int i = 1; i < 100 ; i++)
		{
			int LedValue = 0b00000001;
			for (int i = 0; i < 8; i++)
			{
				wait(50);
				PORTD = LedValue << i;
			}
		}
	}
}

void wipe ()
{
	DDRA = 0xFF;
	DDRB = 0xFF;
	DDRC = 0xFF;
	DDRD = 0xFF;
	DDRE = 0xFF;
	DDRF = 0xFF;
	DDRG = 0xFF;
	
	PORTA = 0x00;
	PORTB = 0x00;
	PORTC = 0x00;
	PORTD = 0x00;
	PORTE = 0x00;
	PORTF = 0x00;
	PORTG = 0x00;
}