/*
 * OpdrachtenWeek1.c
 *
 * Created: 30/01/2020 10:53:39
 *  Author: jelmer
 */ 
#define F_CPU 8e6

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>

#include "OpdrachtenHeader.h"

typedef struct {
	unsigned char data;
	unsigned int delay;
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

/* function prototypes for states */
void s1(void);
void s2(void);
void s3(void);
void end(void);
void start(void);

/* Define fsm (states,events) */
typedef enum { A7, A6, A5 } ENUM_EVENTS;
typedef enum { START, STATE_1, STATE_2, STATE_3, END } ENUM_STATES;
	

/* Define fsm transition */
typedef struct {
	void (*finit)(void);
	void (*fbody)(void);
	void (*fexit)(void);
	ENUM_STATES nextState;
} STATE_TRANSITION_STRUCT;

// Sample fsm definition:
//
// 		| EV_A7    EV_A6		EV_A5
// ---------------------------------
// START| START     S1          S2
// S1   | START     S1        	S2
// S2   | START     S1          S3
// S3   | START     END         END
// END  | START     END         END

STATE_TRANSITION_STRUCT fsm[5][3] = {
	{ {s1,   NULL,  NULL, START}, 	{NULL, s1, NULL, STATE_1},		{NULL, s2, NULL, STATE_2} },
	{ {NULL, start, NULL, START},	{NULL, NULL, NULL, STATE_1},	{NULL, s2, NULL, STATE_2} },
	{ {NULL, start, NULL, START}, 	{NULL, s1, NULL, STATE_1}, 		{NULL, s3, NULL, STATE_3} },
	{ {NULL, NULL,  NULL, START},	{NULL, end, NULL, END}, 		{NULL, end, NULL, END} },
	{ {NULL, start, NULL, START},	{NULL, end, NULL, END}, 		{NULL, end, NULL, END} }
};
	
// State holder
ENUM_STATES state = START;
	
void handleEvent(ENUM_EVENTS event)
{
	// Call EXIT function old state
	if( fsm[state][event].fexit != NULL) {
		fsm[state][event].fexit() ;
	}
	
	// Set new state, -1 means 
	state = fsm[state][event].nextState;

	// Call INIT function
	if( fsm[state][event].finit != NULL) {
		fsm[state][event].finit() ;
	}

	// Call BODY function
	if( fsm[state][event].fbody != NULL) {
		fsm[state][event].fbody() ;
	}
}

//
// State S1
//
void s1(void){
	printf("s1\n");
	
	DDRA = 0xFF;
	DDRB = 0xFF;
	DDRC = 0xFF;
	DDRD = 0xFF;
	DDRE = 0xFF;
	DDRF = 0xFF;
	DDRG = 0xFF;
	
	PORTA = 0xFF;
	PORTB = 0xFF;
	PORTC = 0xFF;
	PORTD = 0xFF;
	PORTE = 0xFF;
	PORTF = 0xFF;
	PORTG = 0xFF;
	
	wait(5000);
}

//
// State S2
//
void s2(void){
	printf("s2\n");
	DDRA = 0xFF;
	DDRB = 0xFF;
	DDRC = 0xFF;
	DDRD = 0xFF;
	DDRE = 0xFF;
	DDRF = 0xFF;
	DDRG = 0xFF;
	
	for (int i = 0; i < 2500; i++)
	{
		PORTA = 0x00;
		PORTB = 0x00;
		PORTC = 0x00;
		PORTD = 0x00;
		PORTE = 0x00;
		PORTF = 0x00;
		PORTG = 0x00;
		wait(1);
		PORTA = 0xFF;
		PORTB = 0xFF;
		PORTC = 0xFF;
		PORTD = 0xFF;
		PORTE = 0xFF;
		PORTF = 0xFF;
		PORTG = 0xFF;
		wait(1);
	}
}

//
// State S3
//
void s3(void){
	printf("s3\n");
	
	DDRA = 0xFF;
	DDRB = 0xFF;
	DDRC = 0xFF;
	DDRD = 0xFF;
	DDRE = 0xFF;
	DDRF = 0xFF;
	DDRG = 0xFF;
	
	for (int i = 0; i < 5; i++)
	{
		int index = 0;
		while (pattern[index].delay != 0) {
			PORTA = pattern[index].data;
			PORTB = pattern[index].data;
			PORTC = pattern[index].data;
			PORTD = pattern[index].data;
			PORTE = pattern[index].data;
			PORTF = pattern[index].data;
			PORTG = pattern[index].data;
			wait(pattern[index].delay);
			index++;
		}
	}
	
}

//
// State Start
//
void start(void){
	printf("start\n");
}

//
// State Stop
//
void end(void){
	printf("end\n");
}


void wait( int ms )
{
	for (int i=0; i<ms; i++)
	{
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

void week1_opdracht_1()
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

void week1_opdracht_2()
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

void week1_opdracht_3()
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

void week1_opdracht_4()
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

void week1_opdracht_5()
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
				wait(1);
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
			wait(1);
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

void week1_opdracht_6(){
	
	wipe();
	
	while (1)
	{
		if (PINA & 0x80)
		{
			handleEvent(A7);
		}
		
		if (PINA & 0x40)
		{
			handleEvent(A6);
		}
		
		if (PINA & 0x20)
		{
			handleEvent(A5);
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