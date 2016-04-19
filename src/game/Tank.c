#include "Tank.h"

#define X_WIDTH_MAX     8
#define Y_WIDTH_MAX     16

const uint8_t utankBitmap[3] = 
{
    B01000000,
    B11100000,
    B11100000,
    0
}
const uint8_t tankBitmap[3] = 
{
    B01000000,
    B11100000,
    B10100000,
    0
}

typedef struct _COORD_
{
    int8_t x;
    int8_t y;
}coord_t;

typedef struct _AMMO_
{
    coord_t   pos;
    direction direct;
}ammo_t;

typedef struct TANK_T
{
    uint8_t    state;               //状态
    coord_t    pos;                 //位置
    direction  direct;              //炮筒朝向
    ammo_t     bullet[MAX_BULLETS]; //子弹
    uint8_t    bulletNums;
}tank_t;

//bullet
//coord
//position
//direction
//trajectory

uint8_t trajeUpdate_handle;
tank_t tankList_mem[MAX_TANKS];
tank_t *tankList;



//更新弹道
void trajectory_update()
{
    uint8_t idxTank, idxBullet;
    
    for(idxTank=0; idxTank<MAX_TANKS; idxTank++)
    {
        if(tankList[idxTank]->state == STA_ALIVE)   //check the tank alive?
        {
            for(idxBullet=0; idxBullet<MAX_BULLETS; idxBullet++)
            {
                //当x或y坐标为0时，表示子弹不存在
                if((tankList[idxTank]->bullet[idxBullet].pos.x != 0) || (tankList[idxTank]->bullet[idxBullet].pos.y != 0))
                {
                    switch (tankList[idxTank]->bullet[idxBullet].direct)
                    {
                        case D_RIGHT:
                            tankList[idxTank]->bullet[idxBullet].pos.x++;
                            break;
                        
                        case D_LEFT:
                            tankList[idxTank]->bullet[idxBullet].pos.x--;
                            break;
                            
                        case D_UP:
                            tankList[idxTank]->bullet[idxBullet].pos.y++;
                            break;
                            
                        case D_DOWN:
                            tankList[idxTank]->bullet[idxBullet].pos.y--;
                            break;
                    }
                    //判断子弹是否射出了边界
                    if((tankList[idxTank]->bullet[idxBullet].pos.x <= X_WIDTH_MIN) || \ 
                       (tankList[idxTank]->bullet[idxBullet].pos.x >  X_WIDTH_MAX) || \
                       (tankList[idxTank]->bullet[idxBullet].pos.y <= Y_WIDTH_MIN) || \ 
                       (tankList[idxTank]->bullet[idxBullet].pos.y >  Y_WIDTH_MAX))
                    {//如果射出了边界，把xy坐标置0表示子弹不存在了。
                        tankList[idxTank]->bullet[idxBullet].pos.x = 0;
                        tankList[idxTank]->bullet[idxBullet].pos.y = 0;
                    }
                }
            }
        }
    }
}





void Tank_GameInit()
{
    *tankList = malloc(sizeof(tank_t) * MAX_TANKS);
    memset(tankList, 0, sizeof(tank_t) * MAX_TANKS);
 //   *tankList = &tankList_mem;
 
    trajeUpdate_handle = TimerCreate(&trajectory_update, 0,  400); //创建弹道循环更新任务
}

void Tank_GamePlay()
{
    
}

void Tank_GameEnd()
{
    free(tankList);
    
    TimerDelete(trajeUpdate_handle);
}