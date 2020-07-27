#ifndef __DS1302_H
#define __DS1302_H
#include <system.h>

#define SEC_READ_ADDR   0x81    //寄存器地址
#define SEC_WRITE_ADDR  0x80
#define MIN_READ_ADDR   0x83
#define MIN_WRITE_ADDR  0x82
#define HOUR_READ_ADDR  0x85
#define HOUR_WRITE_ADDR 0x84


void Write_Ds1302_Byte(unsigned  char temp);
void Write_Ds1302( unsigned char address,unsigned char dat );
unsigned char Read_Ds1302 ( unsigned char address );

#endif
