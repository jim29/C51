#include <timer.h>
#include <global.h>
#include <intrins.h>
#include <STC15F2K60S2.h>

/*
 *	延时毫秒
 *	@param
 *	xms 时长（ms)
 *
 */
void Delayms(u8 xms)		//@11.0592MHz
{
	u8 i, j;
	do{
		_nop_();
		_nop_();
		_nop_();
		i = 11;
		j = 190;
		do
		{
			while (--j);
		} while (--i);
	}while (--xms);
}

/*
 *	系统和数码管刷新中断 500us
 */
void Timer0Init(void)		//500微秒@11.0592MHz
{
	AUXR &= 0x7F;		//定时器时钟12T模式
	TMOD &= 0xF0;		//设置定时器模式
	TL0 = 0x33;		//设置定时初值
	TH0 = 0xFE;		//设置定时初值
	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时器0开始计时
	ET0 = 1;
	EA = 1;
}
