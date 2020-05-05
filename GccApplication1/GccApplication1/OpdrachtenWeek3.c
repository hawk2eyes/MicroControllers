/*
 * OpdrachtenWeek3.c
 *
 * Created: 13/02/2020 11:02:57
 *  Author: jelmer
 */ 

#define F_CPU 16e6

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/interrupt.h>

#include "OpdrachtenHeader.h"
#include "lcd.h"

int tenthValue = 1;
char buffer[100];

//ISR( TIMER2_OVF_vect )
//{
	//TCNT2 = -10; // Preset value
	//tenthValue++; // Increment counter
    //itoa(tenthValue, buffer, 10);
	//clear_screen();
	//char text[] = "value:";
	//strncat(text, buffer, 3);
	//display_text(text);
	//
//}//
//
//void week3_opdrachtB1()
//{
	//init();
	//clear_screen();
	//display_text("value:1");
	//DDRD &= ~(1<<7); // set PORTD.7 for input
	//DDRA = 0xFF; // set PORTA for output (shows countregister)
	//DDRB = 0xFF; // set PORTB for output (shows tenthvalue)//
	//TCNT2 = -10; // Preset value of counter 2
	//TIMSK |= 1<<6; // T2 overflow interrupt enable
	//TCCR2 = 0x07; // Initialize T2: ext.counting, rising edge, run
	//sei(); // turn_on intr all
	//
	//while (1)
	//{
		//PORTA = TCNT2; // show value counter 2
		//PORTB = tenthValue; // show value tenth counter
		//wait(10); // every 10 ms
	//}
//}


void week3_opdrachtB2()
{
	
	DDRB = 0xFF;
	
	 cli(); // Disable interrupts

	 // SETUP CLOCK AT FREQUENCY OF 1 HZ
	 TCCR1A = 0;// set entire TCCR1A register to 0
	 TCCR1B = 0;// same for TCCR1B
	 TCNT1  = 0;//initialize counter value to 0
	 // set compare match register for 1hz increments
	 OCR1A = 15624;// = (16*10^6) / (1*1024) - 1 (must be <65536)
	 // turn on CTC mode
	 TCCR1B |= (1 << WGM12);
	 // Set CS12 and CS10 bits for 1024 prescaler  (pg 130)
	 TCCR1B |= (1 << CS12) | (1 << CS10);
	 // enable timer compare interrupt
	 TIMSK |= (1 << TOIE1);
	

	 sei();//allow interrupts
	 
	 
	 while (1)
	 {
		 wait(50);
	 }
}

ISR(TIMER1_COMPA_vect){//timer1 interrupt 1Hz toggles pin 13 (LED)
	//generates pulse wave of frequency 1Hz/2 = 0.5kHz (takes two cycles for full wave- toggle high then toggle low)
	PORTB ^= (1<<7);
}

