#include <Arduino.h>
#include "keypadConf.h"
#include "lcdConf.h"

#define LED_PIN 12

String password = "12345";
String userInput  = "";

byte caracter[8] = {
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
};

void setup( void ) {
    Serial.begin(9600);
    pinMode(LED_PIN, OUTPUT); 

    lcd.init();
    //lcd.createChar(0, caracter);
    lcd.backlight();
    lcd.print("Bienvenido!");
    lcd.setCursor(13, 0);
    lcd.write(0);
    delay(2000);
    lcd.clear();
    lcd.print("     Password:");
    lcd.setCursor(3, 1);
}
  
void loop( void ) {

    char key = keypad.getKey();
    if (key != NO_KEY) {

        userInput += key;              
        Serial.println(key);
        lcd.print("*");
                        
        if( userInput.length() == password.length() ) {

            if(password == userInput) {

                Serial.println("Correcto!");
                digitalWrite(LED_PIN, HIGH);     
                clearLine(1);
                lcd.print("Correcto!");
                delay(1000);
                clearLine(1);
                digitalWrite(LED_PIN, LOW);

            } else {
                Serial.println("Vuelve a intentarlo");
                clearLine(1);
                lcd.print("Vuelve a intentar");
                delay(1000);
                clearLine(1);
            }
            userInput = "";

        }

    }

}
