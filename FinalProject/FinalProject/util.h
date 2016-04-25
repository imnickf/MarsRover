#ifndef UTIL_H
# define UTIL_H

/// Blocks for a specified number of milliseconds
void wait_ms(unsigned int time_val);

/**
 *  Waits until USART has recieved a character and then returns that character
 *
 *  @return the recieved character 
 */
unsigned char USART_Receive(void);

/// Initalize USART registers
void USART_init();

/**
 *  Waits until USART has finished trasmitting and is ready to trasmit again,
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

/// Initalize Timer 3 registers
void timer3_init(void);

/// Send pulse on wire to control Ping sensor
void send_pulse(void);

/// Initalize Ping sonar sensor
void pinginit(void);

/**
 *  Returns the distance of an object based on the Ping sensor reading
 *
 *  @return distance in centimeters of detected object
 */
int getPingDistance(void);

/// Initalize Analog-Digital Conversion registers
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
