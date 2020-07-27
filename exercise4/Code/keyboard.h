#ifndef _KEYBOARD_H
#define _KEYBOARD_H
#include <system.h>
#define S7  P30
#define S6  P31
#define S5  P32
#define S4  P33

#define NONE_PRESSED    0
#define S7_PRESSED  1
#define S6_PRESSED  2
#define S5_PRESSED  3
#define S4_PRESSED  4

unsigned char KeyScan();

#endif