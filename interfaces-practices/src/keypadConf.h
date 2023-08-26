#include <Keypad.h>

#define ROWS    4 
#define COLUMNS 4

const char KEYS[ROWS][COLUMNS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowsPins[ROWS] = {9, 8, 7, 6}; 
byte columnsPins[COLUMNS] = {5, 4, 3, 2}; 

Keypad keypad = Keypad( makeKeymap(KEYS), rowsPins, columnsPins, ROWS, COLUMNS); 