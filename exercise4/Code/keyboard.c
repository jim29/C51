#include <keyboard.h>
#include <intrins.h>
#include <ds18b20.h>
extern unsigned char SYS_STATE;
extern unsigned char T;
extern unsigned char SEG_CONTENT[];


void Delay20ms()		//@12.000MHz
{
	unsigned char i, j, k;

	_nop_();
	_nop_();
	i = 1;
	j = 234;
	k = 113;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}


/*
 *  键盘扫描判断
 * @return
 * unsigned char 按键事件序号
 */
unsigned char KeyScan()
{
    unsigned char T_data_L;
    unsigned char T_data_H;
    if(S7 == 0){
        Delay20ms();
        if(S7 == 0){
            while(S7 == 0);
            return S7_PRESSED;
        }
    }
    else if(S6 == 0){
        Delay20ms();
        if(S6 == 0){
            while(S6 == 0);
            return S6_PRESSED;
        }
    }
    else if(S5 == 0){
        Delay20ms();
        if(S5 == 0){
            while(S5 == 0);
            return S5_PRESSED;
        }
    }
    else if(S4 == 0){
        Delay20ms();
        if(S4 == 0){
            while(S4 == 0){
                if(SYS_STATE == IDLE){
                    while(init_ds18b20() != INIT_SUCC){
                        Delay20ms();
                    }
                    Write_DS18B20(0xCC);
                    Write_DS18B20(0x44);
                    while(P14 == 0)   ;
                    Delay20ms();
                    while(init_ds18b20() != INIT_SUCC){
                        Delay20ms();
                    }
                    Write_DS18B20(0xCC);
                    Write_DS18B20(0xBE);
                    T_data_L = Read_DS18B20();
                    T_data_H = Read_DS18B20();
                    T = (T_data_L >> 4) + (T_data_H << 4);
                    SEG_CONTENT[0] = 12;
                    SEG_CONTENT[1] = 12;
                    SEG_CONTENT[2] = 12;
                    SEG_CONTENT[3] = 12;
                    SEG_CONTENT[4] = 12;
                    SEG_CONTENT[5] = T / 10;
                    SEG_CONTENT[6] = T % 10;
                    SEG_CONTENT[7] = 11;
                    Delay20ms();
                    Delay20ms();
                }
            }
            SEG_CONTENT[2] = 10;
            SEG_CONTENT[5] = 10;
            return S4_PRESSED;
        }
    }
    else{
        return NONE_PRESSED;
    }
    return NONE_PRESSED;
}