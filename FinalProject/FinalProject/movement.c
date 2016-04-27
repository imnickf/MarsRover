/**
 *  movement.c: functions to maneuver the iRobot Create
 *
 */

#include "movement.h"
#include "util.h"

void enter_lz(oi_t *sensor);

/**
 *  Moves the iRobot Create forward a specified number of centimeters
 *
 *  @param sensor a struct containing the data from all the sensors onboard the Create
 *  @param centimeters the number of centimeters to move the Create forward
 */
void move_forward(oi_t *sensor, int centimeters) 
{
	int sum = 0;
	oi_update(sensor);
	oi_set_wheels(200, 200); // move forward
	while (sum < centimeters * 10) {
/*		if(sensor->cliff_frontright_signal>650 || sensor->cliff_frontleft_signal>1050 || sensor->cliff_left_signal>650 || sensor->cliff_right_signal> 800){
			char message[]="RED DOT -> DONE!";
			for(int i=0;i<strlen(message);i++){USART_Transmit(message[i]);}
			//enter_lz(sensor);
			break;
		} */
		if (sensor->bumper_left==1){
			char message[]="bumper_left";
			for(int i=0;i<strlen(message);i++){USART_Transmit(message[i]);}
			move_backward(sensor, 10);
			break;
		}
		else if(sensor->bumper_right==1){
			char message[]="bumper_right";
			for(int i=0;i<strlen(message);i++){USART_Transmit(message[i]);}
			move_backward(sensor, 10);
			break;
		}
		else if(sensor->cliff_left==1){
			char message[]="cliff_leftCLIFF";
			for(int i=0;i<strlen(message);i++){USART_Transmit(message[i]);}
			move_backward(sensor, 10);
			break;
		}
		else if(sensor->cliff_frontleft==1){
			char message[]="cliff_frontleftCLIFF";
			for(int i=0;i<strlen(message);i++){USART_Transmit(message[i]);}
			move_backward(sensor, 10);
			break;
		}
	    else if(sensor->cliff_right==1){
			char message[]="cliff_rightCLIFF";
			for(int i=0;i<strlen(message);i++){USART_Transmit(message[i]);}
			move_backward(sensor, 10);
			break;
		}
		else if(sensor->cliff_frontright==1){
			char message[]="cliff_frontrightCLIFF";
			for(int i=0;i<strlen(message);i++){USART_Transmit(message[i]);}
			move_backward(sensor, 10);
			break;
		}
//		else if(sensor->cliff_left_signal>400 && sensor->cliff_left_signal<700){   robot 17
	else if(sensor->cliff_left_signal>700){
			char message[]="cliff_left_signal>600WALL";
			for(int i=0;i<strlen(message);i++){USART_Transmit(message[i]);}
			//move_backward(sensor, 10);
			break;
		}
//		else if(sensor->cliff_frontleft_signal>700 && sensor->cliff_frontleft_signal<950){
		else if(sensor->cliff_frontleft_signal>700){
			char message[]="cliff_frontleft_signal>600WALL";
			for(int i=0;i<strlen(message);i++){USART_Transmit(message[i]);}
			//move_backward(sensor, 10);
			break;
		}
//		else if(sensor->cliff_right_signal>360 && sensor->cliff_right_signal<800){
		else if(sensor->cliff_right_signal>700){
			char message[]="cliff_right_signal>350WALL";
			for(int i=0;i<strlen(message);i++){USART_Transmit(message[i]);}
			//move_backward(sensor, 10);
			break;
		}
//		else if(sensor->cliff_frontright_signal>300 && sensor->cliff_frontright_signal<700){
		else if(sensor->cliff_frontright_signal>700){
			char message[]="cliff_frontright_signal>350WALL";
			for(int i=0;i<strlen(message);i++){USART_Transmit(message[i]);}
			//move_backward(sensor, 10);
			break;
		}		
		
		
		oi_update(sensor);
		sum += sensor->distance;
	}
	oi_set_wheels(0, 0); // stop
}

void enter_lz(oi_t *sensor)
{
	int sum = 0;
	oi_set_wheels(200, 200);
	while (sum < 100) {
		if (sensor->bumper_left || sensor->bumper_right) {
			break;
		}
		oi_update(sensor);
		sum += sensor->distance;
	}
	oi_play_song(0);
}

/**
 *  Moves the iRobot Create backward a specified number of centimeters
 *
 *  @param sensor a struct containing the data from all the sensors onboard the Create
 *  @param centimeters the number of centimeters to move the Create backward
 */
void move_backward(oi_t *sensor, int centimeters)
{
	int sum = centimeters * 10;
	oi_set_wheels(-200, -200); // move backwards
	while (sum > 0) {
		oi_update(sensor);
		sum += sensor->distance;
	}
	oi_set_wheels(0, 0); // stop
}

/**
 *  Rotates the iRobot Create a specified number of degrees in the clockwise direction
 *
 *  @param sensor a struct containing the data from all the sensors onboard the Create
 *  @param degrees the number of degrees to rotate the Create clockwise
 */
void turn_clockwise(oi_t *sensor, int degrees)
{
	int sum = degrees;
	oi_set_wheels(-150, 150);  // start turning 
	while (sum > 0) {
		oi_update(sensor);
		sum += sensor->angle;
	}
	oi_set_wheels(0, 0);		// stop turning
}

/**
 *  Rotates the iRobot Create a specified number of degrees in the counter-clockwise direction
 *
 *  @param sensor a struct containing the data from all the sensors onboard the Create
 *  @param degrees the number of degrees to rotate the Create counter-clockwise
 */
void turn_counterClockwise(oi_t *sensor, int degrees) 
{
	int sum = 0;
	oi_set_wheels(150, -150);  // start turning
	while (sum < degrees) {
		oi_update(sensor);
		sum += sensor->angle;
	}
	oi_set_wheels(0, 0);		// stop turning
}
