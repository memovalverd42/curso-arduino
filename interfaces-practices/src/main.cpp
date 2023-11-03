#include <Arduino.h>
#include <Wire.h>

#define IN1 4
#define IN2 5
#define EN  3

void setup( void ) {

  Serial.begin(9600);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(EN, OUTPUT);

  analogWrite(EN, 255);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

}
 
void loop( void ) {

}

