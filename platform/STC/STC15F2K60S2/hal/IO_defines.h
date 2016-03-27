#ifndef _IO_DEFINES_H_
#define _IO_DEFINES_H_

#include "common.h"

/*====================================

		 COL  1 2 3 4 5 6 7 8 
			 -----------------
		 A1 | x x x x x x x x |
		 A2 | x x x x x x x x |
		 A3 | x x x x x x x x |
		 A4 | x x x x x x x x |
		 A5 | x x x x x x x x |
		 A6 | x x x x x x x x |
		 A7 | x x x x x x x x |
		 A8 | x x x x x x x x |
		 ROW -----------------
		 
		 COL  1 2 3 4 5 6 7 8 
			 -----------------	 
		 B1 | x x x x x x x x |
		 B2 | x x x x x x x x |
		 B3 | x x x x x x x x |
		 B4 | x x x x x x x x |
		 B5 | x x x x x x x x |
		 B6 | x x x x x x x x |
		 B7 | x x x x x x x x |
		 B8 | x x x x x x x x |
		 ROW -----------------
 
=====================================*/


/*====================== LED PIN Defines ==========================*/
sbit LED_A_PIN1 = P0^0;
sbit LED_A_PIN2 = P0^1;
sbit LED_A_PIN3 = P2^0;
sbit LED_A_PIN4 = P4^4;
sbit LED_A_PIN5 = P0^2;
sbit LED_A_PIN6 = P4^3;
sbit LED_A_PIN7 = P0^3;
sbit LED_A_PIN8 = P0^4;
sbit LED_A_PIN9  = P2^6;
sbit LED_A_PIN10 = P2^1;
sbit LED_A_PIN11 = P2^2;
sbit LED_A_PIN12 = P2^7;
sbit LED_A_PIN13 = P2^4;
sbit LED_A_PIN14 = P4^5;
sbit LED_A_PIN15 = P4^1;
sbit LED_A_PIN16 = P4^6;

sbit LED_B_PIN1 = P1^0;
sbit LED_B_PIN2 = P1^1;
sbit LED_B_PIN3 = P2^0;
sbit LED_B_PIN4 = P4^4;
sbit LED_B_PIN5 = P4^7;
sbit LED_B_PIN6 = P4^3;
sbit LED_B_PIN7 = P1^2;
sbit LED_B_PIN8 = P1^3;
sbit LED_B_PIN9  = P0^5;
sbit LED_B_PIN10 = P2^1;
sbit LED_B_PIN11 = P2^2;
sbit LED_B_PIN12 = P0^6;
sbit LED_B_PIN13 = P2^4;
sbit LED_B_PIN14 = P0^7;
sbit LED_B_PIN15 = P4^1;
sbit LED_B_PIN16 = P4^6;

//PxM0.n,PxM1.n 	=00--->Standard,	10--->push-pull
//					=01--->pure input,	11--->open drain
//PxM0.n,PxM1.n 	=00--->Standard,	10--->push-pull
//					=01--->pure input,	11--->open drain

//为了方便，所以LED口都并口设置为推挽模式
#define SET_OUT_PUSH_LED_P0		{P0M0 = 0XFF; P0M1 = 0X00;}
#define SET_OUT_PUSH_LED_P1		{P1M0 = 0XFF; P1M1 = 0X00;}
#define SET_OUT_PUSH_LED_P2		{P2M0 = 0XFF; P2M1 = 0X00;}
#define SET_OUT_PUSH_LED_P4		{P4M0 = 0XFF; P4M1 = 0X00;}

/*==============================================*/
#define LED_COL_1		LED_A_PIN16
#define LED_COL_2		LED_A_PIN15
#define LED_COL_3		LED_A_PIN11
#define LED_COL_4		LED_A_PIN6
#define LED_COL_5		LED_A_PIN10
#define LED_COL_6		LED_A_PIN4
#define LED_COL_7		LED_A_PIN3
#define LED_COL_8		LED_A_PIN13

#define LED_ROW_A1		LED_A_PIN9
#define LED_ROW_A2		LED_A_PIN14
#define LED_ROW_A3		LED_A_PIN8
#define LED_ROW_A4		LED_A_PIN12
#define LED_ROW_A5		LED_A_PIN1
#define LED_ROW_A6		LED_A_PIN7
#define LED_ROW_A7		LED_A_PIN2
#define LED_ROW_A8		LED_A_PIN5
#define LED_ROW_B1		LED_B_PIN9
#define LED_ROW_B2		LED_B_PIN14
#define LED_ROW_B3		LED_B_PIN8
#define LED_ROW_B4		LED_B_PIN12
#define LED_ROW_B5		LED_B_PIN1
#define LED_ROW_B6		LED_B_PIN7
#define LED_ROW_B7		LED_B_PIN2
#define LED_ROW_B8		LED_B_PIN5
/*==============================================*/
#define HIGH				1
#define LOW					0

