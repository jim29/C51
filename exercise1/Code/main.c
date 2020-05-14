#include <STC15F2K60S2.h>
#include <global.h>
#include <segment.h>
#include <timer.h>
#include <keyboard.h>
#include <iic.h>



u16 Systick = 0;
u8 count = 0;
u8 SecNum = 0;
u8 MinNum = 0;
u8 SegLength = 4;
u8 SegContent[4] = {0, 0, 0, 0};	//数码管显示内容
u8 code SegSit[] = {3, 4, 7, 8};	//显示位置
u8 Seg_i= 0; 						//刷新序号
u8 BtnPressed = BtnNone;

void FreshSeg();


void main()
{
	InitBuzzer();					//关闭蜂鸣器
	Timer0Init();					
	Timer1Init();
	ReadAddr(0x05, &SecNum, &MinNum);
	
	while(1){
		u16 SystickTmp = Systick;	//缓存对时
		if(Systick > 40000){ 		//20s设定溢出
			Systick = 0;
		}
		
		
		//每500ms计算和写入
		if(Systick % 1000 == 0){
			// 显示内容计算
			SegContent[0] = MinNum / 10;
			SegContent[1] = MinNum % 10;
			SegContent[2] = SecNum / 10;
			SegContent[3] = SecNum % 10;
			WriteAddr(0x05, SecNum, MinNum);
		}
		
		
		//每50ms扫一次键盘响应
		if(Systick % 100 == 0){ 
 			BtnPressed = KeyScan();
			if(BtnPressed != BtnNone){
				switch (BtnPressed){
					//按键1， 加1s
					case Btn1:
						if(SecNum >= 59){	
							SecNum = 0;
							MinNum ++; 
						}
						else
							SecNum ++;
						break;
					//按键2， 减1s
					case Btn2:
						if(SecNum == 0){	
							SecNum = 59;
							MinNum --;
						}
						else
							SecNum --;
						break;
					//按键3，	清零
					case Btn3:
						SecNum = 0;
						MinNum = 0;
						break;
					//按键4，	暂停
					case Btn4:
						//
						break;
					default:	;
				}
			}
		}
		
		while(SystickTmp == Systick) ;	//系统刷新
	}
}


// 系统中断 500us一次
void T0Interrupt()	interrupt 1
{
	Systick ++;
	if(Systick % 10 == 0){ //每5ms刷新数码管
		FreshSeg();
	}
}


// 计时器1 50ms一次
void T1Interrupt()	interrupt 3
{
	count++;
	if(count >= 20){
		count = 0;
		if(SecNum >= 59){		//每隔60s清零
			SecNum = 0;
			MinNum ++; 			//不考虑分钟溢出
		}
		else{
			SecNum++;
		}
	}
}



// 刷新数码管每一位
void FreshSeg()
{
	SegDisplay(SegSit[Seg_i], SegContent[Seg_i]);	
	if(Seg_i >= SegLength - 1)
		Seg_i = 0;
	else
		Seg_i ++;
}



