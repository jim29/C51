#include <STC15F2K60S2.H>
#include <global.h>
#include <segment.h>
#include <timer.h>
#include <keyboard.h>
#include <PCF8591.h>

u8 AIN1;
u16 Systick;
extern u8 SegContent[8];

void NumToContent(u8 n);

void main()
{
	Systick = 0;
	SysInit();
	Timer0Init();
	PCF8591_Init(1);
	while(1){
		AIN1 = PCF8591_Read();
		NumToContent(AIN1);
		Delayms(1000);		
	}
}


//刷新数码管
void T0_Inter() interrupt 1
{
	if(Systick > 400000)	Systick = 0;
	if(Systick % 6 == 0)	SegFresh();
	Systick ++;
}

//计算显示值
void NumToContent(u8 n)
{
	SegContent[0] = n / 100;
	SegContent[1] = n / 10 % 10;
	SegContent[2] = n % 10;
}

