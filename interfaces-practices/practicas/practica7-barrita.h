#include <Arduino.h>
#include "myLcd.h"

#define BTN_UP    4
#define BTN_DOWN  5
#define LED_PIN   6

MyLCD lcd(0x27, 16, 2);

byte customChar[] = {
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
};

char buffer[5];

int pos = 0;
int valueLed;
int percentage = 0;
bool lasBtnUp = true;
bool lasBtnDown = true;

void barritaUp( void );
void barritaDown( void );

void setup( void ) {

  pinMode(BTN_UP, INPUT_PULLUP);
  pinMode(BTN_DOWN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);

  lcd.init();
  lcd.backlight();
  lcd.createChar(0, customChar);

  lcd.print2(1,0, "Nivel: ");
  lcd.print(percentage);
  lcd.print("%");

}
 
void loop( void ) {

  valueLed = map(pos, -1, 16, 0, 255);

  analogWrite(LED_PIN, valueLed);

  if( !digitalRead(BTN_UP) && lasBtnUp && (pos < 16)) {
    barritaUp();
    percentage = map(pos, -1, 16, 0, 100);
    sprintf(buffer, "%3d%%", percentage);
    lcd.print2(9,0, buffer);
  } lasBtnUp = digitalRead(BTN_UP);

  if( !digitalRead(BTN_DOWN) && lasBtnDown && (pos >= 0)) {
    barritaDown();
    percentage = map(pos, -1, 16, 0, 100);
    sprintf(buffer, "%03d%%", percentage);
    lcd.print2(9,0, buffer);
  } lasBtnDown = digitalRead(BTN_DOWN);

}

void barritaUp( void ) {
  lcd.setCursor(pos, 1);
  lcd.write(0);
  pos++;
}

void barritaDown( void ) {
  lcd.setCursor(pos, 1);
  lcd.print(" ");
  pos--;
}