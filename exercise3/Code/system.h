#ifndef _SYSTEM_H
#define _SYSTEM_H

#include <STC15F2K60S2.h>

//定义锁存器元件的ID值
#define LED_ID  4
#define SEG_SEC_ID  7
#define SEG_COM_ID  6
#define ULN_ID  5

#define SEG_INDEX_MAX 4     //数码管显示的位数

void LatchCtrl(unsigned char ID, unsigned char val);
void SysInit();
void Timer_0_Init(void);		//100微秒@12.000MHz

#endif