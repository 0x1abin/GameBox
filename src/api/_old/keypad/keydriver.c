/*
题目：多功能按键设计。利用一个I/O口，接一个按键，实现3功能操作：单击 + 双击 + 长按。
============================================================================
用户基本操作定义：
    1。短按操作：按键按下，按下时间<1s，属于一次短按操作
    2。长按操作：按键按下，按下时间>1s，属于一次长按操作

在正常0.5s内无按键操作为启始按键扫描条件下，扫描按键将产生以下3种按键事件：
    1。长按事件：任何1次出现的长按操作都属于长按事件
    2。单击事件：1次短按操作后，间隔0.5内没有短按操作
    3。双击事件：2次短按操作间隔时间<0.5s，则2次短按操作为1次双击事件，且2次短按都取消

特别操作情况定义：
    1。短按操作和长按操作间隔<0.5s，以及，长按操作和短按操作间隔<0.5s，均不产生双击事件
    2。连续n次（n为奇数）短按操作，且间隔均<0.5s，产生(n-1)/2次双击事件+1次单击事件
    3。连续n次（n为偶数）短按操作，且间隔均<0.5s，产生n/2次双击事件

对按键操作者的建议：
    由于按键的多功能性质，建议操作者每次在单击/长按/双击按键事件发生后，隔0.5s后再进行下一次的按键操作。
		因为在特别操作情况下，程序是保证按定义进行判断和处理的，主要是怕操作者自己记不清楚导致操作失误。

对软件设计者的要求：
    1。应该全面进行分析，给出严格定义和判断条件，如上所示。如果自己都不清楚，你的设计出的系统就不稳定，不可靠。
    2。在1的基础上，编写出符合要求的程序，并进行全面测试

*/

/*=============
低层按键（I/0）扫描函数，即低层按键设备驱动，只返回无键、短按和长按。具体双击不在此处判断。
===============*/

#define key_input    PIND.7    // 按键输入口 

#define N_key    0             //无键 
#define S_key    1             //单键 
#define D_key    2             //双键 
#define L_key    3             //长键 

#define key_state_0 				0
#define key_state_1 				1
#define key_state_2 				2

unsigned char key_driver(void)
{
	static unsigned char key_state = key_state_0, key_time = 0;
	unsigned char key_press, key_return = N_key;

	key_press = key_input;                    // 读按键I/O电平

	switch (key_state)
	{
	case key_state_0:                              // 按键初始态
		if (!key_press) key_state = key_state_1;      // 键被按下，状态转换到按键消抖和确认状态
		break;

	case key_state_1:                      // 按键消抖与确认态
		if (!key_press)
		{
			key_time = 0;                   //
			key_state = key_state_2;   // 按键仍然处于按下，消抖完成，状态转换到按下键时间的计时状态，但返回的还是无键事件
		}
		else
			key_state = key_state_0;   // 按键已抬起，转换到按键初始态。此处完成和实现软件消抖，其实按键的按下和释放都在此消抖的。
		break;

	case key_state_2:
		if(key_press)
		{
			key_return = S_key;        // 此时按键释放，说明是产生一次短操作，回送S_key
			key_state = key_state_0;   // 转换到按键初始态
		}
		else if (++key_time >= 100)     // 继续按下，计时加10ms（10ms为本函数循环执行间隔）
		{
			key_return = L_key;        // 按下时间>1000ms，此按键为长按操作，返回长键事件
			key_state = key_state_3;   // 转换到等待按键释放状态
		}
		break;

	case key_state_3:                 // 等待按键释放状态，此状态只返回无按键事件
		if (key_press) key_state = key_state_0; //按键已释放，转换到按键初始态
		break;
	}
	return key_return;
}

/*=============
中间层按键处理函数，调用低层函数一次，处理双击事件的判断，返回上层正确的无键、单键、双键、长键4个按键事件。
本函数由上层循环调用，间隔10ms
===============*/

unsigned char key_read(void)
{
	static unsigned char key_m = key_state_0, key_time_1 = 0;
	unsigned char key_return = N_key,key_temp;

	key_temp = key_driver();

	switch(key_m)
	{
	case key_state_0:
		if (key_temp == S_key )
		{
			key_time_1 = 0;               // 第1次单击，不返回，到下个状态判断后面是否出现双击
			key_m = key_state_1;
		}
		else
			key_return = key_temp;        // 对于无键、长键，返回原事件
		break;

	case key_state_1:
		if (key_temp == S_key)             // 又一次单击（间隔肯定<500ms）
		{
			key_return = D_key;           // 返回双击键事件，回初始状态
			key_m = key_state_0;
		}
		else
		{
			// 这里500ms内肯定读到的都是无键事件，因为长键>1000ms，在1s前低层返回的都是无键
			if(++key_time_1 >= 50)
			{
				key_return = S_key;      // 500ms内没有再次出现单键事件，返回上一次的单键事件
				key_m = key_state_0;     // 返回初始状态
			}
		}
		break;
	}
	return key_return;
}
