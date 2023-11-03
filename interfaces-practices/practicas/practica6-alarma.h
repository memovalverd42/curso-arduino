#include <Arduino.h>
#include "keypadConf.h"

#define BUZZER      12
#define LDR_PIN     A0
#define FOCO_PIN    7

String password = "12345";
String entrada  = "";
int intensidadLuz;
bool estadoAlarma = false;

void alarma( void );

void setup( void ) {

  Serial.begin(9600);  
  pinMode(FOCO_PIN, OUTPUT); 
  pinMode(BUZZER, OUTPUT);
  digitalWrite(FOCO_PIN, HIGH);

}
 
void loop( void ) {

  char key = keypad.getKey();
  if (key != NO_KEY) 
  {
    entrada = entrada + key;                    //se guarda caracter por caracter en el arreglo codigo[]
    Serial.print(key);                          //se imprime en el puerto serie la tecla presionada
    if(entrada.length() == password.length())   //si ya fueron presionadas 4 teclas se evalúa si la contraseña es correcta
    {
      if(password == entrada)
      {
        estadoAlarma = false;
        Serial.println("\nAlarma Desactivada");
        digitalWrite(FOCO_PIN, HIGH);
      }
      else
      {
        Serial.println("\nVuelve a intentarlo");
      }
      entrada = "";
    }
  }

  intensidadLuz = analogRead(LDR_PIN);
  
  if(intensidadLuz >= 400){
    estadoAlarma = true;
  }

  if(estadoAlarma) {
    alarma();
  } else {
    noTone(BUZZER);
    digitalWrite(FOCO_PIN, 0);
  }

}

void alarma( void ) {
  tone(BUZZER, 100);
  digitalWrite(FOCO_PIN, 1);
  delay(100);
  noTone(BUZZER);
  digitalWrite(FOCO_PIN, 0);
  delay(100);
}