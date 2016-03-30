/*
//作者：郑梓滨	Jaupin@126.com
//日期：2014年10月27日14:04:35   
//功能：复古掌上俄罗斯方块游戏机源代码，包括游戏GUI，俄罗斯方块、贪吃蛇、经典赛车游戏、射击障碍物游戏
v1.0:
	2014-7-26  00:00:00	:完成有俄罗斯方块游戏基本模型;
	2014-7-28  02:12:03	:将原先临时使用的延时键盘扫描改为外部中断状态位检测键;
	2014-7-28  20:40:37	:完成俄罗斯方块分数计数及分数显示功能;
	2014-8-1   01:01:54	:将较早之前完成贪吃蛇游戏代码合并植入;
	2014-8-2   17:04:25	:整理之前的临时源码,使工程文件规范化;
	2014-8-3   23:50:49	:构建游戏选择画面基本模型,完成画面平移效果;
	2014-8-5   00:50:04	:改进LED点阵底层驱动,用软件PWM调节画面亮度;
	2014-8-7   00:53:35	:完成赛车游戏,用PWM分层扫描画面,形成游戏画面对比度;
	2014-8-8   02:16:44	:完成赛车游戏选择预览画面,并将三个游戏合并在一起;
	2014-8-12  01:47:07	:将逐行扫描改为逐点扫描,使显示亮度均匀;增加亮度调节功能;
	2014-9-9   00:32:40	:修改及优化若干细节；
v1.1:
	2014-9-18  0:57:23	:重新布局电路，修改原先不合理的地方，为制作PCB板作准备；
	2014-9-19  22:02:36	:加入游戏音效，并且可以通过软件方式开关声音；
	2014-9-21  14:59:39	:增加三位mini数码管，实时显示游戏分数，数码管共用点阵并行数据口；
	2014-10-20 21:30:15	:加入射击游戏,将GUI模块化，简化流程
	
v2.0:
	2016-3-27  16:35:46 :全新更成熟程序结构，简化逻辑三层程序结构，更好的可读性和扩展性。
*/

#include "gamebox.h"


enum
{	
	STA_STARTUP = 0,
	STA_WELCOME_SCREEN,
	STA_SELECTION_MENU,
	STA_INITIALIZE_GAME,
	STA_PLAY_GAME,
	STA_GAMEOVER
}MAIN_STATE

enum
{
	TETRIS = 0,
	SNAKE,
	RAC,
	SHOT,
	Numbers_Of_Game
}GameName;

typedef struct
{
	uint8_t state;
	void (*pGameInit)(void);
	void (*pGamePlay)(void);
	void (*pGameEnd)(void);
	uint8_t preview[4][8];
	uint8_t *pBGMusic;
}GAME_T;

GAME_T gamelist[Numbers_Of_Game];


uint8 whichGame = 0;
uint8 mainstate = STA_STARTUP;


/**
  * @brief  Hal_Init.
  * @param  None.
  * @retval None.
  */
void Hal_Init()
{
	HAL_TimerInit();
	HAL_KeypadInit();
	HAL_Matrix();
	HAL_Buzer();
}

/**
  * @brief  API_Init.
  * @param  None.
  * @retval None.
  */
void API_Init()
{
	Display_init();
	keypad_init();
}

/**
  * @brief  main func.
  * @param  None.
  * @retval None.
  */
void main()
{
	Hal_Init();
	
	API_Init();
	
	Test_mode();
	
	while(1)
	{
		switch (mainstate)
		{
			case STA_STARTUP:
			
				mainstate = STA_WELCOME_SCREEN;
				break;
				
			case STA_WELCOME_SCREEN:
				
				mainstate = STA_SELECTION_MENU;
				break;		
			
			case STA_SELECTION_MENU:
				GamePreview(&gamelist[].preview[][]);
				
				if(whichGame != 0xff)
				{
					mainstate = STA_INITIALIZE_GAME;
				}
				break;
			
			case STA_INITIALIZE_GAME:
				gamelist[whichGame].pGameInit();
				
				mainstate = STA_PLAY_GAME;
				break;
				
			case STA_PLAY_GAME:
				gamelist[whichGame].pGamePlay();
				
				if(gamelist[whichGame].state == GAMEOVER)
				{
					mainstate = STA_GAMEOVER;
				}
				break;
			
			case STA_GAMEOVER:
				gamelist[whichGame].pGameEnd();
				
				mainstate = STA_SELECTION_MENU;
				break;
		}//end main switch
		
	}
}

/**
  * @brief  Register the games.
  * @param  None.
  * @retval None.
  */
void Register_Game(GameName name, void (*pGameInit)(), void (*pGamePlay)(), void (*pGameEnd)())
{
	
}

/**
  * @brief  Register the game background music.
  * @param  None.
  * @retval None.
  */
void Register_Music(GameName name, uint8_t preview, uint8_t length)
{
	
}

/**
  * @brief  Register the game preview frames.
  * @param  None.
  * @retval None.
  */
void Register_Preview(GameName name, uint8_t *preview)
{
	
}

/**
  * @brief  Hal timer callbock 1ms once.
  * @param  None.
  * @retval None.
  */
void HAL_Timer_Callback()
{
	TimerUpdate();
}















