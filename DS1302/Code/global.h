#ifndef _GLOBAL_H
#define _GLOBAL_H

typedef unsigned char u8;
typedef unsigned int u16;

#define LED_ID  4
#define SEG_COM_ID  6
#define SEG_SEC_ID  7
#define ULN_ID  5

void LatchCtrl(u8 ID, u8 val);
void SysInit();
void Delay();
#endif