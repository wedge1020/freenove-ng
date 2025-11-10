#ifndef _KEY_H
#define _KEY_H

#include <stdint.h>
#include <wiringPi.h>

#define  OPEN    LOW
#define  CLOSED  HIGH

typedef enum{ IDLE, PRESSED, HOLD, RELEASED } KeyState;

const char NO_KEY = '\0';

struct key
{
    int8_t    kchar;
    int32_t   kcode;
    KeyState  kstate;
    bool      stateChanged;

    void      (*init_key)   (uint8_t);
    void      (*key_update) (uint8_t, KeyState, bool);
};
typedef struct key Key;

#endif  _KEY_H
