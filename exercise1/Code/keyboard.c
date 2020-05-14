#include <keyboard.h>
#include <timer.h>
#include <global.h>
#include <STC15F2K60S2.h>

sbit key1 = P3^0;
sbit key2 = P3^1;
sbit key3 = P3^2;
sbit key4 = P3^3;

/*
	@return
	按下按键序号/BtnNone
*/
u8 KeyScan()
{
	if(!key1){
		Delayms(15);
		if(!key1){
			while(!key1) ;
			return 1;
		}
	}
	if(!key2){
		Delayms(15);
		if(!key2){
			while(!key2) ;
			return 2;
		}
	}
	if(!key3){
		Delayms(15);
		if(!key3){
			while(!key3) ;
			return 3;
		}
	}
	if(!key4){
		Delayms(15);
		if(!key4){
			while(!key4) ;
			return 4;
		}
	}
	return BtnNone;
}


