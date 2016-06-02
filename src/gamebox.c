#include "gamebox.h"

uint8_t mem_pool[512];

enum
{
	Tank = 0,
	TETRIS,
	SNAKE,
	RAC,
	SHOT,
	Numbers_Of_Games
}GameName;


typedef struct
{
	uint8_t state;
	void (*pGameInit)(void);
	void (*pGamePlay)(void);
	void (*pGameEnd)(void);
	uint8_t (*preview)[8];
	uint8_t (*pBGMusic)[2];
}GameObject;


static GameObject *gamelist[Numbers_Of_Games];




/**
  * @brief  Register the games.
  * @param  None.
  * @retval None.
  */
void Register_Game(GameName name, GameObject *game_obj)
{
	gamelist[name] = game_obj;
}



void Game_Init(GameName name)
{
    gamelist[name]->pGameInit();
}

void Game_Play(GameName name)
{
    gamelist[name]->pGamePlay();
}

void Game_End(GameName name)
{
    gamelist[name]->pGameEnd();
}

void Game_Preview(GameName name)
{
   
}