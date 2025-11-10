#include "key.h"

////////////////////////////////////////////////////////////////////////////////////////
//
// init_key(): initialize a keypad key
//
void  init_key (int8_t  userKeyChar)
{
    matrix -> kchar         = NO_KEY;
    matrix -> kcode         = -1;
    matrix -> kstate        = IDLE;
    matrix -> stateChanged  = false;
}

////////////////////////////////////////////////////////////////////////////////////////
//
// key_update(): update a keypad key
//
void  key_update (int8_t  userKeyChar, KeyState  userState, bool  userStatus)
{
    matrix -> kchar         = userKeyChar;
    matrix -> kstate        = userState;
    matrix -> stateChanged  = userStatus;
}
