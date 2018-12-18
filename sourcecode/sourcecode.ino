//Embedded Systems Final Project "Blind Leading the Blind"
//Group 15 MetaControllers
//Matthew Avallone, Will Nodvik, Musfera Khan

#include <Wire.h>
#include "Adafruit_LSM303_U.h"
#include <Servo.h> 
#include "Ultrasonic.h"
#include "Arduino.h"


#define rightRumble 5
#define leftRumble  6
#define compassMotorPin 3 

/*============ Initialize Sensors and Motors ===================== */
Servo compassMotor;
Ultrasonic us1(1,2);
Ultrasonic us2(7,8);
Ultrasonic uscenter(9,10);
Adafruit_LSM303_Mag_Unified mag = Adafruit_LSM303_Mag_Unified(12345); //Assign a unique ID to this sensor at the same time

/*============ Rumble Motor Functions ============================= */
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

/*======================= setup ========================= */
void setup(void) 
{
  Serial.begin(115200);
  if(!mag.begin()){
    /* There was a problem detecting the LSM303 ... check your connections */
    Serial.println("Ooops, no LSM303 detected ... Check your wiring!");
    while(!mag.begin());
  }

  //motor for magnetometer
  compassMotor.attach(compassMotorPin); 
  compassMotor.write(0); 
  
  //rumble motors
  pinMode(rightRumble, OUTPUT);
  pinMode(leftRumble, OUTPUT);
} //end setup


/*====================== loop ========================= */
void loop(void) 
{
  sensors_event_t event; 
  mag.getEvent(&event);
  long us1distance = us1.ranging();
  long us2distance = us2.ranging();
  long uscenterdistance = uscenter.ranging();
  float Pi = 3.14159;
  
  // Calculate the angle of the vector y,x
  float heading = (atan2(event.magnetic.y,event.magnetic.x) * 180) / Pi;

  // Normalize to 0-360
  if (heading < 0){  
   // heading = 360 + heading;
    compassMotor.write(heading);
    delay(50);     
  }

  if (heading > 0){
     compassMotor.write(heading); 
      delay(50); 
  }

  if(uscenterdistance < 100){
    analogWrite(leftRumble, 150);
    analogWrite(rightRumble, 150);
  }
  else if(us1distance < 50){
    analogWrite(leftRumble, 150);
  }
  else if(us2distance < 50){
    analogWrite(rightRumble, 150);
  }
  else if(us1distance >= 50){
    analogWrite(leftRumble, 0);
  }
  else if(us2distance >= 50){
    analogWrite(rightRumble, 0);
  }
  else if(uscenterdistance >=100){
    analogWrite(leftRumble, 0);
    analogWrite(rightRumble, 0);
  }
  
//  Serial.print("Compass Heading: ");
//  Serial.println(heading);
//  Serial.print(us1distance);
//  Serial.print("cm - ");
//  Serial.print(uscenterdistance);
//  Serial.print("cm - ");
//  Serial.print(us2distance);
//  Serial.println("cm");
} //end loop
