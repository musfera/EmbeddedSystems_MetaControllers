//
// MotorControllor
//
// Description of the project
// Developed with [embedXcode](http://embedXcode.weebly.com)
//
// Author 		William Nodvik
// 				William Nodvik
//
// Date			12/12/18 12:19 PM
// Version		<#version#>
//
// Copyright	© William Nodvik, 2018
// Licence		<#licence#>
//
// See         ReadMe.txt for references
//


// Core library for code-sense - IDE-based
// !!! Help: http://bit.ly/2AdU7cu

#include "Arduino.h"


// Set parameters


// Include application, user and local libraries



// Define structures and classes


// Define variables and constants

#define RightMotor 5
#define LeftMotor  6


// Prototypes


// Utilities


// Functions

//RampUp brings motor to full speed, which happens rather quickly
void rampUp( int pinNum ){
    for (int i = 15; i < 150; i++) {//i starts at 10% D because it lacks the current neccessary to torque the weight
        analogWrite(pinNum, i);
        delay(50);
    }
    analogWrite(pinNum, 0);//turn off motor after ramping up
}

void rampDown( int pinNum ){
    for (int i = 150; i > 0; i--) {
        analogWrite(pinNum, i);
    }
}

//Step Up increments the motor speed every 500 ms @ 1/4 - 1/2 - 3/4 speeds
void stepUp( int pinNum ){
    analogWrite(pinNum, 37);
    delay(500);
    analogWrite(pinNum, 75);
    delay(500);
    analogWrite(pinNum, 150);
    delay(500);
    analogWrite(pinNum, 0); //Turns motor off
}

void halfSecondPulses( int pinNum, int duration){
    for (int i = 0; i < duration; i++) {
        analogWrite(pinNum, 150); //60% duty cycle for full motor power
        delay(500);
        
        analogWrite(pinNum, 0);
        delay(500);
    }
}

// Add setup code
void setup()
{
    pinMode( RightMotor, OUTPUT);
    pinMode( LeftMotor, OUTPUT);
}

// Add loop code
void loop()
{
    stepUp(LeftMotor);
    delay(1000);
    rampUp(LeftMotor);
    delay (1000);
    halfSecondPulses(LeftMotor, 4);
    delay(1000);
    //halfSecondPulses(LeftMotor, 4);
}
