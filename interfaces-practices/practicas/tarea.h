#include <Arduino.h>
#include <Wire.h>
#include <IRremote.hpp>
#include "myLcd.h"
#include <DHT.h>

#define LED_PIN       12
#define BUZZER_PIN    11
#define TRIGGER_PIN   10
#define ECHO_PIN      9
#define RECEIVER_PIN  4

#define DHT_PIN 2     
#define DHTTYPE DHT11

MyLCD lcd(0x27, 16, 2);
DHT dht(DHT_PIN, DHTTYPE);

void handler(uint16_t command);
void showLedState( void );
void showDHT(char option);
void proximity( void );
int getDistance( void );

void setup( void ) {

  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  Serial.begin(9600);
  dht.begin();
  IrReceiver.begin(RECEIVER_PIN);
  lcd.init();
  lcd.backlight();

}
 
void loop( void ) {

  if( IrReceiver.decode() ) {
    uint16_t command = IrReceiver.decodedIRData.command;
    handler(command);
    IrReceiver.resume();
  }

  delay(300);

}

void handler(uint16_t command) {

  switch (command) {
    case 0x20:
      showLedState();
      break;
    case 0x30:
      showDHT('T');
      break;
    case 0x40:
      showDHT('H');
      break;
    case 0x50:
      proximity();
      break;
    case 0x60:
      digitalWrite(LED_PIN, !digitalRead(LED_PIN));
      break;

    default:
      break;
  }

}

void showLedState() {

  lcd.clear();
  if(digitalRead(LED_PIN))
    lcd.print("LED ENCENDIDO");
  else
    lcd.print("LED APAGADO");

}

void showDHT(char option) {

  int data;

  lcd.clear();
  if(option == 'T'){
    data = dht.readTemperature();
    lcd.print("La temperatura es");
  } else {
    data = dht.readHumidity();
    lcd.print("La humedad es");
  }
  if(isnan(data)) {
    lcd.clear();
    lcd.print("Error");
    return;
  }
  lcd.setCursor(5, 1);
  lcd.print(data);

}

void proximity( void ) {

  int distance;
  int sleep;
  bool buzzerState = false;
  while(true) {

    distance = getDistance();
    lcd.clear();
    lcd.print("  Proximidad");
    lcd.setCursor(3, 1);
    lcd.print(distance);
    lcd.print("cm");

    sleep = map(distance, 3, 15, 200, 1000);
    analogWrite(BUZZER_PIN, 100);
    delay(sleep);
    analogWrite(BUZZER_PIN, 0);
    delay(sleep);

    if( IrReceiver.decode() ) {
      uint16_t command = IrReceiver.decodedIRData.command;
      Serial.println(command);
      IrReceiver.resume();
      if(command == 0x20){
        return;
      }
    }

  }

}

int getDistance( void ) {

  const int CONSTANT_VELOCITY = 58;
  long time = 0;

  // Apagar por 4 microsegundos el trigger
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);

  // Encender el trigger por 10 microsegundos
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);

  // Contamos el tiempo de retorno de la onda de sonido
  time = pulseIn(ECHO_PIN, HIGH);

  // Calculamos la distancia con ayuda de la constante de conversión
  return time / CONSTANT_VELOCITY;

}