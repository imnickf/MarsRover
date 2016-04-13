
/**
 * util.c: utility functions for the Atmel platform
 *
 * For an overview of how timer based interrupts work, see
 * page 111 and 133-137 of the Atmel Mega128 User Guide
 *
 * @author Zhao Zhang & Chad Nelson
 * @date 06/26/2012
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


/// Blocks for a specified number of milliseconds
void wait_ms(unsigned int time_val) {
	//Seting OC value for time requested
	OCR2=250; 				//Clock is 16 MHz. At a prescaler of 64, 250 timer ticks = 1ms.
	timer2_tick=0;
	timer2_start(0);

	//Waiting for time
	while(timer2_tick < time_val);

	timer2_stop();
}


// Start timer2
void timer2_start(char unit) {
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


// Stop timer2
void timer2_stop() {
	TIMSK&=~0b10000000;		//Disabling O.C. Interrupt for Timer2
	TCCR2&=0b01111111;		//Clearing O.C. settings
}


// Interrupt handler (runs every 1 ms)
ISR (TIMER2_COMP_vect) {
	timer2_tick++;
}




/// Initialize PORTC to accept push buttons as input
void init_push_buttons(void) {
	DDRC &= 0xC0;  //Setting PC0-PC5 to input
	PORTC |= 0x3F; //Setting pins' pull up resistors
}

/// Return the position of button being pushed
/**
 * Return the position of button being pushed.
 * @return the position of the button being pushed.  A 1 is the rightmost button.  0 indicates no button being pressed
 */
char read_push_buttons(void)
{
	if ((PINC & 0b00100000) == 0b00000000) {
		return 6;
	}
	else if ((PINC & 0b00010000) == 0b00000000) {
		return 5;
	}
	else if ((PINC & 0b00001000) == 0b00000000) {
		return 4;
	}
	else if ((PINC & 0b00000100) == 0b00000000) {
		return 3;
	}
	else if ((PINC & 0b0000010) == 0b00000000) {
		return 2;
	}
	else if ((PINC & 0b00000001) == 0b00000000) {
		return 1;
	}

	return 0;
}




/// Initialize PORTC for input from the shaft encoder
void shaft_encoder_init(void) {
	DDRC &= 0x3F;	//Setting PC6-PC7 to input
	PORTC |= 0xC0;	//Setting pins' pull-up resistors
}

/// Read the shaft encoder
/**
 * Reads the two switches of the shaft encoder and compares the values
 * to the previous read.  This function should be called very frequently
 * for the best results.
 *
 * @return a value indicating the shaft encoder has moved:
 * 0 = no rotation (switches did not change)
 * 1 = CW rotation
 * -1 = CCW rotation
 */
char read_shaft_encoder(void) {

	return 0;
}



/// Initialize PORTE to control the stepper motor
void stepper_init(void) {
	DDRE |= 0xF0;  	//Setting PE4-PE7 to output
	PORTE &= 0x8F;  //Initial postion (0b1000) PE4-PE7
	wait_ms(2);
	PORTE &= 0x0F;  //Clear PE4-PE7
}

/// Turn the Stepper Motor
/**
 * Turn the stepper motor a given number of steps.
 *
 * @param num_steps A value between 1 and 200 steps (1.8 to 360 degrees)
 * @param direction Indication of direction: 1 for CW and -1 for CCW
 */
void  move_stepper_motor_by_step(int num_steps, int direction) {

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
    //  Wait for empty transmit buffer
    // while ( !( UCSR0A & (1<<UDRE)) )
		;
    //  Copy 9th bit to TXB8
        /*UCSR0B &= ~(1<<TXB8);
        if ( data & 0x0100 )
        UCSR0B |= (1<<TXB8);*/
		/* Wait for empty transmit buffer by checking the UDRE bit */
		while ((UCSR0A & 0b00100000) == 0) {}
		/* Put data into transmit buffer; sends the data */
		UDR0 = data;


	    //    Put data into buffeasdfr, sends the data
	  	// UDR0 = data;
}

	int move_servo(int degree){
		int conv = 20*degree+800;
		OCR3B = conv;
		return conv;
	}

	void timer3_init(void){
		TCCR3A = 0b00100011;
		TCCR3B = 0b00011010;
		OCR3A = 0b1010011111111000;
		OCR3B = 800;	//4250=180d //3500= 135d //2600=90d //1700 = 45d //0800 = 0d
		//wait_ms(2000);
		//OCR3B = 0b0000011111010000;
		DDRE = 0b00010000;
	}

	void send_pulse(void){
		DDRD |=0x10;
		PORTD |= 0x10;
		wait_ms(1);
		PORTD &=0xEF;
		DDRD &=0xEF;
	}

	//Overflow code pulled from lecture notes, overflow in print statement is a constant -1
	//ISR (TIMER1_OVF_vect) {
	//	new_overflows++;
	//}

	ISR(TIMER1_CAPT_vect){
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

void pinginit(void){
	TIFR = 0b00000000;
	TCCR1B = 0b11000011;
}

int pingdistance(void){
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

void ADC_init(void){
	ADMUX=0b11000010;
	ADCSRA=0b10000111;
}
int ADC_read(void){
	ADCSRA |= 0b01000000;
	while(ADCSRA & 0b01000000){}
	return ADC;
}
	int distance=0;

	int value1=0;
int irdistance(void){
	int avgsum = 0;
	for (int i = 0; i < 5; i++) {
		avgsum += ADC_read();
	}
	value1 = avgsum / 5;
	distance = 24443*pow(value1,(-1.156));
	return distance;
}
