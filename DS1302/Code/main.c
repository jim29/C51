/************************************
 *      DS1302练习
 *                      2020/5/14   
 * **********************************
 */

#include <STC15F2K60S2.H>
#include "global.h"
#include "segment.h"
#include "timer.h"
#include "ds1302.h"

void ReadTime();


extern u8 SegContent[];
u16 Systick;    //系统tick


void main()
{
    SysInit();
	Timer0Init();
    DS1302_Init();
    Systick = 0;
    //LatchCtrl(LED_ID, 0x7F);    //LED测试
    while(1){
        if (Systick > 40000)    Systick = 0;    //20s设定溢出
        //每50ms读DS1302时间
        if (Systick % 100 == 0){
           ReadTime();
        }
    }

}


//系统中断T0 500us
void SysInterrupt() interrupt 1 
{
    Systick ++;
    //3ms刷新间隔
    if (Systick % 6 == 0){
        SegFresh();
    }
} 

//读取时间
void ReadTime()
{
    u8 hour, min, sec;
    DS1302_TimeRead(&hour, &min, &sec);
    SegContent[0] = (hour >> 4) & 0x0F;
    SegContent[1] = hour & 0x0F;
    SegContent[3] = (min >> 4) & 0x0F;
    SegContent[4] = min & 0x0F;
    SegContent[6] = (sec >> 4) & 0x0F;
    SegContent[7] = sec & 0x0F;   
}