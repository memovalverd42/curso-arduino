#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

void clearLine(uint8_t line) {
    lcd.setCursor(0, line);
    lcd.print("                    ");
    lcd.setCursor(0, line);
}