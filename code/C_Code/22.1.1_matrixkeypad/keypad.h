//
// Filename:    keypad.h
// Description: this is a C port of the C++ library that provides a simple interface
//              to using matrix keypads. Adapted from the Freenove code for use with
//              the Raspberry Pi.
// Reference:   https://github.com/Chris--A/Keypad
//
////////////////////////////////////////////////////////////////////////////////////////

#ifndef  _KEYPAD_H
#define  _KEYPAD_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <wiringPi.h>
#include "key.h"

#define  INPUT_PULLUP     0x02
#define  bitWrite(x,n,b)  (b ? (x |= 1<<n) : (x &= ~(1<<n)))
#define  bitRead(x,n)     ((((x>>n)&1) == 1) ? 1 : 0)

#define  OPEN             LOW
#define  CLOSED           HIGH

typedef int8_t KeypadEvent;

// Made changes according to this post http://arduino.cc/forum/index.php?topic=58337.0
// by Nick Gammon. Thanks for the input Nick. It actually saved 78 int8_ts for me. :)
typedef struct {
    int8_t rows;
    int8_t columns;
} KeypadSize;

#define LIST_MAX 10        // Max number of keys on the active list.
#define MAPSIZE 10        // MAPSIZE is the number of rows (times 16 columns)
#define makeKeymap(x) ((int8_t*)x)


//class Keypad : public Key, public HAL_obj {
class Keypad : public Key {
public:

    Keypad(int8_t *userKeymap, int8_t *row, int8_t *col, int8_t numRows, int8_t numCols);

    uint32_t  bitMap[MAPSIZE];    // 10 row x 16 column array of bits. Except Due which has 32 columns.
    Key key[LIST_MAX];
    unsigned long holdTimer;

    int8_t getKey();
    bool getKeys();
    KeyState getState();
    void begin(int8_t *userKeymap);
    bool isPressed(int8_t keyChar);
    void setDebounceTime(uint);
    void setHoldTime(uint);
    void addEventListener(void (*listener)(int8_t));
    int findInList(int8_t keyChar);
    int findInList(int keyCode);
    int8_t waitForKey();
    bool keyStateChanged();
    int8_t numKeys();

private:
    unsigned long startTime;
    int8_t *keymap;
    int8_t *rowPins;
    int8_t *columnPins;
    KeypadSize sizeKpd;
    uint debounceTime;
    uint holdTime;
    bool single_key;

    void scanKeys();
    bool updateList();
    void nextKeyState(int8_t n, boolean button);
    void transitionTo(int8_t n, KeyState nextState);
    void (*keypadEventListener)(int8_t);
};

//#define __PIN_MODE__PINWRITE__PINREAD__
void pin_mode  (int8_t pinNum, int8_t mode);
void pin_write (int8_t pinNum, boolean level);
int  pin_read  (int8_t pinNum);

#endif
