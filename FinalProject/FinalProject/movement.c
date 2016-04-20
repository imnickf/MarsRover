#include "movement.h"
#include "util.h"

void move_forward(oi_t *sensor, int centimeters) 
{
	int sum = 0;
	oi_set_wheels(200, 200); // move forward
	while (sum < centimeters * 10) {
		if(sensor->bumper_left==1){
			char message[]="bumper_left";
			for(int i=0;i<strlen(message);i++){USART_Transmit(message[i]);}
			move_backward(sensor, 10);
			break;
		}
		if(sensor->bumper_right==1){
			char message[]="bumper_right";
			for(int i=0;i<strlen(message);i++){USART_Transmit(message[i]);}
			move_backward(sensor, 10);
			break;
		}
		if(sensor->cliff_left==1){
			char message[]="cliff_leftCLIFF";
			for(int i=0;i<strlen(message);i++){USART_Transmit(message[i]);}
			move_backward(sensor, 10);
			break;
		}
		if(sensor->cliff_frontleft==1){
			char message[]="cliff_frontleftCLIFF";
			for(int i=0;i<strlen(message);i++){USART_Transmit(message[i]);}
			move_backward(sensor, 10);
			break;
		}
		if(sensor->cliff_right==1){
			char message[]="cliff_rightCLIFF";
			for(int i=0;i<strlen(message);i++){USART_Transmit(message[i]);}
			move_backward(sensor, 10);
			break;
		}
		if(sensor->cliff_frontright==1){
			char message[]="cliff_frontrightCLIFF";
			for(int i=0;i<strlen(message);i++){USART_Transmit(message[i]);}
			move_backward(sensor, 10);
			break;
		}
		if(sensor->cliff_left_signal>600){
			char message[]="cliff_left_signal>600WALL";
			for(int i=0;i<strlen(message);i++){USART_Transmit(message[i]);}
			move_backward(sensor, 10);
			break;
		}
		if(sensor->cliff_frontleft_signal>600){
			char message[]="cliff_frontleft_signal>600WALL";
			for(int i=0;i<strlen(message);i++){USART_Transmit(message[i]);}
			move_backward(sensor, 10);
			break;
		}
		if(sensor->cliff_right_signal>350){
			char message[]="cliff_right_signal>350WALL";
			for(int i=0;i<strlen(message);i++){USART_Transmit(message[i]);}
			move_backward(sensor, 10);
			break;
		}
		if(sensor->cliff_frontright_signal>350){
			char message[]="cliff_frontright_signal>350WALL";
			for(int i=0;i<strlen(message);i++){USART_Transmit(message[i]);}
			move_backward(sensor, 10);
			break;
		}		
		
		
		oi_update(sensor);
		sum += sensor->distance;
	}
	oi_set_wheels(0, 0); // stop
}

void move_2meters(oi_t *sensor)
{
	int sum = 0;
	oi_set_wheels(200, 200);
	while (sum < 2000) {
		if (sensor->bumper_left || sensor->bumper_right) {
			move_backward(sensor, 15);
			turn_clockwise(sensor, 87);
			move_forward(sensor, 25);
			turn_counterClockwise(sensor, 87);
			move_forward(sensor, (2000 - sum) / 10);
			break;
		}
		oi_update(sensor);
		sum += sensor->distance;
	}
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
