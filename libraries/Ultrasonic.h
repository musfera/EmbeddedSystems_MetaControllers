#ifndef _Ultrasonic_H   
#define _Ultrasonic_H

 class Ultrasonic {
  private:
  int trig;
  int echo;
  char port;
  
  public:
  //constructor takes the trigger and echo pins (using arduino high level numbers, and sets up input/output and identifies port)
  Ultrasonic(int trigPin, int echoPin){ 
    trig = trigPin;
    echo = echoPin;
     if(trigPin >= 0 && trigPin <=7){
        port = 'D';
        Serial.print("in DDRD");
        DDRD |= (1 << trigPin);
     }
     else if(trigPin > 7 && trigPin < 14){
      port = 'B';
        DDRB |= (1 << trigPin-8);
     }
     else{
      port = 'C';
        DDRC |= (1 << trigPin-8);
     }
     
     if(echoPin >= 0 && echoPin <=7){
        port = 'D';
        DDRD &= ~(1 << echoPin);
     }
     else if(echoPin > 7 && echoPin < 14){
        port = 'B';
        DDRB &= ~(1 << echoPin-8);
     }
     else{
        port = 'C';
        DDRC &= ~(1 << echoPin-8);
     }
  }
  long timing(){ //returns the duration of the pulse
    if(port = 'D'){
      //set trig pin low
      PORTD &= ~(1 << trig);
      delayMicroseconds(2);
      //set trig pin high
      PORTD |= (1 << trig);
      delayMicroseconds(10);
      //set trig pin low again
      PORTD &= ~(1 << trig);
    }
    else if(port = 'B'){
      //set trig pin low
      PORTB &= ~(1 << trig);
      delayMicroseconds(2);
      //set trig pin high
      PORTB |= (1 << trig);
      delayMicroseconds(10);
      //set trig pin low again
      PORTB &= ~(1 << trig);
    }
    else {
      //set trig pin low
      PORTC &= ~(1 << trig);
      delayMicroseconds(2);
      //set trig pin high
      PORTC |= (1 << trig);
      delayMicroseconds(10);
      //set trig pin low again
      PORTC &= ~(1 << trig);
    }
    long duration = pulseIn(echo,HIGH); //meaure the time for signal to reach echo
    return duration;
  }

  long ranging(){ //returns the range in sys units (cm or inches)
    long duration = timing();
    long distacne_cm = duration / 29 / 2 ;
    return distacne_cm;
  }  
};

#endif
