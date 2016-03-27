#include "config.h"

#define NORSPEED 500	//正常游戏速度
#define MAXSPEED 28		//按下DOWN键游戏速度
#define KEYSET	50		//按键判断延时

static char x=0,y=15;		//动态方块的位置标
static uint8 boxID;			//当前方块编号
static uint8 showbox[4];	//动态方块缓存
static uint8 sblock[16];	//静态方块缓存

uint8 code getscore[5] = {0,1,3,7,15};	//一次消除行数得分
uint8 code rotlist[19]={0,2,1,4,3,6,5,8,9,10,7,12,13,14,11,16,17,18,15};//方块旋转链表
uint8 code blocks[19][4]=
{
	{0x00,0x00,0x18,0x18},	//田	0
	{0x10,0x10,0x10,0x10},	// |	1
	{0x00,0x00,0x00,0x3c},	// 一	2
	{0x00,0x08,0x18,0x10},	//右竖	3
	{0x00,0x00,0x30,0x18},	//	Z	4
	{0x00,0x10,0x18,0x08},	//		5
	{0x00,0x00,0x18,0x30},	//		6
	{0x00,0x08,0x08,0x18},	//	」	7
	{0x00,0x00,0x38,0x08},	//		8
	{0x00,0x18,0x10,0x10},	//		9
	{0x00,0x00,0x20,0x38},	//		10
	{0x00,0x10,0x10,0x18},	//	L	11
	{0x00,0x00,0x08,0x38},	//		12
	{0x00,0x18,0x08,0x08},	//		13
	{0x00,0x00,0x38,0x20},	//		14
	{0x00,0x00,0x10,0x38},	//	凸	15
	{0x00,0x08,0x18,0x08},	//		16
	{0x00,0x00,0x38,0x10},	//		17
	{0x00,0x10,0x18,0x10},	//		18
};


static void RandBox()	//随机装载一个方块
{
	uint8 i;
	boxID = rand() % 19;
	   if(KEY_LEFT == 0 && KEY_RIGHT == 0)	boxID = 2;//游戏后门,你懂的！^.^
	for(i=0;i<4;i++)	//装载方块
	{
		showbox[i] = blocks[boxID][3-i];//由于硬件布局的原因，倒序装载，方便点阵操作
	}
}

static char Check_LR(uint8 lr)	//0左1右;;可以移动返回1，遇到障碍返回0
{
	uint8 i;
	if(lr)
	{
		for(i=0;i<4;i++)
		{
			if ((showbox[i] & 0x01) || (showbox[i] >>1 & sblock[i+y]))//边界，静态方块
				return 0;	//检测到移出边界既退出
		}
		return 1;
	}
	else 
	{
		for(i=0;i<4;i++)
		{
			if((showbox[i] & 0x80) ||  (showbox[i] <<1 & sblock[i+y]))//
				return 0;	//检测到移出边界既退出
		}
		return 1;
	}
}
static void moveone(bit lr, uint8 *buf)
{
	uint8 i;
	if(lr)
	{
		for(i=0;i<4;i++)
		{
			buf[i] = buf[i]>>1;
		}
	}
	else 
	{
		for(i=0;i<4;i++)
		{
			buf[i] = buf[i]<<1;
		}
	}
}

static char BoxMover(char lr,uint8 *buf)
{
	char i,j;
	if(lr>0)
	{
		for(j=0;j<lr;j++)
		{
			for(i=0;i<4;i++)
			{
				if(buf[i] & 0x80)
				{	
					return  0;
				}
				buf[i] = buf[i] <<1;
				
				if(j+1 == lr)
					if(buf[i]  & sblock[i+y])
						return  0;
			}
		}
		return  1;
	}
	
	if(lr<0)
	{
		for(j=0;j<(-lr);j++)
		{
			for(i=0;i<4;i++)
			{
				if(buf[i] & 0x01)
				{	
					return  0;
				}
				buf[i] = buf[i] >>1;
				
				if(j+1 == (-lr))
					if(buf[i]  & sblock[i+y])
						return  0;
			}
		}
		return  1;
	}
	return 1;	
}

