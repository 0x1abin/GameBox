#include "hal_keypad.h"


typedef enum
{
  KEY_DOWN,           //!< KEY_DOWN
  KEY_UP,             //!< KEY_UP
  KEY_PRESS,          //!< KEY_PRESS
  KEY_HOLD,           //!< KEY_HOLD
  KEY_TRIPLE_PRESS,   //!< KEY_TRIPLE_PRESS
  KEY_HOLD_10SEC,     //!< KEY_HOLD_10SEC
  NUMBER_OF_KEY_EVENTS//!< NUMBER_OF_KEY_EVENTS
}
KEY_EVENT_T;

typedef struct
{
  uint8_t keyname;
  uint8_t event;
}keyEvent_t;


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