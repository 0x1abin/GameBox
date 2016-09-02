#include "config.h"

/****************游戏预览动画，共4帧**************************/
uint8 code tetris_mod[4][8]=
{
	{0x08,0x0C,0x08,0x00,0x00,0x91,0xB3,0xB7},
	{0x00,0x00,0x00,0x00,0x00,0x99,0xBF,0xBF},
	{0x60,0x40,0x40,0x00,0x00,0x99,0xBF,0xBF},
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xF9},
};
uint8 code snake_mod[4][8]=
{
	{0x00,0x00,0x00,0x00,0x00,0x00,0x2E,0x00},
	{0x00,0x00,0x00,0x00,0x00,0x00,0x3C,0x00},
	{0x20,0x00,0x00,0x20,0x20,0x20,0x30,0x00},
	{0x20,0x20,0x20,0x20,0x20,0x20,0x00,0x00},
};
uint8 code RAC_mod[4][8]=
{
	{0x8F,0x85,0x0A,0x81,0xA1,0x70,0xA1,0xD1},
	{0x00,0x85,0x8F,0x04,0xAB,0xF1,0x20,0xD1},
	{0x81,0x00,0x81,0x85,0x2E,0xF5,0xAB,0x50},
	{0x00,0x81,0x81,0x00,0xA1,0xF1,0x20,0xD1},
};
uint8 code shot_mod[4][8]=
{
	{0xBB,0xFB,0x00,0x00,0x00,0x00,0x04,0x0E},
	{0xF6,0xBB,0xFB,0x00,0x10,0x00,0x10,0x38},
	{0xF6,0xBB,0xEB,0x00,0x00,0x00,0x10,0x38},
	{0xCF,0xF6,0xBB,0xEB,0x00,0x00,0x10,0x38},
};


/***************************************************/


static void GUI_Light_ADJ()
{
	uint8 i;
	uint8 code light[2]={0x42,0x24};
	uint8 code tu[2]={0x3c,0x24};
	DispRAM[0]=tu[0];
	DispRAM[1]=tu[1];
	DispRAM[10]=tu[1];
	DispRAM[11]=tu[0];
	DispRAM[12]=0x00;
	DispRAM[13]=0x00;
	DispRAM[14]=light[0];
	DispRAM[15]=light[1];
	
	for(i=2;i<10;i++){	//亮度条显示
		DispRAM[i] = ((i+1)>(duty/10) ? 0x00:0x18);
	}
}

static void GUI_Sound_SET()
{
	code uint8 S_Logo[8]={0x00,0x19,0x2A,0xC8,0x8B,0xC8,0x2A,0x19};
	code uint8 S_ON[8]={0x00,0x00,0x42,0x62,0x52,0x4A,0x46,0x42};/*ON*/
	code uint8 S_OFF[8]={0x00,0x00,0x3C,0x20,0x20,0x3C,0x20,0x20};/*OFF*/
	int8 i;
	for(i=15;i>7;i--)
		DispRAM[i] = S_Logo[15-i];
		
	if(sound_ON)
	{
		for(i=7;i>-1;i--)
			DispRAM[i] = S_ON[7-i];
	}
	else
	{
		for(i=7;i>-1;i--)
			DispRAM[i] = S_OFF[7-i];
	}
}

void Flash_Screen_Clear()//屏幕刷新动画
{
	int8 i,p,n;
	code uint8 bitman[8]={1,2,4,8,16,32,64,128};
	for(p=0;p<8;p++)
		for(i=0;i<8;i++)
		{
			n=2;
			DispRAM[p] |= bitman[i];
			DispRAM[15-p] |= bitman[7-i];
			while(n--)	MatxDisp(DispRAM,duty);
		}
	for(p=7;p>=0;p--)
		for(i=7;i>=0;i--)
		{
			n=2;
			DispRAM[p] &= ~bitman[i];
			DispRAM[15-p] &= ~bitman[7-i];
			while(n--)	MatxDisp(DispRAM,duty);
		}
}


void GUI_Game_Preview(uint8 s, uint16 fps, uint8 (*mod)[8])
{
	uint8 i = 0;
	if((tms/fps) > 3)	tms=0;//动画帧率控制
	while(i<8)
	{
		DispRAM[i] = mod[tms/fps][7-i];//动画装载
		i++;
	}
	for(i=0;i<5;i++)//游戏选择画面序号显示处理
	{
		DispRAM[14-i] = (num[s][i]<<2);
	}
	DispRAM[15] = 0x00;
	DispRAM[9]	= 0x00;
	DispRAM[8]	= 0x00;
}

void GUI_Preview_Load(uint8 n)	//装载游戏预览动画数据
{
	switch (n)
	{
		case 1:	GUI_Game_Preview(n,VIEW_FPS,tetris_mod);
			break;
		case 2:	GUI_Game_Preview(n,VIEW_FPS,snake_mod);
			break;
		case 3:	GUI_Game_Preview(n,VIEW_FPS,RAC_mod);
			break;
		case 4:	GUI_Game_Preview(n,VIEW_FPS,shot_mod);
			break;
		case 5:	GUI_Light_ADJ();
			break;
		case 6:	GUI_Sound_SET();
			break;
	}
}

//void Copier(uint8 *cpy,uint8 *dat)//数据拷贝，用于缓存当前数据
//{
//	while(*cpy++ = *dat++);//听说指针这样用看起来比较拽
//}

void GUI_ScreenTransl(uint8 n,uint8 xfps)//画面平移
{
	static s_ls = 1;//用于左右移动判断
	uint8 i,j,b;
	uint8 tmpram[16];
	for(i=0;i<16;i++)
	{
		tmpram[i] = DispRAM[i];//转移数据，用于平移画面做准备
	}
	GUI_Preview_Load(n);
	for(j=0;j<8;j++)
	{	
		for(i=0;i<16;i++)
		{
			if(n < s_ls)//左移
			{	
				if(DispRAM[i]&0x01)	b=0x80;
				else	b=0;
				tmpram[i]=(tmpram[i]>>1) | b;
				DispRAM[i] = DispRAM[i]>>1;
			}
			else		//右移
			{
				if(DispRAM[i]&0x80)	b=1;
				else	b=0;
				tmpram[i]=(tmpram[i]<<1) | b;
				DispRAM[i]=DispRAM[i]<<1;
			}
		}
		tms=0;
		while(tms < xfps) MatxDisp(tmpram,duty);//画面平移速度
	}
	s_ls = n;//记忆当前序号，用于判断左或右移
	keypad = K_NULL;//平移动画过程需要时间，会与按键消抖时间产生BUG，出现按键连续触发现象，故消除一下按键状态消除BUG
}

uint8 GUI_Main()
{
	static uint8 s = 1;
	uint8 k = K_NULL;
	while(1)
	{
		switch (Get_Kvuale(150))
		{
			case K_NULL:	
				break;
			case K_UP:	if(s==5) if(duty<100) duty+=10;
				break;
			case K_DOWN:if(s==5) if(duty>=10) duty-=10;	
				break;
			case K_LEFT:if(s>1)
						{
							s--;
							GUI_ScreenTransl(s,SMOVE_SPEED);
						}
				break;
			case K_RIGHT:if(s<6)
						 {
							s++;
						 	GUI_ScreenTransl(s,SMOVE_SPEED);
						 }
				break;
			case K_OK:	if(s==6)
						{	
							sound_ON = ~sound_ON;
							Play_Music(sound_up);
						}
						else if(s<5) return s;//返回选择游戏的序号
				break;
		}
		
		GUI_Preview_Load(s);
		MatxDisp(DispRAM,duty);
	}//while
}