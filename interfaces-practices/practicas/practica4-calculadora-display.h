#include <Arduino.h>
#include "keypadConf.h"
// #include "lcdConf.h"
#include "myLcd.h"

MyLCD lcd(0x27, 20, 4);

const char op_sings[]  = {'+','-','*','/'};
String userInput;
float term1;
float term2;
char op;
bool term1_ready = false;
bool term2_ready = false;
bool reboot = true;

float get_result();
void callback(KeypadEvent key);

void setup() {
    Serial.begin(9600);
    keypad.addEventListener(callback);

    lcd.init();
    lcd.backlight();
    lcd.print("  Mi Calculadora");
    lcd.setCursor(0, 1);
}

void loop() {

    char key = keypad.getKey();
    if (key != NO_KEY && reboot) {

        if ( (isDigit(key) || key == '.') ) {

            userInput += key;
            Serial.print(key);
            lcd.print(key);

        } else if ((strchr(op_sings,key)) && !term1_ready) {

            term1 = userInput.toFloat();
            op = key;
            Serial.print(op);
            lcd.print(op);
            userInput = "";
            term1_ready=true; 

        } else if ((key == '=') && (term1_ready)) {

            term2 = userInput.toFloat();
            Serial.print('=');
            lcd.print('=');
            Serial.println(get_result());
            lcd.print(get_result());
            userInput = "";
            term1_ready=false;
            reboot = false;

        }

    }
}

float get_result() {
    switch (op) {
        case '+':
        return term1 + term2;
        case '*':
        return term1 * term2;
        case '-':
        return term1 - term2;
        case '/':
        return term1 / term2;
    }
}

void callback(KeypadEvent key) {

  switch (keypad.getState()) {
    case HOLD:
    if(key=='+'){
      Serial.println();
      userInput="";
      term1_ready=false;
      lcd.clearLine(1);
      reboot = true;
    }   
    break;
  }

}