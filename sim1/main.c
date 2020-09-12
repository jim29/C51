/*
 *		单片机第九届模拟题 “温度记录器”
 *																				by MRY     2020/9/12
**/

#include <config.h>
#include <intrins.h>
#include <ds1302.h>
#include <onewire.h>

code u8 SEG_TAB[] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90, 0xFF, 0xBF};	//数字0~9; 空; '-'
code u8 TEMP_n = 10;
u8 SEG_CONTENT[] = {10, 10, 10, 10, 10, 11, 0, 1};
u8 TIME_HOUR = 0x23, TIME_MIN = 0x59, TIME_SEC = 0x50;
u8 TEM_DUTY[] = {1, 5, 30, 60};
u8 TEM_DUTY_i = 0;
u8 TEMP_SAVE[] = {24, 24, 24, 24, 24, 24, 24 ,24, 24, 24};
u8 TEMP_i;
u8 STATE;
u8 SEC_n;
u16 SYS_TICK; u16 SYS_TICK_tmp;
bit temp_end_flag;

void Latch_Ctrl(u8 ID, u8 val);
void Seg_Disp(u8 index, u8 val);
void Sys_Init();
void Timer0Init(void);
void Seg_Fresh();
void Duty2Seg();
void Delay_20ms();
u8 Key_Scan();
void Update_Time();
u8 Read_Temp();
void Update_Temp();

/**
 *	main function
 *
 */
void main()
{
	u8 key_pressed;
	Sys_Init();
	Timer0Init();
	
	while(1)
	{
		key_pressed = Key_Scan();
		if (key_pressed != KEY_NONE)
		{
			if (key_pressed == KEY_S4 && STATE == SETTING)
			{
				TEM_DUTY_i ++;
				if (TEM_DUTY_i > 3) TEM_DUTY_i = 0;
				Duty2Seg();
			}
			else if (key_pressed == KEY_S5)
			{
				if (STATE == SETTING)	
				{
					STATE = TIME;
					Write_Ds1302(0x80, TIME_SEC);
					Write_Ds1302(0x82, TIME_MIN);
					Write_Ds1302(0x84, TIME_HOUR);
					while (1)
					{
						SYS_TICK_tmp = SYS_TICK;
						while (SYS_TICK == SYS_TICK_tmp)	;
						if (SYS_TICK % 20 == 0)	//60ms
						{
							Update_Time();
							if ((SEC_n >= TEM_DUTY[TEM_DUTY_i]) && (temp_end_flag == 0))
							{
								SEC_n = 0;
								TEMP_SAVE[TEMP_i] = Read_Temp();
								TEMP_i ++;
								if (TEMP_i >= TEMP_n)
								{
									TEMP_i = 0;
									SEC_n = 0;
									temp_end_flag = 1;
								}
							}
							else if (temp_end_flag == 1)
							{
								key_pressed = Key_Scan();
								if (key_pressed == KEY_S6)
								{
									STATE = TEMP;
									temp_end_flag = 0;
									Latch_Ctrl(LED_ID, 0xFF);
									Update_Temp();
									break;
								}
							}
						}		
					}
				}
			}
			else if (key_pressed == KEY_S6 && STATE == TEMP)
			{
				////////////////////
				Update_Temp();
				if (TEMP_i >= TEMP_n)
				{
					TEMP_i = 0;
				}
			}
			else if (key_pressed == KEY_S7 && STATE == TEMP)
			{
				STATE = SETTING;
				TEMP_i = 0;
				TEM_DUTY_i = 0;
				Duty2Seg();
			}
		}
	}
	
	
}


void Latch_Ctrl(u8 ID, u8 val)
{
	P0 = val;
	P2 = ID << 5;
	_nop_();
	_nop_();
	_nop_();
	P2 = 0;
}


void Sys_Init()
{
	bit ds1802_flag = 1;
	Latch_Ctrl(ULN_ID, 0x00);
	Latch_Ctrl(LED_ID, 0xFF);
	Latch_Ctrl(SEG_COM_ID, 0x00);
	STATE = SETTING;
	TEMP_i = 0;
	SEC_n = 0;
	SYS_TICK = 0;
	temp_end_flag = 0;
}


void Timer0Init(void)		//3毫秒@12.000MHz
{
	AUXR |= 0x80;		//定时器时钟1T模式
	TMOD &= 0xF0;		//设置定时器模式
	TL0 = 0x60;		//设置定时初值
	TH0 = 0x73;		//设置定时初值
	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时器0开始计时
	EA = 1;
	ET0 = 1;
}

void T0_Inter() interrupt 1
{
	Seg_Fresh();
	SYS_TICK ++;
	if (SYS_TICK > 10000) SYS_TICK = 0;
}



