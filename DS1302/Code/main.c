/**
 *      DS1302练习
 *                      2020/5/14   
 */

#include <STC15F2K60S2.H>
#include "global.h"

void main()
{
    SysInit();
    LatchCtrl(LED_ID, 0x7F);    //LED测试
    while(1){
        ;
    }

}