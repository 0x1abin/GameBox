#include "config.h"


#define A	0
#define B	1
#define ON	1	//共阴
void Data_CLR(bit ab)	//硬件上的原因，点阵共阳，数码管共阴,所以带参
{
	LED_D0 = ab;LED_D1 = ab;LED_D2 = ab;LED_D3 = ab;
	LED_D4 = ab;LED_D5 = ab;LED_D6 = ab;LED_D7 = ab;
}

void ROW_data(uint8 rdata)//行选择模块
{
	switch (rdata)
	{		
		case 0 :LED_R16 = 0; LED_R1 = 1;	break;
		case 1 :LED_R1	= 0; LED_R2 = 1;	break;
		case 2 :LED_R2	= 0; LED_R3 = 1;	break;
		case 3 :LED_R3	= 0; LED_R4 = 1;	break;
		case 4 :LED_R4	= 0; LED_R5 = 1;	break;
		case 5 :LED_R5	= 0; LED_R6 = 1;	break;
		case 6 :LED_R6	= 0; LED_R7 = 1;	break;
		case 7 :LED_R7	= 0; LED_R8 = 1;	break;
		
		case 8 :LED_R8	= 0; LED_R9 = 1;	break;
		case 9 :LED_R9	= 0; LED_R10= 1;	break;
		case 10:LED_R10	= 0; LED_R11= 1;	break;
		case 11:LED_R11	= 0; LED_R12= 1;	break;
		case 12:LED_R12	= 0; LED_R13= 1;	break;
		case 13:LED_R13	= 0; LED_R14= 1;	break;
		case 14:LED_R14	= 0; LED_R15= 1;	break;
		case 15:LED_R15	= 0; LED_R16= 1;	break;
		
		case 0xff:	LED_R1 = 1;LED_R2 = 1;LED_R3 = 1;LED_R4 = 1;
					LED_R5 = 1;LED_R6 = 1;LED_R7 = 1;LED_R8 = 1;
					LED_R9 = 1;LED_R10= 1;LED_R11= 1;LED_R12= 1;
					LED_R13= 1;LED_R14= 1;LED_R15= 1;LED_R16= 1;	
					break;	//0xff全选模式
		default:	LED_R1 = 0;LED_R2 = 0;LED_R3 = 0;LED_R4 = 0;
					LED_R5 = 0;LED_R6 = 0;LED_R7 = 0;LED_R8 = 0;
					LED_R9 = 0;LED_R10= 0;LED_R11= 0;LED_R12= 0;
					LED_R13= 0;LED_R14= 0;LED_R15= 0;LED_R16= 0;	
					break;	//其他关闭所以列选
	}
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

void Tns(uint8 n)//短暂延时
{
	while(n--);
}

void MatxDisp(uint8 *buf,uint8 duty)
{
	uint8 p,i;
	bit b;
	SMG_S1 = 1; SMG_S2 = 1; SMG_S3 = 1;
	Data_CLR(B);
	#define LED_OFF	 1;
	for(p=0;p<16;p++)
	{
		ROW_data(p);
		for(i=0;i<8;i++)
		{
			b = ~(bit)(buf[p] & bitman[i]);//共阳取反
			switch (i)
			{
				case 0:	LED_D7 = LED_OFF; Tns(100-duty); LED_D0 = b;	break;
				case 1:	LED_D0 = LED_OFF; Tns(100-duty); LED_D1 = b;	break;
				case 2:	LED_D1 = LED_OFF; Tns(100-duty); LED_D2 = b;	break;
				case 3:	LED_D2 = LED_OFF; Tns(100-duty); LED_D3 = b;	break;
				case 4:	LED_D3 = LED_OFF; Tns(100-duty); LED_D4 = b;	break;
				case 5:	LED_D4 = LED_OFF; Tns(100-duty); LED_D5 = b;	break;
				case 6:	LED_D5 = LED_OFF; Tns(100-duty); LED_D6 = b;	break;
				case 7:	LED_D6 = LED_OFF; Tns(100-duty); LED_D7 = b;	break;
				default: break;
			}
			Tns(duty);
		}
		LED_D7 = 1;		
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
