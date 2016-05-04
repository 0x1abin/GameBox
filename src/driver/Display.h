#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include "common.h"

extern uint8 xbuff[16];

extern void Display_init();
extern void Display_now();

extern void setDisplayRam(uint8_t *buf);

#endif

