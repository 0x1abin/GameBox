#include "config.h"

uint8 code sound_up[8][2]=
{
	{8,8},{9,8},{10,8},{11,8},{12,8},{13,8},{14,8},{0,0}
};

uint8 code sound_down[8][2]=
{
	{7,8},{6,8},{5,8},{4,8},{3,8},{2,8},{1,8},{0,0}
};

uint8 code sound_game_start[][2]=
{
	{1,15},
	{1,15},
	{3,15},
	
	{1,10},
	{1,10},
	{3,20},
	{0,0}
};

uint8 code sound_game_over[5][2]=
{
	{6,15},
	{4,15},
	{3,15},
	{1,30},
	{0,0}
};

uint8 code sound_korobelniki[][2]=
{	
	{6,28},
	{3,18},
	{4,18},
	{5,18},

	{4,18},
	{3,18},
	{2,20},

{0,1},

	{2,20},
	{4,20},
	{6,28},

{0,1},

	{5,18},
	{4,22},
	{3,22},
	
{0,1},	

	{4,22},
	{5,22},
	{6,22},	

{0,1},	
	
	{4,22},		
	
	{2,22},
	{0,2},
	{2,28},
	
{0,12},

	{5,30},
	{6,25},
	{7+2,22},
	
	{7+1,22},
	{6,28},

	{4,18},
	{6,20},
	
	{5,18},
	{4,18},
	{3,28},

	{4,18},
	{5,28},
	
	{6,20},
	{4,20},
	{2,20},
	{0,1},
	{2,25},
	{0,0},
};

uint8 code sound_canon[][2]=
{	
	{7+3,35},{7+2,40},{7+1,35},{7,40},

	{6,35},{5,40},

	{6,35},{7,40},

	{7+1,35},{7,40},

	{6,35},{5,40},

	{4,35},{3,40},

	{4,35},{2,40},

	{7+1,20},{7,20},{7+1,20},{1,20},

	{7,20},{5,20},{2,20},{3,20},

	{1,20},{7+1,20},{7,20},{6,20},

	{7,20},{7+3,20},{7+5,20},{7+6,20},

	{7+4,20},{7+3,20},{7+2,20},{7+4,20},

	{7+4,20},{7+3,20},{7+1,20},{7,20},

	{6,20},{5,20},{4,20},{3,20},

	{2,20},{4,20},{3,20},{2,20},

	{1,20},{2,20},{3,20},{4,20},

	{5,20},{2,20},{5,20},{4,20},

	{3,20},{6,20},{5,20},{4,20},

	{5,20},{4,20},{3,20},{2,20},

	{1,20},{6,20},{6,20},{7,20},

	{7+1,20},{7,20},{6,20},{5,20},

	{4,20},{3,20},{2,20},{6,20},

	{5,20},{6,20},{5,20},{4,20},
	
	{0,0},
};
