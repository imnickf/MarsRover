#ifndef MOVEMENT_H
# define MOVEMENT_H

/**
 *		@file movement.h
 *		@brief this header files will contain all required 
 *		definitions for movement functions
 *		
 *		@author Nick, Ashley, Jason, Nathan
 *
 *		@date 4/27/16
 */

# include "open_interface.h"

/**
 *  Moves the iRobot Create forward a specified number of centimeters
 *
 *  @param sensor a struct containing the data from all the sensors onboard the Create
 *  @param centimeters the number of centimeters to move the Create forward
 */
void move_forward(oi_t *sensor, int centimeters);

/**
 *  Moves the iRobot Create forward into the landing zone
 *
 *  @param sensor a struct containing the data from all the sensors onboard the Create
 */
void enter_lz(oi_t *sensor);

/**
 *  Moves the iRobot Create backward a specified number of centimeters
 *
 *  @param sensor a struct containing the data from all the sensors onboard the Create
 *  @param centimeters the number of centimeters to move the Create backward
 */
void move_backward(oi_t *sensor, int centimeters);

/**
 *  Rotates the iRobot Create a specified number of degrees in the clockwise direction
 *
 *  @param sensor a struct containing the data from all the sensors onboard the Create
 *  @param degrees the number of degrees to rotate the Create clockwise
 */
void turn_clockwise(oi_t *sensor, int degrees);

/**
 *  Rotates the iRobot Create a specified number of degrees in the counter-clockwise direction
 *
 *  @param sensor a struct containing the data from all the sensors onboard the Create
 *  @param degrees the number of degrees to rotate the Create counter-clockwise
 */
void turn_counterClockwise(oi_t *sensor, int degrees);

#endif
