# MarsRover

This is the code for the final project of an embedded systems class. We worked with an Atmega128 microcontroller connected to an iRobot 
Create as well as external sonar and IR sensors wired to the Atmega128. The goal of this project was to create a program that allowed 
the iRobot to navigate a course with random obstacles scattered around with the goal of reaching the "retrieval zone". The iRobot has the
ability to scan the environment in front of it and transmit data about the objects it finds over Bluetooth to a computer where it is 
interpreted by a human and commands are sent back to the robot telling it where to move.

## Components

#### iRobot Code

All of this code was written in C. The code interacted with the various sensors plugged into the Atmega128 as well as the sensors that 
are part of the iRobot Create (bump, cliff, ir-wall, etc). All of this code ran only on the Atmega128 and communicated over Bluetooth 
to send data on found objects and receive movement commands from the computer.

#### GUI Code 

A GUI was created to allow communication between a human and the robot. All the GUI code was written in Java using Java Swing components.
An external library was used to handle the serial communication over Bluetooth to the robot. The GUI allows the "driver" to tell the 
robot to scan for objects, move a specified distance, rotate a specified number of degrees, or transmit the current values of the sensors
on the iRobot Create.

#### Documentation

HTML documentation pages for the library functions that were written specifically for this project. Does not include documentation for 
libraries provided to us for the class (i.e. open_interface).
