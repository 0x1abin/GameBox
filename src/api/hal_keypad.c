#include "hal_keypad.h"


typedef enum
{
  KEY01 = 0,     //!< KEY01
  KEY02,         //!< KEY02
  KEY03,         //!< KEY03
  KEY04,         //!< KEY04
  KEY05,         //!< KEY05
  KEY06,         //!< KEY06
  NUMBER_OF_KEYS//!< NUMBER_OF_KEYS
}BTN_NAME_T;

/** HAL_KeyInit.
 *  @param None.
 */
void HAL_ButtonsInit()
{
	//set keypad connent port to output and high pull.
}


/** HAL_KeyRead.
 *  @param None.
 */
uint8_t HAL_ButtonsRead()
{
	uint8_t key_rawData = 0;
	
	//read the gpio state.
	if(gpio_read(KEY01) == KEY_ACTIVE)
	{
		key_rawData |= KEY01_MASK;
	}
	
	if(gpio_read(KEY02) == KEY_ACTIVE)
	{
		key_rawData |= KEY02_MASK;
	}
	
	if(gpio_read(KEY03) == KEY_ACTIVE)
	{
		key_rawData |= KEY03_MASK;
	}
	
	return key_rawData;
}

void Button_Update()
{
	uint8_t readData = HAL_KeyRead();	     // 1
	pressTrg = readData & (readData ^ hold); // 2
	hold = readData;                         // 3
}

void Button_Update()
{
	#define HOLD_COUNT_THRESHOLD		100
	
	static uint8_t pressTrg, hold, holdCount, prevHold;
	
	uint8_t readData = HAL_KeyRead();	     // 1
	pressTrg = readData & (readData ^ hold); // 2
	hold = readData;                         // 3
	
	static uint8_t keyState = 0;
	
	switch(keyState)
	{
		case STATE_KEY_START:
			keyState = STATE_KEY_CHECKING;
			break;
			
		case STATE_KEY_CHECKING:
			if(pressTrg != 0)
			{
				mKey.keyname = pressTrg;
				mKey.event = KEY_DOWN;
				keyState = STATE_KEY_DOWN;
			}
			break;
		
		case STATE_KEY_DOWN:
			if(hold == prevHold)
			{
				if(++holdCount > HOLD_COUNT_THRESHOLD)
				{
					//holdCount--;
					mKey.keyname = hold;
					mKey.event = KEY_HOLD;
					keyState = STATE_KEY_UP;
				}
			}
			else
			{
				mKey.keyname = prevHold;
				mKey.event = KEY_UP;
				keyState = STATE_KEY_UP;
			}
		
			break;
			
		case STATE_KEY_UP:
			
			keyState = STATE_KEY_CHECKING;
			break;
	}
	
	prevHold = hold;
}

boolean pressed(uint8_t button)
{
	if(dat & button != 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

boolean released(uint8_t button);
boolean held(uint8_t button, uint8_t time);
boolean repeat(uint8_t button, uint8_t period);
uint8_t timeHeld(uint8_t button);


bool get_keyEvent(keyEvent_t *getkey)
{
	if(mKey.event == 0)
		return false;
	
	getkey->keyname = mKey.keyname;
	getkey->event   = mKey.event;
	
	mKey.keyname = 0;
	mKey.event   = 0;
	
	return true;
}


/*
	static uint32_t temp1 = 0;
	static uint32_t temp2 = 0;
	static uint32_t key_in = 0;
	
	temp2 = temp1;
	temp1 = READ_KEY();
	key_in = (temp1&temp2) | (key_in&(temp1|temp2));
	
	
	unsigned char Trg;
	unsigned char Cont;
	void KeyRead( void )
	{
		unsigned char ReadData = PINB^0xff;   // 1
		Trg = ReadData & (ReadData ^ Cont);   // 2
		Cont = ReadData;                      // 3
	}
*/