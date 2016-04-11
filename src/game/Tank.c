#include "Tank.h"


typedef struct _COORD_
{
    int8_t x;
    int8_t y;
}coord_t;

typedef struct _AMMO_
{
    coord_t   pos;
    direction trajectory;
}ammo_t;

typedef struct TANK_T
{
    uint8_t    state;
    coord_t    pos;
    direction  direct;
    ammo_t     bullet[MAX_BULLETS];
    uint8_t    bulletNums;
}tank_t;

const coord_t tankMod[6] = 
{
    {.x = 1, .y = 1},
    {.x = 1, .y = 2},
    {.x = 2, .y = 2},
    {.x = 2, .y = 3},
    {.x = 3, .y = 1},
    {.x = 3, .y = 2},
}

tank_t tankList_mem[MAX_TANKS];
tank_t *tankList;


void trajectory_update()
{
    int8_t idxTank, idxBullet;
    
    for(idxTank=0; idxTank<MAX_TANKS; idxTank++)
    {
        if(tankList[idxTank]->state != ST_DEATH)   //check the tank alive?
        {
            for(idxBullet=0; idxBullet<MAX_BULLETS; idxBullet++)
            {
                switch (tankList[idxTank]->bullet[idxBullet].trajectory)
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
            }
        }
    }
    
}

//bullet
//coord
//position
//direction
//trajectory


void Tank_GameInit()
{
    *tankList = malloc(sizeof(tank_t) * MAX_TANKS);
    memset(tankList, 0, sizeof(tank_t) * MAX_TANKS);
 //   *tankList = &tankList_mem;
}

void Tank_GamePlay()
{
    
}

void Tank_GameEnd()
{
    free(tankList);
}