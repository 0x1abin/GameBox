#include "config.h"

#define ASPEED 28 	//按加速键后的速度
uint8 ucar=1;		//你的车，1靠右，2靠左

static void keyscan()
{
	static bit r = 0;
	int8 k = Get_Kvuale(30);
	if(KEY_OK==0) {
		speeds = ASPEED;
		if(!sound_cnt_time | r) Sound_Tone(sound_ON,6,255);
		r=0;
	}
	else{	//随着分数的增加， 游戏速度逐渐加快
		speeds = 200 - scores/10;
		if(!sound_cnt_time | !r) Sound_Tone(sound_ON,1,255);
		r=1;
	}
	if(k==K_LEFT)	ucar=1;
	if(k==K_RIGHT)	ucar=2;
}
void RAC_Game()
{	
	int8 xcar[4][2]={0};	//[2] 0:左/右/无;	1:车的Y轴位置
	uint8 code carport[3][4]={{0,0,0,0},{0x50,0x20,0x70,0x20},{0x0a,0x04,0x0e,0x04}};
	uint8 code track[5]={0x81,0x81,0x81,0x00,0x00};
	uint8 carid=0,lastid=0,stp=0;
	uint8 p,i;
	Glife=1;
	speeds = 200;
	scores = 0;
	for(i=0;i<4;i++){
		xcar[i][1]=i*5;//其它赛车之间间隔控制,重要部分!
		xcar[i][0]=0;
	}	
	/******************初始化完成,开始游戏***********************/
	while(Glife){	
//		分层扫描,将画面两边的赛道和赛车分为两次扫描，使跑道跟赛车产生画面对比度
//		uint8 xtmp[16];
//		for(p=0;p<16;p++)//刷新跑道
//			DispRAM[p]=track[(p+stp)%5];//动态跑道算法
//		for(p=0;p<16;p++){
//			xtmp[p]=0x00;
//			for(i=0;i<4;i++)	//刷新其他赛车
//				if((0<=(p-xcar[i][1])) && (p-xcar[i][1])<4)	
//					xtmp[p] = carport[xcar[i][0]][p-(xcar[i][1])];
//			if(p<4)
//				if(xtmp[p] & carport[ucar][p])//判断你的赛车是否与其它赛车碰撞
//					Glife=0;
//				else
//					xtmp[p] |= carport[ucar][p];
//		}
		
		//同步扫描
		for(p=0;p<16;p++)//刷新跑道
		{
			DispRAM[p]=0x00;
			DispRAM[p]=track[(p+stp)%5];//动态跑道算法
			
			for(i=0;i<4;i++)//刷新其他赛车
				if((0<=(p-xcar[i][1])) && (p-xcar[i][1])<4)	
					DispRAM[p] |= carport[xcar[i][0]][p-(xcar[i][1])];
			if(p<4)
			{
				if(DispRAM[p] & carport[ucar][p])//判断你的赛车是否与其它赛车碰撞
					Glife=0;
				else	DispRAM[p] |= carport[ucar][p];
			}
		}
		if(tms > speeds)//游戏速度节拍
		{	
			stp++;
			if(stp==5) stp=0;//跑道动态算法标记位
			for(i=0;i<4;i++)
			{
				xcar[i][1]--;	//其他车跟随跑道下移
				if(xcar[i][1]== -4){
					xcar[i][1]=15;
					if(lastid>0)	//游戏规则,如果上次产生的不是空车位,则这一次产生一个空车位
						carid=0;
					else 
						carid=rand()%3;//随机产生一辆车
					lastid = carid;
					xcar[i][0]=carid;
					scores ++;
				}
			}	
			tms=0;
		}
		keyscan();
		MatxDisp(DispRAM,duty);
		SMG_Display(scores,duty);
	}
	TR2_OFF;
}
