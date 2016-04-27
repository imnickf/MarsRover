/**
 *  movement.c: functions to maneuver the iRobot Create
 *
 */

#include "movement.h"
#include "util.h"

void move_forward(oi_t *sensor, int centimeters) 
{
	int sum = 0;
	oi_update(sensor);
	oi_set_wheels(200, 200); // move forward
	while (sum < centimeters * 10) {
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
	while (sum < 150) {
		if (sensor->bumper_left || sensor->bumper_right || sensor->cliff_left || sensor->cliff_right || sensor->cliff_frontleft || sensor->cliff_frontright) {
			break;
		}
		oi_update(sensor);
		sum += sensor->distance;
	}
	oi_set_wheels(0, 0); // stop
	for (int i = 0; i < 4; i++)
	{
		oi_set_leds(1,1,255,255);
		wait_ms(200);
		oi_set_leds(0,0,0,0);
		wait_ms(200);
	}
	oi_set_leds(1,1,0,0);
	oi_play_song(0);
}

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
