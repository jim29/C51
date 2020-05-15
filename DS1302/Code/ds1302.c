/*
  程序说明: DS1302驱动程序
  软件环境: Keil uVision 4.10 
  硬件环境: CT107单片机综合实训平台 8051，12MHz
  日    期: 2011-8-9
*/

#include <reg52.h>
#include <intrins.h>
#include <ds1302.h>
#include "global.h"

sbit SCK = P1^7;		
sbit SDA= P2^3;		
sbit RST = P1^3;   // DS1302复位												



void Write_Ds1302(unsigned  char temp) 
{
	unsigned char i;
	for (i=0;i<8;i++)     	
	{ 
		SCK=0;
		SDA=temp&0x01;
		temp>>=1; 
		SCK=1;
	}
}   

void Write_Ds1302_Byte( unsigned char address,unsigned char dat )     
{
 	RST=0;	Delay();
 	SCK=0;	Delay();
 	RST=1; 	Delay();  
 	Write_Ds1302(address);	
 	Write_Ds1302(dat);		
 	RST=0; 
}

unsigned char Read_Ds1302_Byte ( unsigned char address )
{
 	unsigned char i,temp=0x00;
 	RST=0;	Delay();
 	SCK=0;	Delay();
 	RST=1;	Delay();
 	Write_Ds1302(address);
 	for (i=0;i<8;i++) 	
 	{		
		SCK=0;
		temp>>=1;	
 		if(SDA)
 		temp|=0x80;	
 		SCK=1;
	} 
 	RST=0;	Delay();
 	SCK=0;	Delay();
	SCK=1;	Delay();
	SDA=0;	Delay();
	SDA=1;	Delay();
	return (temp);			
}


/**
 *  DS1302初始化，写入23小时59分59秒
 */
void DS1302_Init()
{
    Write_Ds1302_Byte(0x80, 0x59);    //写入59s
    Write_Ds1302_Byte(0x82, 0x59);    //写入59min
    Write_Ds1302_Byte(0x84, 0x23);    //写入23h
}


/**
 *  依次读取DS1302中的时，分，秒
 * @param
 * hour 小时
 * min  分
 * sec  秒
 */
void DS1302_TimeRead(unsigned char* hour, unsigned char* min, unsigned char* sec)
{
    *sec = Read_Ds1302_Byte(0x81);
    *min = Read_Ds1302_Byte(0x83);
    *hour = Read_Ds1302_Byte(0x85);
}

