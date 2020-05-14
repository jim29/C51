#include <global.h>
#include <STC15F2K60S2.h>
#include <timer.h>
#include <intrins.h>


/*
	定时器0 500us

*/
void Timer0Init(void)		//500微秒@11.0592MHz
{
	AUXR |= 0x80;		//定时器时钟1T模式
	TMOD &= 0xF0;		//设置定时器模式
	TL0 = 0x66;		//设置定时初值
	TH0 = 0xEA;		//设置定时初值
	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时器0开始计时
	EA = 1;
	ET0 = 1;
}

/*
	定时器1	50ms

*/
void Timer1Init(void)		//50毫秒@11.0592MHz
{
	AUXR &= 0xBF;		//定时器时钟12T模式
	TMOD &= 0x0F;		//设置定时器模式
	TL1 = 0x00;		//设置定时初值
	TH1 = 0x4C;		//设置定时初值
	TF1 = 0;		//清除TF1标志
	TR1 = 1;		//定时器1开始计时
	EA = 1;
	ET1 = 1;
}




/*
	@param
	xms		延迟xms
*/
void Delayms(u8 xms)		//@11.0592MHz
{
	u8 i, j, k = xms;
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
	}while(k--);
}





