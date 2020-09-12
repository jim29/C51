#ifndef _SYSTEM_H
#define _SYSTEM_H
#include <STC15F2K60S2.H>
#define LED_ID	4
#define SEG_SEC_ID	7
#define SEG_COM_ID	6
#define ULN_ID	5

void Latch_Ctrl(unsigned char ID, unsigned char val);
void System_Init();

#endif