void Seg_Disp(u8 index, u8 val)
{
	Latch_Ctrl(SEG_COM_ID, 1 << index);	// index 0~7
	Latch_Ctrl(SEG_SEC_ID, SEG_TAB[val]);
}


void Seg_Fresh()
{
	static u8 i = 0;
	Seg_Disp(i, SEG_CONTENT[i]);
	i ++;
	if (i >= 8)	i = 0;
}


void Duty2Seg()
{
	SEG_CONTENT[0] = 10;
	SEG_CONTENT[1] = 10;
	SEG_CONTENT[2] = 10;
	SEG_CONTENT[3] = 10;
	SEG_CONTENT[4] = 10;
	SEG_CONTENT[5] = 11;
	SEG_CONTENT[6] = TEM_DUTY[TEM_DUTY_i] / 10;
	SEG_CONTENT[7] = TEM_DUTY[TEM_DUTY_i] % 10;
}


void Delay_20ms()
{
	unsigned char i, j, k;
	_nop_();
	_nop_();
	i = 1;
	j = 234;
	k = 113;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}


u8 Key_Scan()
{
	u8 key = KEY_NONE;
	if (P30 == 0)
	{
		Delay_20ms();
		if (P30 == 0)
		{
			while (P30 == 0) ;
			key = KEY_S7;
		}
	}
	else if (P31 == 0)
	{
		Delay_20ms();
		if (P31 == 0) 
		{
			while (P31 == 0) ;
			key = KEY_S6;
		}
	}
	else if (P32 == 0)
	{
		Delay_20ms();
		if (P32 == 0) 
		{
			while (P32 == 0) ;
			key = KEY_S5;
		}
	}
	else if (P33 == 0)
	{
		Delay_20ms();
		if (P33 == 0)
		{
			while (P33 == 0) ;
			key = KEY_S4;
		}
	}
	else	key = KEY_NONE;
	return key;
}


void Update_Time()
{
	u8 sec_tmp;
	bit flag = 0;
	sec_tmp = Read_Ds1302(0x81);
	if (sec_tmp != TIME_SEC)
	{
		flag = ~flag;
		SEC_n ++;
	}
	TIME_SEC = sec_tmp;
	TIME_MIN = Read_Ds1302(0x83);
	TIME_HOUR = Read_Ds1302(0x85);
	SEG_CONTENT[0] = TIME_HOUR >> 4;
	SEG_CONTENT[1] = TIME_HOUR & 0x0F;
	SEG_CONTENT[2] = 10 + (u8)flag;
	SEG_CONTENT[3] = TIME_MIN >> 4;
	SEG_CONTENT[4] = TIME_MIN & 0x0F;
	SEG_CONTENT[5] = 10 + (u8)flag;
	SEG_CONTENT[6] = TIME_SEC >> 4;
	SEG_CONTENT[7] = TIME_SEC & 0x0F;
	if (temp_end_flag == 1)
	{
		Latch_Ctrl(LED_ID, 0xFE + (u8)flag);
	}
}



u8 Read_Temp()
{
	u8 dat1, dat2, temp;
	bit ds1802_flag;
	while(1)
	{
		ds1802_flag = Init_DS18B20();
		if (ds1802_flag == 0)
		{
			//Latch_Ctrl(LED_ID, 0xFE);
			break;
		}
		Delay_20ms();
	}
	Write_DS18B20(0xCC);
	Write_DS18B20(0x44);
	SYS_TICK_tmp = SYS_TICK;
	while (1)
	{
		while (SYS_TICK == SYS_TICK_tmp)	;
		if (SYS_TICK % 200 == 0)	 break;//600ms 
	}
	while(1)
	{
		ds1802_flag = Init_DS18B20();
		if (ds1802_flag == 0)
		{
			//Latch_Ctrl(LED_ID, 0xFE);
			break;
		}
		Delay_20ms();
	}
	Write_DS18B20(0xCC);
	Write_DS18B20(0xBE);
	dat1 = Read_DS18B20();
	dat2 = Read_DS18B20();
	while(1)
	{
		ds1802_flag = Init_DS18B20();
		if (ds1802_flag == 0)
		{
			//Latch_Ctrl(LED_ID, 0xFE);
			break;
		}
		Delay_20ms();
	}
	temp = (dat1 >> 4) + (dat2 << 4);
	return temp;
}


void Update_Temp()
{
	SEG_CONTENT[0] = 11;
	SEG_CONTENT[1] = TEMP_i / 10;
	SEG_CONTENT[2] = TEMP_i % 10;
	SEG_CONTENT[3] = 10;
	SEG_CONTENT[4] = 10;
	SEG_CONTENT[5] = 11;
	SEG_CONTENT[6] = TEMP_SAVE[TEMP_i] / 10;
	SEG_CONTENT[7] = TEMP_SAVE[TEMP_i] % 10;
	TEMP_i ++;
}







