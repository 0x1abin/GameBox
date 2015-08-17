//#include "config.h"
#include "common.h"

static uint8 key_value;
static uint8 last_key_value;

void Keypad_init()
{
	SET_IN_KEY_UP;
	SET_IN_KEY_DOWN;
	SET_IN_KEY_LEFT;
	SET_IN_KEY_RIGHT;
	SET_IN_KEY_A;
	
	key_value = 0;
	last_key_value = 0;
}

void Keypad_scan_poll()
{
	if(GET_KEYPAD_A == KEY_PRESS_STATE)
	{
		key_value = KEY_VALUE_A;
	}
	else if(GET_KEYPAD_UP == KEY_PRESS_STATE)
	{
		key_value = KEY_VALUE_UP;
	}
	else if(GET_KEYPAD_DOWN == KEY_PRESS_STATE)
	{
		key_value = GET_KEYPAD_DOWN;
	}
	else if(GET_KEYPAD_LEFT == KEY_PRESS_STATE)
	{
		key_value = GET_KEYPAD_LEFT;
	}
	else if(GET_KEYPAD_RIGHT == KEY_PRESS_STATE)
	{
		key_value = GET_KEYPAD_RIGHT;
	}
	else 
	{
		last_key_value = 0;		//release the key
	}
	
	if(key_value == last_key_value)
	{
		key_value |= KEY_PRESS_AGAIN;
	}
	else 
	{
		last_key_value = key_value;
	}
}

uint8 get_keypad()
{
	uint8 keyretutn = key_value;
	key_value = 0;
	return keyretutn;
}

