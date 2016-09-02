

#include "Tank.h"

#define X_WIDTH_MIN     0
#define Y_WIDTH_MIN     0

#define X_WIDTH_MAX     7
#define Y_WIDTH_MAX     15


//坦克序号0，是我自己的坦克
#define MY_TANK     0

#define MAX_TANKS   4

const uint8_t utank_bitmap[4][3] = {
	B01000000,
	B11100000,
	B11100000,
	//UP

	B11100000,
	B11100000,
	B01000000,
	//DOWN

	B01100000,
	B11100000,
	B01100000,
	//LEFT

	B11000000,
	B11100000,
	B11000000,
	//RIGHT
}

const uint8_t tank_bitmap[4][3] = {
	B01000000,
	B11100000,
	B10100000,
	//UP

	B10100000,
	B11100000,
	B01000000,
	//DOWN

	B01100000,
	B11000000,
	B01100000,
	//LEFT

	B11000000,
	B01100000,
	B11000000,
	//RIGHT
}

//炮筒坐标偏移量
const x_barrel_offset[] = {1, 1, 0, 2};
const y_barrel_offset[] = {2, 0, 1, 1};

typedef struct _COORD_ {
	int8_t x;
	int8_t y;
} coord_t;

typedef struct _AMMO_ {
	coord_t     pos;
	direction_t direct;
} ammo_t;

typedef struct tank_t {
	uint8_t     state;               //状态
	coord_t     pos;                 //位置
	direction_t direct;              //炮筒朝向
	ammo_t      bullet[MAX_BULLETS]; //子弹
//    uint8_t    bulletNums;
} tank_t;

//bullet
//coord
//position
//direction
//trajectory


static uint8_t nums_of_tanks;
static uint8_t trajeUpdate_handle;
static tank_t tankList_mem[MAX_TANKS];
static tank_t *tankList;

//随机生成坦克
static void RandomGenerateTank()
{
	uint8_t idx = 1;
	if(nums_of_tanks < MAX_TANKS) {
		if(__rand() % 3 == 0) { //三分之一的概率会生成
			nums_of_tanks++;
			while(tankList[idxTank]->state != DEATH) {
				idx++;
			}
			tankList[idx]->state  = ALIVE;
			tankList[idx]->pos.x  = __rand() % 8;
			tankList[idx]->pos.y  = __rand() % 16;
			tankList[idx]->direct = __rand() % 4;
		}
	}
}

//随机射出子弹
static void RandomShotBullet()
{
	uint8_t rand_idx = __rand() % MAX_TANKS + 1;
	if(tankList[rand_idx]->state == ALIVE) {
		ShotOnebullet(rand_idx);
	}
}

//更新弹道处理函数
static void TrajectoryUpdate()
{
	uint8_t idxTank, idxBullet;
	//不管坦克和子弹存不存在都更新一遍，这样能保证本函数时间接近于恒定。
	for(idxTank=0; idxTank<MAX_TANKS; idxTank++) {
		for(idxBullet=0; idxBullet<MAX_BULLETS; idxBullet++) {
			switch (tankList[idxTank]->bullet[idxBullet].direct) {
			case D_RIGHT:
				if(tankList[idxTank]->bullet[idxBullet].pos.x <= X_WIDTH_MAX)
					tankList[idxTank]->bullet[idxBullet].pos.x++;
				break;

			case D_LEFT:
				if(tankList[idxTank]->bullet[idxBullet].pos.x >= X_WIDTH_MIN)
					tankList[idxTank]->bullet[idxBullet].pos.x--;
				break;

			case D_UP:
				if(tankList[idxTank]->bullet[idxBullet].pos.y <= Y_WIDTH_MAX)
					tankList[idxTank]->bullet[idxBullet].pos.y++;
				break;

			case D_DOWN:
				if(tankList[idxTank]->bullet[idxBullet].pos.y = Y_WIDTH_MIN)
					tankList[idxTank]->bullet[idxBullet].pos.y--;
				break;
			}
		}
	}
}

//将坐标绘制成图像
static void DrawingImage()
{
	uint8_t idxTank, idxBullet;

	GUI_Clear();

	//绘画我的坦克
	GUI_DrawBitmap(tankList[MY_TANK]->pos.x, tankList[MY_TANK]->pos.x, utank_bitmap[tankList[MY_TANK]->direct], 3, 3);

	//绘制敌方坦克
	for(idxTank=1; idxTank<MAX_TANKS; idxTank++) {
		if(tankList[idxTank]->state == ALIVE) {
			GUI_DrawBitmap(tankList[idxTank]->pos.x, tankList[idxTank]->pos.x, tank_bitmap[tankList[idxTank]->direct], 3, 3);
		}
	}

	//绘画子弹
	for(idxTank=0; idxTank<MAX_TANKS; idxTank++) {
		for(idxBullet=0; idxBullet<MAX_BULLETS; idxBullet++) {
			GUI_DrawPixel(tankList[idxTank]->bullet[idxBullet].pos.x, tankList[idxTank]->bullet[idxBullet].pos.y);
		}
	}
}

