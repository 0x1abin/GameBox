#include "config.h"
#include "IO_defines.h"

uint8 buffer[16];

void Tns(uint8 n)//短暂延时
{
	while(n--);
}

void Display_Init()
{
	
}

void Select_Row(uint8 row)
{
	switch (row)
	{
		case 0:
			// LED_ROW_A1_OFF;
			LED_ROW_B8_ON;
			break;
		case 1:
			LED_ROW_B8_OFF;
			LED_ROW_B7_ON;
			break;
		case 2:
			LED_ROW_B7_OFF;
			LED_ROW_B6_ON;
			break;
		case 3:
			LED_ROW_B6_OFF;
			LED_ROW_B5_ON;
			break;
		case 4:
			LED_ROW_B5_OFF;
			LED_ROW_B4_ON;
			break;
		case 5:
			LED_ROW_B4_OFF;
			LED_ROW_B3_ON;
			break;
		case 6:
			LED_ROW_B3_OFF;
			LED_ROW_B2_ON;
			break;
		case 7:
			LED_ROW_B2_OFF;
			LED_ROW_B1_ON;
			break;
		case 8:
			LED_ROW_B1_OFF;
			LED_ROW_A8_ON;
			break;
		case 9:
			LED_ROW_A8_OFF;
			LED_ROW_A7_ON;
			break;
		case 10:
			LED_ROW_A7_OFF;
			LED_ROW_A6_ON;
			break;
		case 11:
			LED_ROW_A6_OFF;
			LED_ROW_A5_ON;
			break;
		case 12:
			LED_ROW_A5_OFF;
			LED_ROW_A4_ON;
			break;
		case 13:
			LED_ROW_A4_OFF;
			LED_ROW_A3_ON;
			break;
		case 14:
			LED_ROW_A3_OFF;
			LED_ROW_A2_ON;
			break;
		case 15:
			LED_ROW_A2_OFF;
			LED_ROW_A1_ON;
			break;	
		default:
			LED_ROW_A1_OFF;
			LED_ROW_A2_OFF;
			LED_ROW_A3_OFF;
			LED_ROW_A4_OFF;
			LED_ROW_A5_OFF;
			LED_ROW_A6_OFF;
			LED_ROW_A7_OFF;
			LED_ROW_A8_OFF;
			LED_ROW_B1_OFF;
			LED_ROW_B2_OFF;
			LED_ROW_B3_OFF;
			LED_ROW_B4_OFF;
			LED_ROW_B5_OFF;
			LED_ROW_B6_OFF;
			LED_ROW_B7_OFF;
			LED_ROW_B8_OFF;
			break;		
	}
}

void Display_Now()
{
	uint8 x,y,tmp;
	for(y=0; y<16; y++)
	{
		tmp = buffer[y];
		Select_Row(y);
		for(x=1;x<9;x++)
		{
			switch (x)
			{
				case 1:
//					LED_COL_8_OFF;
					if(tmp & 0x01)
						LED_COL_1_ON;
					else
						LED_COL_1_OFF;
					break;
					
				case 2:
					LED_COL_1_OFF;
					if(tmp & 0x01)
						LED_COL_2_ON;
					else
						LED_COL_2_OFF;
					break;
					
				case 3:
					LED_COL_2_OFF;
					if(tmp & 0x01)
						LED_COL_3_ON;
					else
						LED_COL_3_OFF;
					break;
					
				case 4:
					LED_COL_3_OFF;
					if(tmp & 0x01)
						LED_COL_4_ON;
					else
						LED_COL_4_OFF;
					break;
					
				case 5:
					LED_COL_4_OFF;
					if(tmp & 0x01)
						LED_COL_5_ON;
					else
						LED_COL_5_OFF;
					break;
					
				case 6:
					LED_COL_5_OFF;
					if(tmp & 0x01)
						LED_COL_6_ON;
					else
						LED_COL_6_OFF;
					break;
					
				case 7:
					LED_COL_6_OFF;
					if(tmp & 0x01)
						LED_COL_7_ON;
					else
						LED_COL_7_OFF;
					break;
					
				case 8:
					LED_COL_7_OFF;
					if(tmp & 0x01)
						LED_COL_8_ON;
					else
						LED_COL_8_OFF;
					break;
			}
			// Tns(duty);
			tmp >>= 1;
		}
		LED_COL_8_OFF;
	}
	LED_ROW_A1_OFF;
}




void DisPoint(uint8 x,uint8 y)
{
	#define L_ON 0
	ROW_data(88);	//清除
	Data_CLR(B);
	
	ROW_data(y);	//行选择
	switch (x)
	{
		case 0:	LED_D0 = L_ON;	break;
		case 1:	LED_D1 = L_ON;	break;
		case 2:	LED_D2 = L_ON;	break;
		case 3:	LED_D3 = L_ON;	break;
		case 4:	LED_D4 = L_ON;	break;
		case 5:	LED_D5 = L_ON;	break;
		case 6:	LED_D6 = L_ON;	break;
		case 7:	LED_D7 = L_ON;	break;
	}
}

void SMG_Num(uint8 n)	//数码管段码
{
	switch (n)
	{
		case 0:	SMG_A = ON; SMG_B = ON; SMG_C = ON; SMG_D = ON; SMG_E = ON; SMG_F = ON;
			break;
		case 1: SMG_B = ON; SMG_C = ON;
			break;
		case 2:	SMG_A = ON; SMG_B = ON; SMG_D = ON; SMG_E = ON; SMG_G = ON;
			break;
		case 3:	SMG_A = ON; SMG_B = ON; SMG_C = ON; SMG_D = ON; SMG_G = ON;
			break;
		case 4: SMG_B = ON; SMG_C = ON; SMG_F = ON; SMG_G = ON;
			break;
		case 5:	SMG_A = ON; SMG_C = ON; SMG_D = ON; SMG_F = ON; SMG_G = ON;
			break;
		case 6:	SMG_A = ON; SMG_C = ON; SMG_D = ON; SMG_E = ON; SMG_F = ON; SMG_G = ON;
			break;
		case 7:	SMG_A = ON; SMG_B = ON; SMG_C = ON;
			break;
		case 8:	SMG_A = ON; SMG_B = ON; SMG_C = ON; SMG_D = ON; SMG_E = ON; SMG_F = ON; SMG_G = ON;
			break;
		case 9:	SMG_A = ON; SMG_B = ON; SMG_C = ON; SMG_D = ON; SMG_F = ON; SMG_G = ON;
			break;
	}
}
void SMG_Display(uint16 goal,uint8 duty)
{
	
	ROW_data(88);//屏蔽点阵
	
	Data_CLR(A);
	Tns(100-duty);
	SMG_S1 = 0;
	SMG_Num(goal/100);
	Tns(duty);
	
	Data_CLR(A);
	Tns(100-duty);
	SMG_S1 = 1; SMG_S2 = 0; 
	SMG_Num(goal/10%10);
	Tns(duty);
	
	Data_CLR(A);
	Tns(100-duty);
	SMG_S2 = 1; SMG_S3 = 0;
	SMG_Num(goal%10);
	Tns(duty);
	
	SMG_S3 = 1;
}
