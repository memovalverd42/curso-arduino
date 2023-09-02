#include "keypadConf.h"
#include "myLcd.h"

MyLCD lcd(0x27, 20, 4);

#define TOTAL_RANDOM_NUMBERS 20

int players = 0;
int actual_player;
int numbers[TOTAL_RANDOM_NUMBERS];
int index = 0;

void start_game( void );
int get_players( void );
bool play_turn( int player );
void show_numbers( void );
void print_number( int n );

void setup( void ) {

    Serial.begin(9600);
    lcd.init();
    lcd.backlight();
    randomSeed( analogRead(A0) );
    
    start_game();

}

void loop( void ) {

    if( play_turn(actual_player) ) {
        if(players > 1){
            actual_player += 1;
            if(actual_player > players) {
                actual_player = 1;
            }
        }

        show_numbers();
    } else {
        Serial.print("El jugador ");
        Serial.print(actual_player);
        Serial.println(" perdio!");

        lcd.print2(0,0, "El jugador" + (String)actual_player, true);
        lcd.print2(0,1, "Perdio!");
        delay(1000);

        start_game();
    }

}

void start_game( void ) {

    Serial.println("Presiona A para comenzar un nuevo juego");
    lcd.print2(2,0, "Presione A para ", true);
    lcd.print2(1,1, "comenzar el juego");
    while( keypad.getKey() != 'A' ){}
    players = get_players();
    actual_player = 1;
    index = 0;

    show_numbers();

}

// Funcion para solicitar el numero de jugadores
int get_players( void ) {
    Serial.println("\nIngresa el numero de jugadores: ");
    lcd.print2(0, 0, "Numero jugadores: ", true);
    char c;
    while( true ) {
        c = keypad.getKey();
        if( c != '0' && isDigit(c) ){
            Serial.println(c);
            lcd.print(c);
            delay(1500);
            lcd.clear();
            return c-48;
        }
    } 
}

void show_numbers( void ) {

    numbers[index] = random(256);

    for(int i=0; i<=index; i++){
        // print_number(numbers[i]);
        lcd.print2(5, 0, numbers[i], true);
        delay(1000);
        // lcd.clear();
    }
    
    index++;

}

void print_number( int n ) {
    for(int i=0; i<100; i++)
        Serial.println();

    Serial.println(n);
}

bool play_turn( int player ) {

    String user_input;      // Variable para almacenar numero del usuario
    String str_number;      // Para guardar el numro esperado como String
    char c;                 // Para obtener caracter del teclado
    int i = 0;              // Index del numero que se espera

    Serial.print("\nTurno de jugador ");
    Serial.println(player);

    lcd.print2(0, 0, "Turno de jugador: " + (String) player, true);
    lcd.setCursor(4, 1);

    while( true ) {

        c = keypad.getKey();
        str_number = (String) numbers[i];
        if( c != NO_KEY && isDigit(c) ) {

            Serial.print(c);
            lcd.print(c);
            user_input += c;

            if( user_input.length() == str_number.length() ){

                if(user_input == str_number){

                    user_input = "";
                    i++;
                    Serial.println();
                    lcd.clearLine(1);
                    lcd.setCursor(4, 1);
                    if(i == index){
                        return true;
                    }

                } else {

                    Serial.println("Perdiste!");
                    lcd.print2(4,0, "Perdiste!", true);
                    delay(1500);
                    return false;

                }

            }
            
        }

    }

}