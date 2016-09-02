/*
//作者：郑梓滨	Jaupin@126.com
//日期：2014年10月27日14:04:35   
//功能：复古掌上俄罗斯方块游戏机源代码，包括游戏GUI，俄罗斯方块、贪吃蛇、经典赛车游戏、射击障碍物游戏
v1.0:
	2014-7-26 00:00:00	:完成有俄罗斯方块游戏基本模型;
	2014-7-28 02:12:03	:将原先临时使用的延时键盘扫描改为外部中断状态位检测键;
	2014-7-28 20:40:37	:完成俄罗斯方块分数计数及分数显示功能;
	2014-8-1 01:01:54	:将较早之前完成贪吃蛇游戏代码合并植入;
	2014-8-2 17:04:25	:整理之前的临时源码,使工程文件规范化;
	2014-8-3 23:50:49	:构建游戏选择画面基本模型,完成画面平移效果;
	2014-8-5 00:50:04	:改进LED点阵底层驱动,用软件PWM调节画面亮度;
	2014-8-7 00:53:35	:完成赛车游戏,用PWM分层扫描画面,形成游戏画面对比度;
	2014-8-8 02:16:44	:完成赛车游戏选择预览画面,并将三个游戏合并在一起;
	2014-8-12 01:47:07	:将逐行扫描改为逐点扫描,使显示亮度均匀;增加亮度调节功能;
	2014-9-9 00:32:40	:修改及优化若干细节；
v1.1:
	2014-9-18 0:57:23	:重新布局电路，修改原先不合理的地方，为制作PCB板作准备；
	2014-9-19 22:02:36	:加入游戏音效，并且可以通过软件方式开关声音；
	2014-9-21 14:59:39	:增加三位mini数码管，实时显示游戏分数，数码管共用点阵并行数据口；
	~~~~~~~~~~~忘记备注
	2014-10-20 21:30:15	:加入射击游戏,将GUI模块化，简化流程
*/

#include "config.h"
volatile uint8 data keypad = K_NULL;	//键盘状态
volatile uint8 data keycont = 0;		//键盘检测消抖定时器
volatile uint16 data tms = 0;			//1ms T0定时器
bit key_state = 0;						//按键状态

uint16 data speeds = 0;		//游戏速度
uint16 data scores = 0;		//游戏计分
bit Glife = 1;				//游戏生命
bit sound_ON = 1;			//音效开关
uint8 data duty = 80;		//PWM，默认亮度
uint8 data DispRAM[16]={0};
uint8 code bitman[8]={1,2,4,8,16,32,64,128};//用于数字序号定位0~7bit位

uint8 code num[10][5]=		//阳码
{
	{0x7,0x5,0x5,0x5,0x7},
	{0x2,0x6,0x2,0x2,0x7},
	{0x7,0x1,0x7,0x4,0x7},
	{0x7,0x1,0x7,0x1,0x7},
	{0x5,0x5,0x7,0x1,0x1},
	{0x7,0x4,0x7,0x1,0x7},
	{0x7,0x4,0x7,0x5,0x7},
	{0x7,0x1,0x1,0x1,0x1},
	{0x7,0x5,0x7,0x5,0x7},
	{0x7,0x5,0x7,0x1,0x7}
};

/*********************PORT_INIT********************/
void Port_Init()
{
	P0M0 = 0Xff;
	P0M1 = 0X00;
	P1M0 = 0Xff;
	P1M1 = 0X00;
	P2M0 = 0Xff;
	P2M1 = 0X00;
	P3M0 = 0X00;
	P3M1 = 0X00;
	P4M0 = 0Xff;
	P4M1 = 0X00;
	P5M0 = 0Xff;
	P5M1 = 0X00;
}

