#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_DCMotor *motor_right = AFMS.getMotor(1); 
Adafruit_DCMotor *motor_left = AFMS.getMotor(2);

#define echoPin1 41// attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin1 31//attach pin D3 Arduino to pin Trig of HC-SR04
#define echoPin2 42// attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin2 32//attach pin D3 Arduino to pin Trig of HC-SR04
#define echoPin3 43// attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin3 33//attach pin D3 Arduino to pin Trig of HC-SR04
#define echoPin4 44// attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin4 34//attach pin D3 Arduino to pin Trig of HC-SR04

// defines variables
long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement

void setup() {
  Serial.begin(9600); 
  AFMS.begin();  
  motor_right->setSpeed(100);
  motor_left->setSpeed(100);
  pinMode(trigPin1, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin1, INPUT); // Sets the echoPin as an INPUT
  pinMode(trigPin2, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin2, INPUT); // Sets the echoPin as an INPUT
  pinMode(trigPin3, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin3, INPUT); // Sets the echoPin as an INPUT
  pinMode(trigPin4, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin4, INPUT); // Sets the echoPin as an INPUT
}
 
void loop() {
  if(Serial.available()) // Chek for availablity of data at Serial Port
  {
    char data = Serial.read(); // Reading Serial Data and saving in data variable
    
     // Printing the Serial data
    if(data == 's'){
      int rcr = 0;
      int rr=sensor (trigPin1,echoPin1);
      if ( rr <= 20){
         rcr = 1;
        }
       int crc = 0;
      int cr = sensor (trigPin2,echoPin2);
      if ( cr <= 20){
        crc = 2;
        }
      int clc= 0;
      int cl = sensor (trigPin3,echoPin3);
      if ( cl <= 20){
        clc = 4;
        }
      int lcl=0;
      
      int ll= sensor (trigPin4,echoPin4);
      if ( ll <= 20){
        lcl = 8;
        }
      int result = rcr + crc + clc + lcl;
      if(result < 10){
        String nresult = String(result);
        Serial.print("0"+nresult);
      }
       else{
        String nresult = String(result);
        Serial.print(nresult);
       }
     
      }
    else if(data == 'c'){
      int rr=sensor (trigPin1,echoPin1);
      int cr = sensor (trigPin2,echoPin2);
      int cl = sensor (trigPin3,echoPin3);
      int ll= sensor (trigPin4,echoPin4);
      if (rr < 10 || cr < 10 || cl < 10 || ll < 10){
        Serial.print('y');
      }
      else {
        Serial.print('n');
        }
      
      }
    else if(data == 'f'){
      motor_right->run(FORWARD);
      motor_left->run(FORWARD);
      delay(200);
      motor_right->run(RELEASE);
      motor_left->run(RELEASE);
      }
   else if(data == 'b'){
      motor_right->run(BACKWARD);
      motor_left->run(BACKWARD);
      delay(200);
      motor_right->run(RELEASE);
      motor_left->run(RELEASE);
      }
   else if(data == 'r'){
      motor_right->run(FORWARD);
      motor_left->run(RELEASE);
      delay(100);
      motor_right->run(RELEASE);
      motor_left->run(RELEASE);
      }
   else if(data == 'l'){
      motor_right->run(RELEASE);
      motor_left->run(FORWARD);
      delay(100);
      motor_right->run(RELEASE);
      motor_left->run(RELEASE);
      }
  }
  
 
}
int sensor (int trigPin, int echoPin){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
 // Reads the echoPin, returns the sound wave travel time in microseconds
   duration = pulseIn(echoPin, HIGH);
 // Calculating the distance
 distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
 return distance;
}
