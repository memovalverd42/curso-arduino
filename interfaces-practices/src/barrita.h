#include <Arduino.h>
#include "myLcd.h"

class Barrita {

    private:
        MyLCD* _lcd;
        int _pos = 0;
        int _row;


        void barritaUP( void ) {
            _lcd->setCursor(_pos, _row);
            _lcd->write(0);
            _pos++;
        }

        void barritaDown( void ) {
            _lcd->setCursor(_pos, _row);
            _lcd->print(" ");
            _pos--;
        }

    public:
        Barrita(MyLCD* lcd, int row) {
            _lcd = lcd;
            _row = row;
        }

        void set( int value ) {

            if(value==_pos)
                return;

            if(value > _pos) {
                for(int i=_pos; i<=value; i++)
                    barritaUP();
            } else {
                for(int i=_pos; i>=value; i--)
                    barritaDown();
            }
            
        }

};