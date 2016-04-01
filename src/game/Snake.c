/*
	2014-1-26 00:00:00	:完成贪吃蛇游戏模型
	2014-3-8 23:27:05	:增加游戏会随着吃的食物的增加而加快游戏速度
	2014-3-15 20:06:15	:进行实体硬件测剩，运行良好，但贪吃蛇结构设置太耗RAM，将进行优化。
*/
#include "config.h"

#define NORSPEED 360
#define ASPEED 100
#define WIDTH  8	//游戏屏幕宽度
#define LENGTH 16	//游戏屏幕长度 

static struct Food
{
    uint8 x;//食物的横坐标
    uint8 y;//食物的纵坐标
}food;

struct Snake snake;

enum direc{up, down, left, right};//蛇的运动方向

static void Snake_Init();		//初始化游戏
static void Snake_Disp();	//游戏显示
static void Snake_Run();		//蛇向前走一步
static void Create_Food();		//随机生成食物

static void Create_Food()
{
	uint8 i;
	food.x = rand() % WIDTH;	//范围1-16;
	food.y = rand() % LENGTH;	//获得随机数种子;//用计数器作为随机数发生器
	for(i=1;i<(snake.node);i++)//检测产生的食物是否与蛇本身重叠
	{
		if((food.x==snake.x[i])&&(food.y==snake.y[i]))
			Create_Food();	//重叠则重新成生 
	}
}

static void Snake_Init()
{	
	uint8 c;	
	for(c=0;c < MAX_SNAKE;c++)//清除内存数据
	{
		snake.x[c]=-1;
		snake.y[c]=-1;
	}
	snake.life = 1;				//赋予蛇生命
	snake.node = 3;			//默认长度3节
	snake.direc = up;//初始方向
	snake.x[0]=4;
	snake.y[0]=5;
	snake.x[1]=4;
	snake.y[1]=4;
	snake.x[2]=4;
	snake.y[2]=3;
	speeds = NORSPEED; 	//游戏速度
	tms = 0;
	scores = 0;
	Create_Food();		//生成第一个食物
}

static void Snake_Run()	//蛇爬行算法
{	
	uint8 i;
	for(i=(snake.node-1);i>0;i--)		//蛇头作为前进引导，长江后浪推前浪 
	{
		snake.y[i]=snake.y[i-1];
		snake.x[i]=snake.x[i-1];
	}
	switch (snake.direc)	//根据蛇的方向标前进
	{
		case up: 	snake.y[0]+=1;	break;
		case down:	snake.y[0]-=1;	break;
		case left:	snake.x[0]-=1;	break;
		case right:	snake.x[0]+=1;	break;
	}
}

static void Snake_Disp()	//游戏画面显示
{
	uint8 p = 16;
//	for(p=0;p<snake.node;p++)//绘制蛇图像
//	{		
//		delayus(500-duty);
//		DisPoint(snake.x[p],snake.y[p]);
//		delayus(duty/5);
//		cdata = 0xff;
//	}
//	DisPoint(food.x,food.y);//绘制食物图像
//	delayus(duty);
//	cdata = 0xff;
//	
//	for(i=0;i<16;i++)
//	{
//		DispRAM[i] = 0;
//	}
	while(p--) DispRAM[p]=0;	//清除缓存	
	for(p=0;p<snake.node;p++)	//写入新缓存
	{	
		DispRAM[snake.y[p]] |= 0x80 >> (snake.x[p]);
	}
//	DispRAM[food.y] |= 0x80 >> (food.x);
	
	MatxDisp(DispRAM,duty);
	DisPoint(7-food.x,food.y);
	delayus(duty);
}

void Snake_Game()	//游戏过程
{
	Snake_Init();		//初始化游戏
	Play_Music(sound_canon);
	while(snake.life)	//有生命，便可玩
	{
		uint8 i;
		switch(keypad)//直接读取键值，贪吃蛇不需要消抖
		{
			case K_UP:	if((snake.direc==left)||(snake.direc==right))	snake.direc=up;
				//按下UP键时，只有蛇在水平方向时才能改变
				break;
			case K_DOWN:if((snake.direc==left)||(snake.direc==right))	snake.direc=down;
				//按下DOWN键时，只有蛇在水平方向时才能改变
				break;
			case K_LEFT:if((snake.direc==up)||(snake.direc==down))		snake.direc=left;
				//按下left键时，只有蛇在垂直方向时才能改变
				break;
			case K_RIGHT:if((snake.direc==up)||(snake.direc==down))		snake.direc=right;
				//按下right键时，只有蛇在垂直方向时才能改变
				break;
			default :
				break;
		}
		
		if(KEY_OK==0) speeds = ASPEED;//加速键
		else speeds = NORSPEED;
		keypad = K_NULL;
		
		if(tms > speeds)	//半秒前进一格
		{
			tms=0;
			Snake_Run();	//无聊散步
		}
		if((snake.x[0]==food.x) && (snake.y[0]==food.y))//是否吃到食物
		{
			Sound_Tone(sound_ON,4,5);
//			getfood=1;//直接在此增加蛇长度会在下一个显示扫描产生一个原有数据留影，故通过加长
			snake.node++;
//			game_speed-=10;	//每吃一个食物增加10点速度
			Create_Food();	//产生新食物
		}
		if((snake.x[0]>WIDTH-1)||(snake.x[0]<0)||(snake.y[0]>LENGTH-1)||(snake.y[0]<0))//是否碰壁
		{
			snake.life=0;	//蛇碰到墙壁死亡
		}
		for(i=3;i<snake.node;i++)//从蛇的第四节开始判断是否撞到自己了，因为蛇头不可能撞到二三四节
		{
			if((snake.x[i]==snake.x[0])&&(snake.y[i]==snake.y[0]))//是否自残
				snake.life=0;	//蛇头碰到自身死亡
		}
		Snake_Disp();	//显示游戏图像
		scores = snake.node-3;
		SMG_Display(scores,duty);
	}
	scores = snake.node-3;
	TR2_OFF;
}



