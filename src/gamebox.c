#include "gamebox.h"

uint8_t mem_pool[512];
uint8 whichGame = 0;
uint8 mainstate = STA_STARTUP;

enum
{	
	STA_STARTUP = 0,
	STA_WELCOME_SCREEN,
	STA_SELECTION_MENU,
	STA_INITIALIZE_GAME,
	STA_PLAY_GAME,
	STA_GAMEOVER
}MAIN_STATE

enum {
	Tank = 0,
	TETRIS,
	SNAKE,
	RAC,
	SHOT,
	Number_Of_Games
} GameName;



typedef struct {
	uint8_t state;
	void (*pGameInit)(void);
	void (*pGamePlay)(void);
	void (*pGameEnd)(void);
	uint8_t (*preview)[8];
	uint8_t (*pBGMusic)[2];
} GameObject;


static GameObject *gamelist[Number_Of_Games];



/**
  * @brief  Register the games.
  * @param  None.
  * @retval None.
  */
void Game_Register(GameName name, GameObject *game_obj)
{
	gamelist[name] = game_obj;
}




void Game_Preview(GameName name)
{

}

void GameBox_Run()
{
	while(1) {
		switch (mainstate) {
		case STA_STARTUP:

			mainstate = STA_WELCOME_SCREEN;
			break;

		case STA_WELCOME_SCREEN:

			mainstate = STA_SELECTION_MENU;
			break;

		case STA_SELECTION_MENU:
			Game_Preview(whichGame);

			if(whichGame != 0xff) {
				mainstate = STA_INITIALIZE_GAME;
			}
			break;

		case STA_INITIALIZE_GAME:
			gamelist[whichGame]->pGameInit();

			mainstate = STA_PLAY_GAME;
			break;

		case STA_PLAY_GAME:
			gamelist[whichGame]->pGamePlay();

			if(gamelist[whichGame].state == GAMEOVER) {
				mainstate = STA_GAMEOVER;
			}
			break;

		case STA_GAMEOVER:
			gamelist[whichGame]->pGameEnd();

			mainstate = STA_SELECTION_MENU;
			break;
		}//end main switch

	}
}