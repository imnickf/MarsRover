#include "movement.h"

void move_forward(oi_t *sensor, int centimeters) 
{
	int sum = 0;
	oi_set_wheels(200, 200); // move forward
	while (sum < centimeters * 10) {
		if (sensor->bumper_left || sensor->bumper_right) {
			move_backward(sensor, 15);
			turn_clockwise(sensor, 87);
			move_forward(sensor, 25);
			turn_counterClockwise(sensor, 87);
			move_forward(sensor, (centimeters - (sum / 10)));
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
