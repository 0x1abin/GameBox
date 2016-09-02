#ifndef _CONFIG_H_
#define _CONFIG_H_

#define FOSC 24000000L
#define T1MS (65536-FOSC/1000)	//1T模式
/*******************include*********************/
#include <stdlib.h>
#include "intrins.h"

#include "STC15F2K60S2.H"
#include "typedef.h"
//#include "common.h"
#include "delay.h"

#include "Display_Drives.h"
#include "Sound_Drives.h"
#include "GUI.h"

#include "Tetris.h"
#include "snake.h"
#include "RAC.h"
#include "Shot.h"

/*******************PIN_CONFIG*********************/
//无源蜂鸣器
sbit beep = P5^5;		
/*******keyborad******/
sbit KEY_UP		=P3^2;	
sbit KEY_DOWN	=P3^6;
sbit KEY_LEFT	=P3^0;
sbit KEY_RIGHT	=P3^3;
sbit KEY_OK		=P3^7;
//exint，按键各接于几号外部中断设置
#define K_UP		0
#define K_DOWN		2
#define K_RIGHT		1
#define K_LEFT		4
#define K_OK		3
#define K_NULL		255	//未触发值
/*******数码管管脚配置********/
sbit SMG_S1 = P2^3;		//数码管位选
sbit SMG_S2 = P2^5;
sbit SMG_S3 = P4^2;

sbit SMG_A = P4^1;
sbit SMG_B = P2^4;
sbit SMG_C = P2^1;
sbit SMG_D = P2^0;
sbit SMG_E = P4^4;
sbit SMG_F = P2^2;
sbit SMG_G = P4^3;
/*********点阵管脚配置*********/
//点阵数据口
sbit LED_D0 = P4^6;
sbit LED_D1 = P4^1;
sbit LED_D2 = P2^2;
sbit LED_D3 = P4^3;
sbit LED_D4 = P2^1;
sbit LED_D5 = P4^4;
sbit LED_D6 = P2^0;
sbit LED_D7 = P2^4;
//点阵行选
sbit LED_R16= P2^6;
sbit LED_R15= P4^5;
sbit LED_R14= P0^4;
sbit LED_R13= P2^7;
sbit LED_R12= P0^0;
sbit LED_R11= P0^3;
sbit LED_R10= P0^1;
sbit LED_R9 = P0^2;
sbit LED_R8 = P0^5;
sbit LED_R7 = P0^7;
sbit LED_R6 = P1^3;
sbit LED_R5 = P0^6;
sbit LED_R4 = P1^0;
sbit LED_R3 = P1^2;
sbit LED_R2 = P1^1;
sbit LED_R1 = P4^7;
/******************通用全局变量*******************/
#define VIEW_FPS		600		//游戏选择画面帧间隔时间
#define SMOVE_SPEED		28		//游戏选择画面画面平移速度

extern volatile uint8 data keypad;	//键盘状态
extern volatile uint16 data scores;	//游戏计分
extern volatile uint8 data keycont;	//键盘检测消抖定时器
extern uint16 data tms;				//1ms T0定时器
extern uint16 data speeds;			//游戏速度
extern uint8 data duty;				//显示占空比
extern bit sound_ON;				//声音开关
extern bit Glife;					//游戏生命
extern uint8 data DispRAM[16];		//显示缓存区
extern uint8 code bitman[8];		//用于数字定位
extern uint8 code num[10][5];

void ShowScore(uint score);
//void Copier(uint8 *dat,uint8 *cpy);
uint8 Get_Kvuale(uint8 key_delay);

#endif