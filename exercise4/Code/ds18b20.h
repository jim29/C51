#ifndef __DS18B20_H
#define __DS18B20_H
#include <system.h>
#define INIT_SUCC 0 //初始化成功
//单总线延时函数
void Delay_OneWire(unsigned int t);
void Write_DS18B20(unsigned char dat);
unsigned char Read_DS18B20(void);
bit init_ds18b20(void);

#endif
