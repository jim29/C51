/*
  ����˵��: DS1302��������
  �������: Keil uVision 4.10 
  Ӳ������: CT107��Ƭ���ۺ�ʵѵƽ̨ 8051��12MHz
  ��    ��: 2011-8-9
*/

#include <reg52.h>
#include <intrins.h>
#include <ds1302.h>

sbit SCK=P1^7;		
sbit SDA=P2^3;		
sbit RST = P1^3;   // DS1302��λ												


void Some_Nop()
{
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
}

void Write_Ds1302_Byte(unsigned  char temp) 
{
	unsigned char i;
	for (i=0;i<8;i++)     	
	{ 
		SCK=0;
		Some_Nop();
		SDA=temp&0x01;
		temp>>=1;
		Some_Nop();		
		SCK=1;
		Some_Nop();
	}
}   

void Write_Ds1302( unsigned char address,unsigned char dat )     
{
 	RST=0;
	Some_Nop();
 	SCK=0;
	Some_Nop();
 	RST=1;	
  Some_Nop();  
 	Write_Ds1302_Byte(address);	
 	Write_Ds1302_Byte(dat);		
 	RST=0; 
}

unsigned char Read_Ds1302 ( unsigned char address )
{
 	unsigned char i,temp=0x00;
 	RST=0;
	Some_Nop();
 	SCK=0;
	Some_Nop();
 	RST=1;
	Some_Nop();
 	Write_Ds1302_Byte(address);
 	for (i=0;i<8;i++) 	
 	{		
		SCK=0;
		temp>>=1;
		Some_Nop();
 		if(SDA)
 		temp|=0x80;	
 		SCK=1;
		Some_Nop();
	} 
 	RST=0;
	Some_Nop();
 	RST=0;
	SCK=0;
	Some_Nop();
	SCK=1;
	Some_Nop();
	SDA=0;
	Some_Nop();
	SDA=1;
	Some_Nop();
	return (temp);			
}
