/*
 * FinalProject.c
 *
 * Created: 4/6/2016 12:42:28 PM
 *  Author: jlt94
 */ 


#include <avr/interrupt.h>
#include <avr/io.h>
#include "util.h"
#include <stdio.h>
#include <string.h>
#include "lcd.h"
#include <math.h>
#include <stdlib.h>
#include "open_interface.h"
#include "movement.h"

typedef struct object {
	int diameter;
	int location;
} object_t;

void getCommand(oi_t *sensor_data);
object_t * scanForObjects();

unsigned long time_diff;

int main(void)
{
    lcd_init();
    ADC_init();
    pinginit();
    timer3_init();
	USART_init();
	
	oi_t *sensor_data = oi_alloc();
	oi_init(sensor_data);
	
	while(1)
    {
		getCommand(sensor_data);
		//TODO:: Please write your application code 
    }
}

void getCommand(oi_t *sensor_data)
{
	unsigned char command = USART_Receive();
	unsigned char commandRecieved = 0;
	char angleString[4];
	char distanceString[3];
	object_t *foundObjects;
		
	while (!commandRecieved) {
		switch (command) {
			case 'r':			// Rotate iRobot
				for (int i = 0; i < 3; i++) {
					angleString[i] = USART_Receive();
				}
				int degrees = atoi(angleString);
				lprintf("Degrees: %d", degrees);
				turn_clockwise(sensor_data, degrees);
				commandRecieved = 1;
				break;
			case 'm':			// Move iRobot
				for (int i = 0; i < 2; i++) {
					distanceString[i] = USART_Receive();
				}
				int distance = atoi(distanceString);
				lprintf("Distance: %d", distance);
				move_forward(sensor_data, distance);
				commandRecieved = 1;
				break;
			case 's':			// Scan for objects
				foundObjects = scanForObjects();
				commandRecieved = 1;
				free(foundObjects);
				break;
			default:
				command = USART_Receive();
		}	
	}
}

object_t * scanForObjects()
{
	int sonarDistance =0;
	int irDistance = 0;
	/*
	char heading[]="\r\nDegrees\t     IRDistance\tSonarDistance";   //   \r\n for new line, \t and spaces to line up text and numbers on output
	char output[50];
	*/
	int currObjectIndex = -1;
	//int currDiam = 0;
	//int smallestObjectIndex = 0;
	//int smallestDiam = 0;
	//int smallestLocation = 0;
	int inObject = 0;
	int lastIRDistance = 0;
	int firstDegrees = 0;
	int degreeWidth = 0;
	int lastSonarDistance = 0;
	int degrees = 0;
	
	object_t *objects = malloc(sizeof(object_t) * 10);

	while(degrees <= 180)
    {
		/*
		for(int i = 0; i < strlen(heading); i++) {     //  Put this inside loop so it would reprint for each iteration
			USART_Transmit(heading[i]);
		}
		*/
		
		move_servo(degrees);
		wait_ms(800);									//  Allows time for servo to move back to the 0 position
		while (degrees <= 180) {
			
			move_servo(degrees);
			sonarDistance = getPingDistance();
			irDistance = getIrDistance();			
			
			/*
			sprintf(output,"\r\n%d\t\t%d\t\t%d", degrees, irDistance, sonarDistance);  //  \r\n is new line characters. \t is used to line up numbers 
					
			for(int i = 0; i < strlen(output); i++){		//  Print output data
				USART_Transmit(output[i]);				
			}											
			*/
							
			if(irDistance <= 100 && inObject == 0){			// Going into object
				inObject = 1;								// Sensor is now detecting an object
				currObjectIndex++;							// Index of this object
				lastIRDistance = irDistance;
				firstDegrees = degrees;
				lastSonarDistance = sonarDistance;	
			}
			
			if(irDistance > 100 && inObject == 1){			// Going out of object	
				degreeWidth = abs(firstDegrees - degrees);	
				objects[currObjectIndex].location = (firstDegrees + degrees) / 2;
				objects[currObjectIndex].diameter = (sqrt(2*pow(lastSonarDistance,2) - 2*pow(lastSonarDistance,2) * cos(degreeWidth)) / 5.5);   //Actual diameter calculation						
				inObject = 0;											//Sensor is no longer on an object
			}	
		
			degrees += 2;
			wait_ms(200);
		}
    }
	
	for (int i = 0; i < currObjectIndex; i++) {
		char output[30];
		sprintf(output, "Diameter: %2d Angle: %3d\r\n", objects[i].diameter, objects[i].location);
		
		for(int i = 0; i < strlen(output); i++){		//  Transmit object data
			USART_Transmit(output[i]);
		}
	}
	return objects;
}