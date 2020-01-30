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

typedef struct {
	unsigned char data;
	unsigned int delay ;
} PATTERN_STRUCT;

PATTERN_STRUCT pattern[] = {
	{0x00, 100}, {0x01, 100}, {0x02, 100}, {0x04, 100}, {0x10, 100}, {0x20, 100}, {0x40, 100}, {0x80, 100},
	{0x00, 100},
	{0xAA,  50}, {0x55,  50},
	{0xAA,  50}, {0x55,  50},
	{0xAA,  50}, {0x55,  50},
	{0x00, 100},
	{0x81, 100}, {0x42, 100}, {0x24, 100}, {0x18, 100}, {0x0F, 200}, {0xF0, 200}, {0x0F, 200}, {0xF0, 200},
	{0x00, 0x00}
};

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

void opdracht_4()
{
	wipe(); // turns all leds off
	
	DDRA = 0xFF;
	DDRB = 0xFF;
	DDRC = 0xFF;
	DDRD = 0xFF;
	
	while (1)
	{
		int index = 0;
		while (pattern[index].delay != 0) {
			PORTA = pattern[index].data;
			PORTB = pattern[index].data;
			PORTC = pattern[index].data;
			PORTD = pattern[index].data;
			wait(pattern[index].delay);
			index++;
		}
	}
}

void opdracht_5()
{
	wipe(); // turns all leds off
	
	DDRD = 0xFF;
	PINC = 0x01;
	
	int state = 1000;
	
	while (1)
	{
		PORTD = 0b10000000;
		for (int i = 0; i < state; i++)
		{
				wait(1)
				if (PINC & 0x01)
				{
					if (state == 1000)
					{
						state = 250;
						} else {
						state = 1000;
					}
					break;
				}
		} 
		PORTD = 0x00;
		for (int i = 0; i < state; i++)
		{
			wait(1)
			if (PINC & 0x01)
			{
				if (state == 1000)
				{
					state = 250;
					} else {
					state = 1000;
				}
				break;
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