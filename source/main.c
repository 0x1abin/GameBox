#include "common.h"
// #include "config.h"

#define RESET_SYSTEM		{IAP_CONTR=0x60;}
#define IRQ_ENABLE			EA = 1
#define IRQ_DISABLE			EA = 0

#define STA_WELCOME_SCREEN		1
#define STA_SELECTION_MENU		2
#define STA_INITIALIZE_GAME		3
#define STA_PLAY_GAME			4
#define STA_GAMEOVER			5


uint8 imbuff[16] = 0;
uint8 which_game = 0;
uint8 mainstate = STA_WELCOME_SCREEN;
BOOL gameover_flg = 0;

void buffcpy(uint8 *dest, uint8 pt, const uint8 *src, uint8 length)
{
	uint8 i,p;
	for(i=0,p=pt; p < ((pt+length)>16 ? 16:(pt+length)); i++,p++)
	{
		dest[p] = src[i];
	}
}

void buffcpy_16byte(uint8 *dest, const uint8 *src)
{
	uint8 i;
	for(i=0; i<16; i++)
	{
		dest[i] = src[i];
	}
}

void clear(uint8 *buf)
{
	uint8 i;
	for(i=0; i<16; i++)
	{
		buf[i] = 0;
	}
}

void refresh()
{
	uint8 i;
	for(i=0; i<16; i++)
	{
		xbuff[i] = imbuff[i];
	}
}


void Timer0Init(void)	//1毫秒@24.000MHz
{
	AUXR |= 0x80;		//定时器时钟1T模式
	TMOD &= 0xF0;		//设置定时器模式
	TL0 = 0x40;			//设置定时初值
	TH0 = 0xA2;			//设置定时初值
	TF0 = 0;			//清除TF0标志
	TR0 = 1;			//定时器0开始计时
	
	ET0 = 1;        	//使能定时器0中断
	// EA = 1;
}

void Test_mode()
{
	code uint8 S_Logo[8]={0x00,0x19,0x2A,0xC8,0x8B,0xC8,0x2A,0x19};
	code uint8 S_ON[8]={0x00,0x00,0x42,0x62,0x52,0x4A,0x46,0x42};/*ON*/
	
	uint8 i;
	
	clear(imbuff);
	// for(i=0; i<8; i++)
	// {
		// imbuff[i] = S_ON[i];
	// }
	
	// for(i=0; i<8; i++)
	// {
		// imbuff[i+7] = S_Logo[i];
	// }
	
	buffcpy(imbuff, 8, S_Logo, sizeof(S_Logo));
	
	buffcpy(imbuff, 0, S_ON, sizeof(S_ON));
	
	
} 

void main()
{
	IRQ_DISABLE;
	
	Timer0Init();
	Display_init();
	keypad_init();
	
	Test_mode();
	IRQ_ENABLE;
	
	while(1)
	{
		switch (mainstate)
		{
			case STA_WELCOME_SCREEN:
			{
				
				mainstate = STA_SELECTION_MENU;
				break;		
			}
			
			case STA_SELECTION_MENU:
			{
				if(which_game != 0)
				{
					mainstate = STA_INITIALIZE_GAME;
				}	
				break;
			}
			
			case STA_INITIALIZE_GAME:
			{
				switch (which_game)
				{
					case 1:
					
						break;
						
					case 2:
					
						break;
						
					case 3:
					
						break;
				}
				mainstate = STA_PLAY_GAME;
				break;
			}
				
			case STA_PLAY_GAME:
			{
				switch (which_game)
				{
					case 1:
					
						break;
						
					case 2:
					
						break;
						
					case 3:
					
						break;
				}
				
				if(gameover_flg)
				{
					mainstate = STA_GAMEOVER;
				}
				break;
			}
			
			case STA_GAMEOVER:
			{
				
				mainstate = STA_SELECTION_MENU;
			}
				
		}
		
		refresh();
	}
}


/* Timer0 interrupt routine */
void tm0_isr() interrupt 1
{
	if(!RXD) RESET_SYSTEM;//自动下载
	
	IRQ_DISABLE;
	
	Display_now();
	Keypad_scan_poll();
	
	IRQ_ENABLE;
}















