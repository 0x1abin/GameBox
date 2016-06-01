#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include "common.h"

extern void display_init();
extern void display_update();
extern void display_setBuffer(uint8_t *buf);
extern void display_setBrightness(uint8_t duty);

extern void DisplayInit();
extern void DisplayUpdate();
extern void setDisplayBuffer(uint8_t *buf);
extern void setDisplayBrightness(uint8_t duty);

#endif

