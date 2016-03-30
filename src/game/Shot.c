#include "config.h"

uint8 site;
uint8 bullet = 0;
uint8 aim_layer = 1;
uint8 plane[2];
uint8 block[16];
static void Shot_One();

static void Shot_One()
{
	if(bullet>15){
		bullet=1;
		return;
	}
	if(bitman[site] & block[bullet])
	{
		block[bullet] &= (~bitman[site]);//消除被射击块
		bullet=1;
		scores++;
//		Sound_Tone(1,site+1,5);
	}
	else
	{
		++bullet;
		Sound_Tone(sound_ON,bullet,1);
		DisPoint(site,bullet);	//迭代产生弹道
		delayus(300);
		Shot_One();	//递归消除
	}
}

static void Block_Down()
{
	uint8 i;
	for(i=0;i<15;i++)
	{
		block[i] = block[i+1];
	}
	block[15] = rand()%256;
}
static void Key_Control()
{
	int8 k = Get_Kvuale(150);
	switch (k)
	{
		case K_LEFT: if(site < 7) site++;
			break;
		case K_RIGHT:if(site > 0) site--;
			break;
		case K_OK:	Shot_One();	return;
			break;
		default: break;
	}
	if(!(tms%20)) if(!KEY_OK)	Shot_One();
}

static void Shot_Game_Init()
{
	uint8 i;
	Glife=1;
	site=3;
	scores=0;
	bullet=0;
	speeds = 1000;
	plane[1] = bitman[site];	//绘制飞机形状
	plane[0] = plane[1]<<1 | plane[1] | plane[1]>>1;
	
	for(i=0;i<16;i++)	block[i]=0x00;	//清楚数据
	block[15] = rand()%256;	//先来一发
}
static void Shot_GameDisp()
{
//	Copier(DispRAM,block);
	uint8 i;
	for(i=0;i<16;i++)
	{
		DispRAM[i] = block[i];
	}
	DispRAM[0] |= plane[0];
	DispRAM[1] |= plane[1];
	MatxDisp(DispRAM,duty);
}
void Shot_Game()
{
	Shot_Game_Init();
	while(Glife)
	{
		Key_Control();
		plane[1] = bitman[site];
		plane[0] = plane[1]<<1 | plane[1] | plane[1]>>1;
		if(tms > (speeds-scores))
		{
			tms = 0;
			Block_Down();
			if(block[0] | (block[1]&plane[1]))	Glife=0;
		}
		Shot_GameDisp();
		SMG_Display(scores,duty);
	}
}
