#include <system.h>
#include <intrins.h>
#include <segment.h>
#include <sonic.h>
/*
 *  超声波测距练习  2020/7/22 by MRY
 */

extern int SYSTICK;     
int SYSTICK_tmp;        //存储上一tick
code unsigned char SEG_INDEX[] = {0, 1, 2, 3};       //显示位置
unsigned char SEG_CONTENT[] = {1, 2, 3, 4};     //显示数字
unsigned int DISTANCE = 2233;  //超声波测距距离     

void ContentUpdate(unsigned int dst, unsigned char content[]);

int main()
{
    SysInit();
    SYSTICK = 0;
    while(1){   
        SYSTICK_tmp = SYSTICK;
        while(SYSTICK_tmp == SYSTICK){;}    //等待tick
        if(SYSTICK % 5000 == 0){        //0.5s更新距离
            DISTANCE = SonicMeasure();  //单位mm
            ContentUpdate(DISTANCE, SEG_CONTENT);
        }
        if(SYSTICK > 40000){
            SYSTICK = 0;
        }
        
    }
}


//定时器0用来刷新系统 100us
void Timer_0_Routine() interrupt 1
{
    SYSTICK ++;
    if(SYSTICK % 30 == 0){  //3ms刷新数码管
        SegmentFresh(SEG_INDEX, SEG_CONTENT);
    }
}


/*
 *  重新计算显示内容
 */
void ContentUpdate(unsigned int dst, unsigned char content[])
{
    char i;     //unsigned 会反向溢出，不能和0比较
    if(dst > 9999) dst = 9999;
    for(i = SEG_INDEX_MAX -1; i >= 0; i --){
        content[i] = dst % 10;
        dst = dst / 10;
    }
}

