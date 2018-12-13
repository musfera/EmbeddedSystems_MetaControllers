#include <Wire.h>
//#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>
#include <Servo.h> 



int servoPin = 9; 
Servo Servo1;

/* Assign a unique ID to this sensor at the same time */
Adafruit_LSM303_Mag_Unified mag = Adafruit_LSM303_Mag_Unified(12345);

void setup(void) 
{
  Serial.begin(9600);
  Serial.println("Magnetometer Test"); Serial.println("");
  
  /* Initialise the sensor */
  if(!mag.begin())
  {
    /* There was a problem detecting the LSM303 ... check your connections */
    Serial.println("Ooops, no LSM303 detected ... Check your wiring!");
    while(1);
  }

  Servo1.attach(servoPin); 

  Servo1.write(0); 
}

void loop(void) 
{
  sensors_event_t event; 
  mag.getEvent(&event);
  
  float Pi = 3.14159;
  
  // Calculate the angle of the vector y,x
  float heading = (atan2(event.magnetic.y,event.magnetic.x) * 180) / Pi;

   //Servo1.write(heading); 
   // delay(100); 

  // Normalize to 0-360
  if (heading < 0)
  {
    
   // heading = 360 + heading;
    Servo1.write(heading);
    delay(50); 

       
  }

  if (heading > 0){

     Servo1.write(heading); 
      delay(50); 
  }
  Serial.print("Compass Heading: ");
  Serial.println(heading);
  delay(500);
}
