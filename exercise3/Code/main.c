#include <STC15F2K60S2.h>
#include <system.h>
#include <timer.h>
#include <intrins.h>


int SYSTICK, SYSTICK_tmp;
unsigned char LED_val = 0xFE;
int main()
{
    SysInit();
    Timer0Init();
    SYSTICK = 0;
    while(1){
        LatchCtrl(LED_ID, LED_val);
        SYSTICK_tmp = SYSTICK;
        while(SYSTICK_tmp == SYSTICK){;}
        if(SYSTICK % 10000 == 0){
            LED_val = _crol_(LED_val, 1);
        }
        if(SYSTICK > 40000){
            SYSTICK = 0;
        }
    }
}

//定时器0用来刷新系统 100us
void Timer0() interrupt 1
{
    SYSTICK ++;
}