#include <Arduino.h>
#include <Wire.h>
#include "myLcd.h"

#define TRIGGER_PIN 4
#define ECHO_PIN    5

MyLCD lcd(0x27, 16, 2);

uint8_t pinLeds[] = { 6, 8, 6, 7 };
int states[] = {
  B0000,
  B1000,
  B1100,
  B1110,
  B1111,
};

int distance;
int state;

int getDistance( void );
void showState( int state );

void setup( void ) {

  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.print("   Distancia: ");

  for(uint8_t i=0; i<4; i++)
    pinMode(pinLeds[i], OUTPUT);

  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  digitalWrite(TRIGGER_PIN, LOW);

}
 
void loop( void ) {

  distance = getDistance();
  if(distance > 15 && distance <= 20)
    showState(1);
  else if(distance > 10 && distance <= 15)
    showState(2);
  else if(distance > 5 && distance <= 10)
    showState(3);
  else if(distance <= 5)
    showState(4);
  else
    showState(0);


  // Imprimir los resultados
  // Serial.print("Distancia: ");
  // Serial.print(getDistance());
  // Serial.println("cm");

  delay(200);

}

void showState( int state ) {

  int bin = states[state];

  for(int i=3; i>=0; i--){
    digitalWrite(pinLeds[i], bin & 1);
    bin >>= 1;
  }

}

int getDistance( void ) {

  const int CONSTANT_VELOCITY = 58;
  int time = 0;

  // Apagar por 4 microsegundos el trigger
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(4);

  // Encender el trigger por 10 microsegundos
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);

  // Contamos el tiempo de retorno de la onda de sonido
  time = pulseIn(ECHO_PIN, HIGH);

  // Calculamos la distancia con ayuda de la constante de conversión
  return time / CONSTANT_VELOCITY;

}