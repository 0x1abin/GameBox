

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

static GAME_T gamelist[Numbers_Of_Game];


/**
  * @brief  Register the games.
  * @param  None.
  * @retval None.
  */
void Register_Game(GameName name, void (*pInit)(), void (*pPlay)(), void (*pEnd)())
{
	gamelist[name].pGameInit = pInit;
	gamelist[name].pGamePlay = pPlay;
	gamelist[name].pGameEnd  = pEnd;
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
	gamelist[name].preview = preview;
}



void Game_Preview(GameName name)
{
   
}

void Game_Init(GameName name)
{
    gamelist[name].pGameInit();
}

void Game_Play(GameName name)
{
    gamelist[name].pGamePlay();
}

void Game_End(GameName name)
{
    gamelist[name].pGameEnd();
}