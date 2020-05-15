#ifndef _DS1302_H
#define _DS1302_H
#include "global.h"

void DS1302_Init();
void DS1302_TimeRead(unsigned char* hour, unsigned char* min, unsigned char* sec);
#endif