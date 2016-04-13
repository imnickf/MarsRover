#ifndef UTIL_H
# define UTIL_H

/// Blocks for a specified number of milliseconds
void wait_ms(unsigned int time_val);

/// Shaft encoder initialization
void shaft_encoder_init(void);

/// Shaft encoder read function
char read_shaft_encoder(void);

/// Initialize Stepper Motor
void stepper_init(void);

/// Stepper motor move function
void move_stepper_motor_by_step(int num_steps, int direction);

/// Initialize PORTC, which is used by the push buttons
void init_push_buttons(void);

/// Return the position of button being pushed
/**
 * Return the position of button being pushed.
 * @return the position of the button being pushed.  A 1 is the rightmost button.  0 indicates no button being pressed
 */
char read_push_buttons(void);

unsigned char USART_Receive( void );

void USART_init();

void USART_Transmit( unsigned char data );

int move_servo(int degree);

void timer3_init(void);

void send_pulse(void);

void pinginit(void);

int getPingDistance(void);

void ADC_init(void);

int ADC_read(void);

int getIrDistance(void);

#endif
