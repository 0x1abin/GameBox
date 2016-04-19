#ifndef _HAL_KEYPAD_H_
#define _HAL_KEYPAD_H_

#define KEY_ACTIVE          0

#define KEY01_MASK	        0X01
#define KEY02_MASK	        0X02
#define KEY03_MASK	        0X04
#define KEY04_MASK	        0X08


extern void    HAL_KeyInit();
extern uint8_t HAL_KeyRead();

#endif
