#ifndef _SOUND_DRIVES_H__
#define _SOUND_DRIVES_H__

/*************Tone_Freq_HZ*******************/
#define L_1D0	262
#define	L_2RE	294
#define	L_3MI	330
#define	L_4FA	349
#define	L_5SO	392
#define	L_6LA	440
#define	L_7XI	494
#define M_1DO   523
#define M_2RE   587
#define M_3MI   659
#define M_4FA   698
#define	M_5SO	784
#define	M_6LA	880
#define	M_7XI	988
#define	H_1DO	1046
#define	H_2RE	1175
#define	H_3MI	1318
#define	H_4FA	1397
#define	H_5SO	1568
#define	H_6LA	1760
#define	H_7XI	1967
/*********************************************/
#define TR2_NO		AUXR |= 0x10	//定时器2打开
#define TR2_OFF		AUXR &= 0xEF	//关闭
#define PIN_TR2		(AUXR & 0x10)	//判断TR2是否打开

extern uint8 code sound_up[][2];
extern uint8 code sound_down[8][2];
extern uint8 code sound_game_start[][2];
extern uint8 code sound_game_over[][2];
extern uint8 code sound_korobelniki[][2];
extern uint8 code sound_canon[][2];

extern uint16 data sound_cnt_time;
extern uint8 (*music_p)[2];
extern uint8 s_p;

void Sound_Init(void);
void Sound_Tone(bit ON_OFF,uint8 freq,uint8 s_tms);  //freq>367
void Play_Music(uint8 (*sound)[2]);

#endif