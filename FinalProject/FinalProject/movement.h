#ifndef MOVEMENT_H
# define MOVEMENT_H

# include "open_interface.h"

void move_forward(oi_t *sensor, int centimeters);

void move_backward(oi_t *sensor, int centimeters);

void move_2meters(oi_t *sensor);

void turn_clockwise(oi_t *sensor, int degrees);

void turn_counterClockwise(oi_t *sensor, int degrees);

#endif
