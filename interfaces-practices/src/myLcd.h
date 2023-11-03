#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

class MyLCD : public LiquidCrystal_I2C {
    public:
        MyLCD(uint8_t lcd_Addr, uint8_t lcd_cols, uint8_t lcd_rows)
            : LiquidCrystal_I2C(lcd_Addr, lcd_cols, lcd_rows) {
        }

        void clearLine(uint8_t line) {
            setCursor(0, line);
            for(uint8_t i=0; i<_cols; i++)
                print(" ");
            setCursor(0, line);
        }

        void print2(uint8_t col, uint8_t row, String data, bool cls = false) {
            if(cls)
                clear();

            setCursor(col, row);
            print(data);
        }

        void print2(uint8_t col, uint8_t row, char data, bool cls = false) {
            if(cls)
                clear();

            setCursor(col, row);
            print(data);
        }

        void print2(uint8_t col, uint8_t row, int data, bool cls = false) {
            if(cls)
                clear();

            setCursor(col, row);
            print(data);
        }

        void print2(uint8_t col, uint8_t row, char* data, bool cls = false) {
            if(cls)
                clear();

            setCursor(col, row);
            print(data);
        }

        // void printString(String text){
        //     uint8_t col = 0;
        //     uint8_t row = 0;
        //     clear();

        //     for(int i=0; i<text.length(); i++){
        //         print2(col, row, text[i]);
        //         col++;
        //         if(col == _cols) {
        //             col = 0;
        //             row++;
        //         }
        //     }
        // }

};