#include "keypadConf.h"

String user_input;
int lev = 1;
int length = 5;

String generate_password(int len, uint8_t level);
int get_lenght( void );
int get_level( void );

void setup( void ) {

    Serial.begin(9600);
    randomSeed( analogRead(A0) );

    Serial.println("Generador de passwords");

}

void loop( void ) {

    Serial.println("Presiona A para iniciar");
    while( keypad.getKey() != 'A' ){}

    length = get_lenght();
    lev = get_level();
    Serial.print("\nTu password generado es: ");
    Serial.println(generate_password(length, lev));

}

int get_lenght( void ) {

    String user_input;
    char c;
    unsigned long previousMillis = millis();

    Serial.print("Longitud del password que deseas (# Para confirmar): ");
    while( true ) {

        c = keypad.getKey();
        if( c != NO_KEY && isDigit(c) ) {

            Serial.print(c);
            user_input += c;

        } else if( c == '#' ) {
            return user_input.toInt();
        }

        if(millis() - previousMillis >= 3000){
            return -1;
        }

    }

}

int get_level( void ) {

    char c;

    Serial.print("\nNivel del password que deseas (1, 2 o 3): ");
    while( true ) {

        c = keypad.getKey();
        if( c != NO_KEY && isDigit(c) ) {

            if( c == '1' || c == '2' || c == '3' ){
                Serial.print(c);
                return c-48;
            } else {
                Serial.println("\nPor favor ingres un valor entre 1 y 3");
            }
            
        } 

    }

}


String generate_password(int len, uint8_t level) {

    int levels[3][2] = {
        {48, 57},           // Nivel 1: '0' al '9'
        {97, 122},          // Nivel 2: 'a' a 'z'
        {48, 122}           // Nivel 3: todo!
    };

    String password;
    int min_value = levels[level-1][0];
    int max_value = levels[level-1][1] + 1;

    for(int i=0; i<len; i++) 
        password += char( random(min_value, max_value) );
    
    return password;

}