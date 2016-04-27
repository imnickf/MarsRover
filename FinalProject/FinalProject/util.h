#ifndef UTIL_H
# define UTIL_H

/**
 *		@file util.h
 *		@brief this header files will contain all required 
 *		definitions for basic utility functions
 *		
 *		@author Nick, Ashley, Jason, Nathan
 *
 *		@date 4/27/16
 */

/**
 *  Blocks for a specified number of milliseconds
 *
 *  @param time_val number of milliseconds to block
 */
void wait_ms(unsigned int time_val);

/**
 *  Waits until USART has received a character and then returns that character
 *
 *  @return the received character 
 */
unsigned char USART_Receive(void);


/**
 *  Initialize USART registers
 *
 *  
 */
void USART_init();

/**
 *  Waits until USART has finished transmitting and is ready to transmit again,
 *  then sends the provided character.
 *
 *  @param data the character to be transmitted
 */
void USART_Transmit( unsigned char data );

/**
 *  Rotates the servo on the iRobot Create to a specified degree
 *
 *  @param degree angle to rotate the servo to
 */
int move_servo(int degree);

/**
 *  Initialize Timer 3 registers
 *
 *  
 */
void timer3_init(void);

/**
 *  Send pulse on wire to control Ping sensor
 *
 *  
 */
void send_pulse(void);

/**
 *  Initialize Ping sonar sensor
 *
 *  
 */
void pinginit(void);

/**
 *  Returns the distance of an object based on the Ping sensor reading
 *
 *  @return distance in centimeters of detected object
 */
int getPingDistance(void);

/**
 *  Initalize Analog-Digital Conversion registers
 *
 *  
 */
void ADC_init(void);

/**
 *  Waits until current conversion has finished then converts current analog signal to digital 
 *
 *  @return digital integer value of the analog signal between 0-1023 
 */
int ADC_read(void);

/**
 *  Returns the distance of an object based on the IR sensor reaing 
 *
 *  @return distance in centimeters of detected object
 */
int getIrDistance(void);

#endif
