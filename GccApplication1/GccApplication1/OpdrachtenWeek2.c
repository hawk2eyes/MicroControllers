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

void display(int number);

typedef struct {
	unsigned char data;
	unsigned int delay ;
} PATTERN_STRUCT;

PATTERN_STRUCT pattern2[] = 
{
	{0x80, 150}, {0x00, 150},
	{0x80, 150}, {0x00, 150},
	{0x01, 150}, {0x02, 150}, {0x40, 150}, {0x20, 150},
	{0x01, 150}, {0x02, 150}, {0x40, 150}, {0x20, 150},
	{0x00, 150},
	{0x01, 150}, {0x03, 150}, {0x43, 150}, {0x63, 150},
	{0x01, 150}, {0x03, 150}, {0x43, 150}, {0x63, 150},
	{0x00, 150},
	{0xFF, 0}
};

ISR( INT0_vect )
{
    PORTD |= (1<<5);		
}

ISR( INT1_vect )
{
    PORTD &= ~(1<<5);		
}

const unsigned char
Numbers [10] =
{
	0b00111111, // 0
	0b00000110, // 1
	0b01011011, // 2
	0b01001111, // 3
	0b01100110, // 4
	0b01101101, // 5
	0b01111101, // 6
	0b00000111, // 7
	0b01111111, // 8
	0b01101111, // 9
};

void week2_opdracht_1()
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
void week2_opdracht_B3()
{
	for (int i = 0; i < 10; ++i)
	{
		wait(1000);
		display(i);
	}
}

void week2_opdracht_B4()
{
	DDRD = 0b11111111;
	
	while (1==1)
	{

		int index = 0;

		while( pattern2[index].delay != 0 )
		{
			PORTD = pattern2[index].data;
			wait(pattern2[index].delay);
			index++;
		}
	}
}

void display(int number)
{
	DDRB = 0xFF;
	PORTB = Numbers[number];
}


