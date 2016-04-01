#ifndef __SNAKE_H_
#define __SNAKE_H_

#include "typedef.h"

#define MAX_SNAKE 128
struct Snake
{
	char x[MAX_SNAKE];	//snake.x[0]为蛇头
	char y[MAX_SNAKE];
	char node;			//蛇的节数
	char direc;		//unsigned char direction;/*蛇移动方向*/
	int life_time;		//蛇存活时间
	uint8 life;			//蛇的生命,1活着,0死亡
};

extern void Snake_Game(void);

#endif