//射出一个子弹
static void ShotOnebullet(uint8_t whickTank)
{
	uint8_t idxBullet = 0;

	do {
		//寻找一个子弹槽发射子弹,射出边界的子弹即为空槽
		if((tankList[idxTank]->bullet[idxBullet].pos.x < X_WIDTH_MIN)  || \
		    (tankList[idxTank]->bullet[idxBullet].pos.x > X_WIDTH_MAX) || \
		    (tankList[idxTank]->bullet[idxBullet].pos.y < Y_WIDTH_MIN) || \
		    (tankList[idxTank]->bullet[idxBullet].pos.y > Y_WIDTH_MAX)) {
			//坦克位置是以本身最左下角的像素点定位的，所以通过偏移量把坐标移到炮筒口
			tankList[whickTank]->bullet[idxBullet].pos.x = \
			 tankList[whickTank]->pos.x + x_barrel_offset[tankList[whickTank]->direct];
			tankList[whickTank]->bullet[idxBullet].pos.y = \
			 tankList[whickTank]->pos.y + y_barrel_offset[tankList[whickTank]->direct];

			//坦克炮筒的朝向即为子弹射出的方向
			tankList[whickTank]->bullet[idxBullet].direct = tankList[whickTank]->direct;

			return;
		}
	} while(++idxBullet < MAX_BULLETS);
	//程序跑到这里表示没有空余的子弹槽了
}

//改变坦克朝向
static void ChangeDirection(uint8_t whickTank, direction_t newDirect)
{
	tankList[whickTank]->direct = newDirect;
}

//往前走一步
static void MoveOneStep(uint8_t whickTank)
{
	switch (tankList[whickTank]->direct) {
	case D_RIGHT:
		if(tankList[whickTank]->pos.x+2 < X_WIDTH_MAX)
			tankList[whickTank]->pos.x++;
		break;

	case D_LEFT:
		if(tankList[whickTank]->pos.x > X_WIDTH_MIN)
			tankList[whickTank]->pos.x--;
		break;

	case D_UP:
		if(tankList[whickTank]->pos.y+2 < Y_WIDTH_MAX)
			tankList[whickTank]->pos.y++;
		break;

	case D_DOWN:
		if(tankList[whickTank]->pos.y > Y_WIDTH_MAX)
			tankList[whickTank]->pos.y--;
		break;
	}
}


//------------------------------------------------------------------------------

void Tank_GameInit()
{
//    *tankList = malloc(sizeof(tank_t) * MAX_TANKS);
	*tankList = mem_pool;
	memset(tankList, 0, sizeof(tank_t) * MAX_TANKS);

	//变量初始化
	nums_of_tanks = 1;

	//初始化坦克位置

	//初始化坦克朝向

	//创建弹道循环更新任务,默认200ms更新一次
	trajeUpdate_handle = TimerCreate(&TrajectoryUpdate, 0,  20);
}


void Tank_GamePlay()
{
	if(Buttons_pressed(BTN_A)) {
		ShotOnebullet(MY_TANK);
	}

	if(Buttons_pressed(BTN_RIGHT)) {
		//如果按下方向按键的方向刚好与坦克的朝向一样，则往前前进一步
		if(tankList[whickTank]->direct == D_RIGHT)
			MoveOneStep(MY_TANK);
		else //否则改变转向
			ChangeDirection(MY_TANK, D_RIGHT);
	}

	if(Buttons_pressed(BTN_LEFT)) {
		if(tankList[whickTank]->direct == D_LEFT)
			MoveOneStep(MY_TANK);
		else
			ChangeDirection(MY_TANK, D_LEFT);
	}
}


void Tank_GameEnd()
{
//    free(tankList);

	TimerDelete(trajeUpdate_handle);
}

//------------------------------------------------------------------------------

const struct GameObject game_tank = {
	.state     = INITIZEAL;
	.pGameInit = Tank_GameInit;
	.pGamePlay = Tank_GamePlay;
	.pGameEnd  = Tank_GameEnd;
	.preview   = array;
	.pBGMusic  = tank_music;
}

//Register_Game(TANK, &game_tank);



