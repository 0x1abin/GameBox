
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