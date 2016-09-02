#ifndef __DISPLAY_DRIVES_H__
#define __DISPLAY_DRIVES_H__

#include "typedef.h"
#define cdata	P0	//行数据口
#define IORow_A P1	//列选
#define IORow_B P2

extern void ROW_data(uint8 rdata);		//行选择模块
extern void DisPoint(uint8 x,uint8 y);	//显示指针
extern void MatxDisp(uint8 *buf,uint8 duty);//刷新显示
extern void SMG_Display(uint16 goal,uint8 duty);

#endif

