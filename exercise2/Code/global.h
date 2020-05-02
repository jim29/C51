#ifndef _GLOBAL_H
#define _GLOBAL_H

//元件ID
#define LED_ID 4
#define SEG_SEC_ID	7
#define SEG_COM_ID	6
#define ULN_ID	5

//按键定义
#define NUM_0 0
#define NUM_1 1
#define NUM_2 2
#define NUM_3 3
#define NUM_4 4
#define NUM_5 5
#define NUM_6 6
#define NUM_7 7
#define NUM_8 8
#define NUM_9 9 
#define CLEAR 10
#define CHANGE 11
#define INPUT 12
#define NONE 13

//状态定义
#define IDLE	0
#define INPUT_MOD 1
#define OPEN_MOD 2
#define CHANGE_MOD 3	



typedef unsigned char u8;
typedef unsigned int u16;

void SysInit();
void LatchCtrl(u8 ID, u8 val);


#endif