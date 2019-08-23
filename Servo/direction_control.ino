/*
 *    This project use 9g servo,
 *
 */

#include <Servo.h>                  // include Servo library

Servo servo;                        // Create a servo object to control the servo
int initial_position = 90;          // Declaring the initial position at 90

int pos = 0;                        // variable to store the servo position
int eLDRpin = A0;                   // Analog pin sensor is attached
int wLDRpin = A1;                   // Analog pin sensor is attached
int eastLDR = 0;                    // Create a varieble to store to LDR readings
int westLDR = 0;

void setup() {

  servo.attach(9);               // Attaches the servo object to PWM pin 9
  Serial.begin(9600);
  pinMode(eLDRpin, INPUT);             // Making the LDR pin as input
  pinMode(wLDRpin, INPUT);
}

void loop() {

  eastLDR = analogRead(eLDRpin);    // Read the left side LDR values
  westLDR = analogRead(wLDRpin);    // Read the right side LDR values

  pos = initial_position;
  servo.write(pos);

  // Check whether which value is greater
  if(eastLDR > westLDR){
    // Turn left
    pos--;
    servo.write(pos);
  }else if(westLDR > eastLDR){
    // Turn right
    pos++;
    servo.write(pos);
  }else{
    // Stay in the same position
    pos = pos;
    servo.write(pos);
  }

 }
