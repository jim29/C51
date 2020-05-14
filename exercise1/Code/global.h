#ifndef _GLOBAL_H
#define _GLOBAL_H

#define	ULN_ID	5
#define	SEG_COM_ID	6
#define	SEG_SEC_ID	7
#define	LED_ID	4

typedef unsigned char u8;
typedef unsigned int u16;



void LatchControl(u8 ID, u8 val);	//控制锁存器
void InitBuzzer();	//初始化蜂鸣器

#endif