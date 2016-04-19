#inculde "key.h"


typedef enum
{
  KEY01,         //!< KEY01
  KEY02,         //!< KEY02
  KEY03,         //!< KEY03
  KEY04,         //!< KEY04
  KEY05,         //!< KEY05
  KEY06,         //!< KEY06
  NUMBER_OF_KEYS //!< NUMBER_OF_KEYS
}KEY_NAME_T;

/*!
 * Holds the key events and the number of events. Add more events before
 * NUMBER_OF_KEY_EVENTS, if necessary.
 */
typedef enum
{
  KEY_DOWN,           //!< KEY_DOWN
  KEY_UP,             //!< KEY_UP
  KEY_PRESS,          //!< KEY_PRESS
  KEY_HOLD,           //!< KEY_HOLD
  KEY_TRIPLE_PRESS,   //!< KEY_TRIPLE_PRESS
  KEY_HOLD_10SEC,     //!< KEY_HOLD_10SEC
  NUMBER_OF_KEY_EVENTS//!< NUMBER_OF_KEY_EVENTS
}KeyEventCode;

typedef struct{
	uint8_t keyVal;                 //!< key value and the value 0 is reserve
	KeyEventCode event;                //!< key event type
}TKeyEvent;

void KeyInitial()
{
	
}

bool getKeyVal(keyEvent* keybuf)
{
	
}

void KeyScanPoll()
{
	static uint8_t keyState = 0;
	static TKeyEvent keyEventBuf;
	uint8_t newKeyVal = HAL_ReadKey();
	
	switch(keyState)
	{
		case STATE_KEY_START:
			keyState = STATE_KEY_CHECKING;
			break;
			
		case STATE_KEY_CHECKING:
			if(newKeyVal != KEY_NULL)
			{
				keyEventBuf.keyVal = newKeyVal;
				keyEventBuf.event = KEY_DOWN;
				keyState = STATE_KEY_DOWN;
			}
			break;
		
		case STATE_KEY_DOWN:
			if(newKeyVal == keyEventBuf.keyVal)
			{
				++keyCounts;
			}
			else if(newKeyVal == KEY_NULL)
			{
				// keyEventBuf.keyVal = newKeyVal;
				keyEventBuf.event = UP;
				keyState = STATE_KEY_UP;
			}
			break;
			
		case STATE_KEY_UP:
			
			
			break;
	}
}






