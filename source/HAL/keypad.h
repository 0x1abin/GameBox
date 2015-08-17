#ifndef _KEYPAD_H_
#define _KEYPAD_H_

#include "common.h"

#define KEY_VALUE_UP		1
#define KEY_VALUE_DOWN		2
#define KEY_VALUE_LEFT		3
#define KEY_VALUE_RIGHT		4
#define KEY_VALUE_A			5

#define KEY_PRESS_STATE		0
#define KEY_PRESS_AGAIN		0X80

extern void keypad_init();
extern void Keypad_scan_poll();
extern uint8 get_keypad();

#endif

