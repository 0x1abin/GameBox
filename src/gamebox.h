

#define X_WIDTH_MIN    0
#define X_WIDTH_MAX    8

#define Y_WIDTH_MIN    0
#define Y_WIDTH_MAX    16


extern uint8_t mem_pool[512];

enum
{
	TETRIS = 0,
	TANK,
	SNAKE,
	RAC,
	SHOT,
	Numbers_Of_Game
}GameName;


struct GameObject
{
	uint8_t state;
	void (*pGameInit)(void);
	void (*pGamePlay)(void);
	void (*pGameEnd)(void);
	uint8_t (*preview_bitmap)[8];
	uint8_t (*pBGMusic)[2];
};