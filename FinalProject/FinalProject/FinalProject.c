/*
 * FinalProject.c
 *
 * Created: 4/6/2016 12:42:28 PM
 *  Author: jlt94
 *
 *	Robot #17
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
	int distance;
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
	
// 	unsigned char notes[12]    = {62, 67, 69, 72, 71, 69, 67, 67, 62, 67, 69, 69};
// 	unsigned char duration[12] = {64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 256};
	
//	unsigned char notes[26]  = {72, 67, 69, 67,  0, 72, 67, 69, 67,  0, 72, 72, 72, 72,  0, 72, 72, 72, 72,  0, 72, 71, 72, 71, 72};
//	unsigned char duration[26]={64, 16, 16, 16, 40, 64, 16, 16, 16, 40, 8,   8, 16, 16, 16, 8,   8, 16, 16, 16, 20, 20, 32, 20, 96};
 		
//	oi_load_song(0, 26, notes, duration);
//	oi_play_song(0);
	
	while(1)
    {
		getCommand(sensor_data);
		//TODO:: Please write your application code 
    }
}

/**
*  Gets and parses the command from the GUI to control the iRobot Create
*
*  @param sensor_data struct containing all the sensor data for the Create
*/
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
				transmitSensorData(sensor_data);
				commandRecieved = 1;
				break;
			case 'm':			// Move iRobot
				for (int i = 0; i < 2; i++) {
					distanceString[i] = USART_Receive();
				}
				int distance = atoi(distanceString);
				lprintf("Distance: %d", distance);
				move_forward(sensor_data, distance);
				transmitSensorData(sensor_data);
				commandRecieved = 1;
				break;
			case 's':			// Scan for objects
				foundObjects = scanForObjects();
				transmitSensorData(sensor_data);
				commandRecieved = 1;
				free(foundObjects);
				break;
			default:
				command = USART_Receive();
		}	
	}
}

/**
 *  Transmits the values of the bump sensors, cliff sensors, and cliff signals to the GUI
 *
 *  @param sensor_data struct containing all the sensor data for the Create
 */
void transmitSensorData(oi_t *sensor_data)
{
	char bumpSensors[50], cliffSensors[100], cliffSignals[100];
	sprintf(bumpSensors, "\r\nBump Sensor (r, l) values: R: %d, L: %d\r\n", sensor_data->bumper_right, sensor_data->bumper_left);
	sprintf(cliffSensors, "Cliff Sensor (l, fl, fr, r) values: L: %d, FL: %d, FR: %d, R: %d\r\n", sensor_data->cliff_left, sensor_data->cliff_frontleft, sensor_data->cliff_frontright, sensor_data->cliff_right);
	sprintf(cliffSignals, "Cliff Sensor (l, fl, fr, r) values: L: %d, FL: %d, FR: %d, R: %d\r\n\r\n", sensor_data->cliff_left_signal, sensor_data->cliff_frontleft_signal, sensor_data->cliff_frontright_signal, sensor_data->cliff_right_signal);
	
	for(int i = 0; i < strlen(bumpSensors); i++) {
		USART_Transmit(bumpSensors[i]);
	}
	
	for(int i = 0; i < strlen(cliffSensors); i++) {	
		USART_Transmit(cliffSensors[i]); 
	}
	
	for(int i = 0; i < strlen(cliffSignals); i++) {	
		USART_Transmit(cliffSignals[i]);
	}
}

/**
 *  Uses the Ping and IR sensors to scan for objects in the path of the Create and then returns
 *  the found objects. Each object contains a diameter, distance from the Create, and an angle.
 *
 *  @return the found objects
 */
object_t * scanForObjects()
{
	int sonarDistance =0;
	int irDistance = 0;
	int currObjectIndex = -1;
	int inObject = 0;
	int lastIRDistance = 0;
	int firstDegrees = 0;
	int degreeWidth = 0;
	int lastSonarDistance = 0;
	int degrees = 0;
	
	object_t *objects = malloc(sizeof(object_t) * 10);

	while(degrees <= 180)
    {	
		move_servo(degrees);
		wait_ms(800);									//  Allows time for servo to move back to the 0 position
		while (degrees <= 180) {
			
			move_servo(degrees);
			sonarDistance = getPingDistance();
			irDistance = getIrDistance();			
							
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
				objects[currObjectIndex].distance = lastSonarDistance;					
				inObject = 0;											//Sensor is no longer on an object
			}	
		
			degrees += 2;
			wait_ms(200);
		}
    }
	
	for (int i = 0; i < currObjectIndex; i++) {
		char output[70];
		sprintf(output, "Distance: %-3d cm Diameter: %-2d cm Angle: %-3d degrees\r\n", objects[i].distance, objects[i].diameter, objects[i].location);
		
		for(int i = 0; i < strlen(output); i++){		//  Transmit object data
			USART_Transmit(output[i]);
		}
	}
	return objects;
}

