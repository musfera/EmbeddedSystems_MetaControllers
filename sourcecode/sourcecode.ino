#include <Wire.h>
#include "Adafruit_LSM303_U.h"
#include <Servo.h> 
#include "Ultrasonic.h"

int servoPin = 9; 
Servo Servo1;
Ultrasonic us1(1,2);
Ultrasonic us2(5,6);
Ultrasonic uscenter(3,4);
/* Assign a unique ID to this sensor at the same time */
//Adafruit_LSM303_Mag_Unified mag = Adafruit_LSM303_Mag_Unified(12345);

void setup(void) 
{
  Serial.begin(115200);
//  if(!mag.begin()){
//    /* There was a problem detecting the LSM303 ... check your connections */
//    Serial.println("Ooops, no LSM303 detected ... Check your wiring!");
//    while(!mag.begin());
//  }

  //Servo1.attach(servoPin); 

  //Servo1.write(0); 
}

void loop(void) 
{
  //sensors_event_t event; 
  //mag.getEvent(&event);
  us1distance = us1.ranging();
  us2distance = us2.ranging();
  centerdistance = uscenter.ranging();
  float Pi = 3.14159;
  
  // Calculate the angle of the vector y,x
  //float heading = (atan2(event.magnetic.y,event.magnetic.x) * 180) / Pi;

//  // Normalize to 0-360
//  if (heading < 0){  
//   // heading = 360 + heading;
//    Servo1.write(heading);
//    delay(50);     
//  }
//
//  if (heading > 0){
//
//     Servo1.write(heading); 
//      delay(50); 
//  }
//  Serial.print("Compass Heading: ");
//  Serial.println(heading);
  Serial.print(us1distance);
  Serial.print("cm - ");
  Serial.print(uscenterdistance);
  Serial.print("cm - ");
  Serial.print(us2distance);
  Serial.println("cm");
}