void Init_Timer()
{
/******************定时器0中断设置**********************/
	AUXR |= 0x80;                   //定时器0为1T模式
    TMOD = 0x00;                    //设置定时器为模式0(16位自动重装载)
    TL0 = T1MS;                     //初始化计时值
    TH0 = T1MS >> 8;
    TR0 = 1;                        //定时器0开始计时
    ET0 = 1;                        //使能定时器0中断
	
/*****************外部中断设置*************************/	
	IT0 = 1;                    //设置INT0下降沿触发
    EX0 = 1;                    //使能外部中断INT0
	IT1 = 1;                    //设置INT1下降沿触发
    EX1 = 1;                    //使能外部中断INT1
	INT_CLKO |= 0x70;           //使能INT2,INT3,INT4(EX4 = 1,EX3 = 1,EX2 = 1
	
	EA = 1;	
}

void Array_CLR(uint8 *p)
{
	uint8 i=0;
	while(i!=16)
	{
		p[i] = 0x00;
		i++;
	}
}

void ShowScore(uint score)
{
	uint8 i;
	uint8 qx,bx,sx,gx;
	qx = score /1000;
	bx = score %1000 /100;
	sx = score %100/10;
	gx = score %10;

	Array_CLR(DispRAM);

	for(i=0;i<5;i++)
		DispRAM[8-i] = (num[sx][i]<<4) | (num[gx][i]);
	
	for(i=0;i<5;i++)
		DispRAM[14-i] = (num[qx][i]<<5) | (num[bx][i]<<1);
				
//	MatxDisp(DispRAM,duty);
}

void main()
{
	Port_Init();
	Sound_Init();
	Init_Timer();
	Sound_Tone(1,14,5);//滴
	
	srand(TL0);		
	delayms(100);
	Play_Music(sound_game_start);
	Flash_Screen_Clear();
	while(1) 
	{
		tms = 0;
		keypad = K_NULL;//清除按键状态
		switch (GUI_Main())	//进入用户游戏选择界面，返回选择的游戏
		{
			case 1:	Tetris_Game();	break;
			case 2:	Snake_Game();	break;
			case 3:	RAC_Game();		break;
			case 4:	Shot_Game();	break;
		}
		Play_Music(sound_game_over);
		Flash_Screen_Clear();
		ShowScore(scores);	//将分数载入显存
		delayms(300);
		
		keypad = K_NULL;
		while(keypad != K_UP)	//在没按下OK键时保持分数显示
		{
			MatxDisp(DispRAM,duty);
			SMG_Display(scores,duty);
		}
	}	
}

/* Timer0 interrupt routine */
void T0_Timer_1ms_int() interrupt 1 using 1
{
	if(tms<0xfffe)	tms++;	//防止溢出
	if(key_state){ if(!--keycont) key_state=0;}

	if(PIN_TR2)//TR2如果打开，则开始播放音效
	{
		if(!sound_cnt_time--)
		{
			TR2_OFF;
			beep = 1;
			if(music_p[s_p][1])
			{
				Sound_Tone(sound_ON,music_p[s_p][0],music_p[s_p][1]);
				s_p++; //自动装载下一个音符，实现音效与游戏“同时”运行
			}
		}
	}
	if(KEY_DOWN==0 & KEY_UP==0)	IAP_CONTR=0x60;//软件复位下载程序
}

void T2_Timer_Sound_freq() interrupt 12           //中断入口
{
     beep = ~beep; //蜂鸣器频率震动
}

uint8 Get_Kvuale(uint8 key_delay)//键值消抖处理，参数为灵敏度调节
{
	uint8 kvuale = K_NULL;	//返回的初始值为空值
	if(keypad != K_NULL)	//当键值不为NULL时,说明有按键按下
	{	
		if(!key_state)		//当按键状态位state为0时说明是第一次触发有效,为1时为重复触发
		{
			key_state=1;	//置1，防止重复触发
			kvuale = keypad;//获得读取键值
			keycont = key_delay;//载入消抖时间
		}
		keypad = K_NULL;	//清楚键值
	}
	return kvuale;
}
/*********外部中断按键区**********/
void exint0() interrupt 0       //INT0
{
	keypad = 0;
}
void exint1() interrupt 2       //INT1
{
	keypad = 1;	
}
void exint2() interrupt 10      //INT2
{
	keypad = 2;
}
void exint3() interrupt 11      //INT3
{
	keypad = 3;
}
void exint4() interrupt 16      //INT4
{	
	keypad = 4;
}


