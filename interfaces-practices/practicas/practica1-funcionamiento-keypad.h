#include <Arduino.h>
#include "keypadConf.h"

void setup( void ) {
  Serial.begin(9600);
}
  
void loop( void ) {

  char key = keypad.getKey();
  
  if (key != NO_KEY) {

    Serial.println(key);

  } 

}
