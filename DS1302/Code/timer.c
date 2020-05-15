#include "global.h"
#include "STC15F2K60S2.H"
#include "timer.h"

/*
 *  T0 16位自动重载计数器 500us
 */
void Timer0Init(void)		//500微秒@11.0592MHz
{
	AUXR |= 0x80;		//定时器时钟1T模式
	TMOD &= 0xF0;		//设置定时器模式
	TL0 = 0x66;		//设置定时初值
	TH0 = 0xEA;		//设置定时初值
	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时器0开始计时
    ET0 = 1;        //使能T0
    EA = 1;
}
