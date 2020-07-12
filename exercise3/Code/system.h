#ifndef _SYSTEM_H
#define _SYSTEM_H

//定义锁存器元件的ID值
#define LED_ID  4
#define SEG_SEC_ID  7
#define SEG_COM_ID  6
#define ULN_ID  5

void LatchCtrl(unsigned char ID, unsigned char val);
void SysInit();

#endif