static void SpinBox()
{
	uint8 i,tmpid,tmpbuf[4]={0};
	tmpid = rotlist[boxID];
	for(i=0;i<4;i++)
		tmpbuf[i] = blocks[tmpid][3-i];//根据链表，变换下一个图像

	if(x > 0)
	{
		if(BoxMover(x,tmpbuf))
		{
			boxID = tmpid;
			for(i=0;i<4;i++)
				showbox[i] = tmpbuf[i];
		}
	}

	else if(x < 0)
	{
		if(BoxMover(x,tmpbuf))
		{
			boxID = tmpid;
			for(i=0;i<4;i++)
				showbox[i] = tmpbuf[i];
		}
	}
	
	else
	{
		bit f = 1;
		for(i=0;i<4;i++)
		{
			if(tmpbuf[i] & sblock[i+y])
			{
				f = 0;
				break;
			}
		}
		if( f )
		{	
			for(i=0;i<4;i++)
				showbox[i] = tmpbuf[i];
			boxID = tmpid;
		}
	}
}
static char Check_Down()	//检测方块下降一个是否与静态方块重叠
{
	if((sblock[15] & showbox[0]) | (sblock[15] & showbox[1]))
		return -1;
	
	if(y==0)							return 1;
	if(sblock[y-1] & showbox[0])		return 1;
	if(sblock[y]   & showbox[1])		return 1;
	if(y<15)
		if(sblock[y+1] & showbox[2])	return 1;
	if(y<14)
		if(sblock[y+2] & showbox[3])	return 1;
	
	return 0;
}

static void TetrisDisp() //0:只扫描静态图像 1:静态和动态图像同时扫描
{
	uint p;
	for(p=0;p<16;p++)
		DispRAM[p] = sblock[p];
	
	for(p=y;p<y+4;p++)
		if(p<16) DispRAM[p] |= showbox[p-y];	

	MatxDisp(DispRAM,duty);
}

static void RowFull()	//检测是否满行并相关处理
{
	uint8 p,k;
	uint8 tmps=0;
	for(p=0;p<16;p++)
	{
		if(sblock[p] == 0xff)
		{
			char c = 4;	//闪烁次数
			tmps++;
			
			while(c--)
			{
				#define BLINKTIME 128	//满行闪烁速度
				uint tmpct = tms+BLINKTIME;
				Sound_Tone(sound_ON,5,3);
				sblock[p] = ~sblock[p];
				while(tmpct > tms)
				{
					MatxDisp(sblock,duty);
					SMG_Display(scores,duty);
				}
			}
			for(k=p;k<15;k++)
			{
				sblock[k] = sblock[k+1];
				if(sblock[k] == 0x00)
					break;
			}
			p--;
		}
	}
	scores += getscore[tmps];
}

static void Tetris_Keyscan()	//
{
	int8 k = Get_Kvuale(150);

	switch (k)
	{
		case K_NULL:break;
		
		case K_LEFT:if(Check_LR(0))
					{
						moveone(0, showbox);
						x++;
					}
				break;			
		case K_RIGHT:if(Check_LR(1))
					{
						moveone(1, showbox);
						x--;
					}
				break;
		case K_OK:	
				Sound_Tone(sound_ON & !(AUXR & 0x10),2,8);
				SpinBox();				
				break;
	}
	
	if(KEY_DOWN==0)
		speeds = MAXSPEED;//当down按下时切换到最大速度方块下坠
	else speeds = NORSPEED;//没按时恢复正常速度
}
static void Tetris_Init()
{
	uint i;
	for(i=0;i<16;i++)	//清除静态内存
		sblock[i]=0x00;
	scores=0;
	keycont=0;
	keypad=0;
	tms=0;
	speeds = NORSPEED;
	RandBox();	//随机装载一个方块
	Glife=1;
}

void Tetris_Game()
{
	Tetris_Init();
	Play_Music(sound_korobelniki);
	while(Glife)
	{
		Tetris_Keyscan();		
		if(tms > speeds)	//游戏速度节拍
		{
			tms=0;
			if(Check_Down() == 1)	//检测动态方块是否已无法再下降
			{
				sblock[y]   |= showbox[0];	//动态方块与静态图像结合
				if(y<15)	sblock[y+1] |= showbox[1];
				if(y<14)	sblock[y+2] |= showbox[2];
				if(y<13)	sblock[y+3] |= showbox[3];

				RowFull();	//检测是否有满行,并执行先关处理				 
				RandBox();	//随机产生一个新方块
				x=0;		
				y=15;		//将动态方块坐标归位,迎接下一个新方块								
			}
			else if(Check_Down() == -1)//检测到方块已堆积到极限
			{
				Glife = 0;//结束游戏
			}
			else 
			{
				y--;	//方块下降一格
			}
		}
		TetrisDisp();//刷新游戏图像
		SMG_Display(scores,duty);
	}
	TR2_OFF;
}







