#include "hal_keypad.h"


void HAL_KeyInit()
{
	//set keypad connent port to output and high pull.
}



uint8_t HAL_KeyRead()
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