#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include "common.h"

extern void DisplayInit();
extern void DisplayUpdate();
extern void SetDisplayBuffer(uint8_t *buf);
extern void SetDisplayBrightness(uint8_t duty);

#endif

