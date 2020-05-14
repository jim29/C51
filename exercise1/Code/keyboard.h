#ifndef	_KEYBOARD_H
#define	_KEYBOARD_H
#include <global.h>

#define BtnNone 0	//空响应
#define Btn1	1	//4个按键标志
#define Btn2	2
#define Btn3	3
#define Btn4	4

u8 KeyScan(); //判断哪个按键被按下，返回按键序号 1~4

#endif