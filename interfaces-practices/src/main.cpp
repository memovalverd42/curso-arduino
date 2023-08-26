#include <Arduino.h>
#include "keypadConf.h"

#define LED_PIN 12

String password = "12345";
String userInput  = "";

void setup( void ) {
    Serial.begin(9600);
    pinMode(LED_PIN, OUTPUT); 
}
  
void loop( void ) {

    char key = keypad.getKey();
    if (key != NO_KEY) {

        userInput += key;              
        Serial.println(key); 
                        
        if( userInput.length() == password.length() ) {

            if(password == userInput) {
                digitalWrite(LED_PIN, HIGH);     
                Serial.println("Correcto!");
                delay(1000);
                digitalWrite(LED_PIN, LOW);
            } else {
                Serial.println("Vuelve a intentarlo");
            }
            userInput = "";

        }

    }

}