#define COL_ON				LOW
#define COL_OFF				HIGH
#define ROW_ON				HIGH
#define ROW_OFF				LOW
/*---------------------------------------------*/
#define LED_COL_1_ON		LED_COL_1 = COL_ON
#define LED_COL_2_ON		LED_COL_2 = COL_ON
#define LED_COL_3_ON		LED_COL_3 = COL_ON
#define LED_COL_4_ON		LED_COL_4 = COL_ON
#define LED_COL_5_ON		LED_COL_5 = COL_ON
#define LED_COL_6_ON		LED_COL_6 = COL_ON
#define LED_COL_7_ON		LED_COL_7 = COL_ON
#define LED_COL_8_ON		LED_COL_8 = COL_ON

#define LED_COL_1_OFF		LED_COL_1 = COL_OFF
#define LED_COL_2_OFF		LED_COL_2 = COL_OFF
#define LED_COL_3_OFF		LED_COL_3 = COL_OFF
#define LED_COL_4_OFF		LED_COL_4 = COL_OFF
#define LED_COL_5_OFF		LED_COL_5 = COL_OFF
#define LED_COL_6_OFF		LED_COL_6 = COL_OFF
#define LED_COL_7_OFF		LED_COL_7 = COL_OFF
#define LED_COL_8_OFF		LED_COL_8 = COL_OFF
/*==============================================*/
#define LED_ROW_A1_ON		LED_ROW_A1 = ROW_ON
#define LED_ROW_A2_ON		LED_ROW_A2 = ROW_ON
#define LED_ROW_A3_ON		LED_ROW_A3 = ROW_ON
#define LED_ROW_A4_ON		LED_ROW_A4 = ROW_ON
#define LED_ROW_A5_ON		LED_ROW_A5 = ROW_ON
#define LED_ROW_A6_ON		LED_ROW_A6 = ROW_ON
#define LED_ROW_A7_ON		LED_ROW_A7 = ROW_ON
#define LED_ROW_A8_ON		LED_ROW_A8 = ROW_ON
#define LED_ROW_B1_ON		LED_ROW_B1 = ROW_ON
#define LED_ROW_B2_ON		LED_ROW_B2 = ROW_ON
#define LED_ROW_B3_ON		LED_ROW_B3 = ROW_ON
#define LED_ROW_B4_ON		LED_ROW_B4 = ROW_ON
#define LED_ROW_B5_ON		LED_ROW_B5 = ROW_ON
#define LED_ROW_B6_ON		LED_ROW_B6 = ROW_ON
#define LED_ROW_B7_ON		LED_ROW_B7 = ROW_ON
#define LED_ROW_B8_ON		LED_ROW_B8 = ROW_ON

#define LED_ROW_A1_OFF		LED_ROW_A1 = ROW_OFF
#define LED_ROW_A2_OFF		LED_ROW_A2 = ROW_OFF
#define LED_ROW_A3_OFF		LED_ROW_A3 = ROW_OFF
#define LED_ROW_A4_OFF		LED_ROW_A4 = ROW_OFF
#define LED_ROW_A5_OFF		LED_ROW_A5 = ROW_OFF
#define LED_ROW_A6_OFF		LED_ROW_A6 = ROW_OFF
#define LED_ROW_A7_OFF		LED_ROW_A7 = ROW_OFF
#define LED_ROW_A8_OFF		LED_ROW_A8 = ROW_OFF
#define LED_ROW_B1_OFF		LED_ROW_B1 = ROW_OFF
#define LED_ROW_B2_OFF		LED_ROW_B2 = ROW_OFF
#define LED_ROW_B3_OFF		LED_ROW_B3 = ROW_OFF
#define LED_ROW_B4_OFF		LED_ROW_B4 = ROW_OFF
#define LED_ROW_B5_OFF		LED_ROW_B5 = ROW_OFF
#define LED_ROW_B6_OFF		LED_ROW_B6 = ROW_OFF
#define LED_ROW_B7_OFF		LED_ROW_B7 = ROW_OFF
#define LED_ROW_B8_OFF		LED_ROW_B8 = ROW_OFF



/*====================== Keypad PIN Defines ==========================*/
sbit KEY_UP	   = P3^2;	
sbit KEY_DOWN  = P3^6;
sbit KEY_LEFT  = P3^0;
sbit KEY_RIGHT = P3^3;
sbit KEY_A     = P3^7;

//PxM0.n,PxM1.n 	=00--->Standard,	10--->push-pull
//					=01--->pure input,	11--->open drain
//PxM0.n,PxM1.n 	=00--->Standard,	10--->push-pull
//					=01--->pure input,	11--->open drain
#define SET_IN_KEY_UP		{P3M0 &= ~0xcd; P3M1 |= 0xcd;}
#define SET_IN_KEY_DOWN
#define SET_IN_KEY_LEFT
#define SET_IN_KEY_RIGHT
#define SET_IN_KEY_A	


#define GET_KEYPAD_UP		KEY_UP
#define GET_KEYPAD_DOWN		KEY_DOWN
#define GET_KEYPAD_LEFT		KEY_LEFT
#define GET_KEYPAD_RIGHT	KEY_RIGHT
#define GET_KEYPAD_A		KEY_A


#endif