#ifndef _SYSTEM_H
#define _SYSTEM_H
#include <STC15F2K60S2.h>
#define LED_ID  4           //定义锁存元件ID
#define SEG_SEC_ID  7
#define SEG_COM_ID  6
#define ULN_ID  5

#define IDLE    0    //时钟显示 （系统状态）   SYS STATE
#define HOUR_SETTING 1
#define MIN_SETTING 2
#define SEC_SETTING 3
#define ALARM_RISING 4

#define NONE_SETTING 0  //设置模式      SETTING MODE
#define RUNTIME_SETTING 1   
#define ALARM_SETTING   2

#define TIME_ADD    0   //时间加减标准
#define TIME_SUB    1

void LatchCtrl(unsigned char ID, unsigned char val);
void SysInit();

#endif