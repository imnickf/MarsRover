
/**
 * util.c: utility functions for the Atmega 128
 * 
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "util.h"
#include <math.h>

// Global used for interrupt driven delay functions
volatile unsigned int timer2_tick;
volatile enum {RISING,FALLING,DONE} State;
volatile unsigned long rising_time=0;
volatile unsigned long falling_time=0;
volatile int update_flag =0;

void timer2_start(char unit);
void timer2_stop();

void wait_ms(unsigned int time_val) 
{
	//Seting OC value for time requested
	OCR2=250; 				//Clock is 16 MHz. At a prescaler of 64, 250 timer ticks = 1ms.
	timer2_tick=0;
	timer2_start(0);

	//Waiting for time
	while(timer2_tick < time_val);

	timer2_stop();
}

void timer2_start(char unit) 
{
	timer2_tick=0;
	if ( unit == 0 ) { 		//unit = 0 is for slow 
        TCCR2=0b00001011;	//WGM:CTC, COM:OC2 disconnected,pre_scaler = 64
        TIMSK|=0b10000000;	//Enabling O.C. Interrupt for Timer2
	}
	if (unit == 1) { 		//unit = 1 is for fast
        TCCR2=0b00001001;	//WGM:CTC, COM:OC2 disconnected,pre_scaler = 1
        TIMSK|=0b10000000;	//Enabling O.C. Interrupt for Timer2
	}
	sei();
}

void timer2_stop() 
{
	TIMSK&=~0b10000000;		//Disabling O.C. Interrupt for Timer2
	TCCR2&=0b01111111;		//Clearing O.C. settings
}

ISR (TIMER2_COMP_vect) 
{
	timer2_tick++;
}

void USART_init()
{
	unsigned int baud = 34;
	
	UBRR0H = (unsigned char)(baud >> 8);
	UBRR0L = (unsigned char)baud;
	
	UCSR0A = 0b00000010;
	UCSR0C = 0b00001110;
	UCSR0B = 0b00011000;
}

unsigned char USART_Receive( void )
{
	/* Wait for data to be received */
	while ((UCSR0A & 0b10000000) == 0);
	/* Get and return received data from buffer */
	return UDR0;
}

void USART_Transmit( unsigned char data )
{
	/* Wait for empty transmit buffer by checking the UDRE bit */
	while ((UCSR0A & 0b00100000) == 0) {}

	/* Put data into transmit buffer; sends the data */
	UDR0 = data;
}
	
int move_servo(int degree)
{
	int conv = 20*degree+800;
	OCR3B = conv;
	return conv;
}

void timer3_init(void)
{
	TCCR3A = 0b00100011;
	TCCR3B = 0b00011010;
	OCR3A = 0b1010011111111000;
	OCR3B = 800;	
	DDRE = 0b00010000;
}

void send_pulse(void)
{
	DDRD |=0x10;
	PORTD |= 0x10;
	wait_ms(1);
	PORTD &=0xEF;
	DDRD &=0xEF;
}

ISR(TIMER1_CAPT_vect)
{
	if(State==RISING){
		rising_time=ICR1;
		State = FALLING;
		TCCR1B &= 0b10111111;
	}
	else if(State==FALLING){
		falling_time=ICR1;
		State = DONE;
		TCCR1B |= 0b01000000;
	}
}

void pinginit(void)
{
	TIFR = 0b00000000;
	TCCR1B = 0b11000011;
}

int getPingDistance(void)
{
	int ping =0;
	int centimeters=0;
	
	int milliseconds = 0;
	//for (int i=0;i<5;i++){
	State=RISING;
	TIMSK &= 0b11011111;
	send_pulse();
	TIFR |= 0b00100000;
	TIMSK |= 0b00100000;
	
	while (State != DONE){
		// lprintf("NOt Done");
		// wait_ms(1000);
	}
	
	ping = falling_time-rising_time;
	milliseconds = ping / 250;
	centimeters = ping / 14.70588;
	
	return centimeters;
}

void ADC_init(void)
{
	ADMUX=0b11000010;
	ADCSRA=0b10000111;
}

int ADC_read(void)
{
	ADCSRA |= 0b01000000;
	while(ADCSRA & 0b01000000){}
	return ADC;
}

int distance=0;
int value1=0;


int getIrDistance(void)
{
	int avgsum = 0;
	for (int i = 0; i < 5; i++) {
		avgsum += ADC_read();
	}
	value1 = avgsum / 5;
	distance = 24443*pow(value1,(-1.156));
	return distance;
}