#include <ds1302.h>
#include <intrins.h>

sbit SCK=P1^7;		
sbit SDA=P2^3;		
sbit RST = P1^3;   											


//满足DS1302时序的延时 
void SomeNop()
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
		SDA=temp&0x01;
		temp>>=1; 
		SCK=1;
	}
}   


void Write_Ds1302( unsigned char address,unsigned char dat )     
{
 	RST=0;
	SomeNop();
 	SCK=0;
	SomeNop();
 	RST=1;	
   	SomeNop();  
 	Write_Ds1302_Byte(address);	
 	Write_Ds1302_Byte(dat);		
 	RST=0; 
}

unsigned char Read_Ds1302 ( unsigned char address )
{
 	unsigned char i,temp=0x00;
 	RST=0;
	SomeNop();
 	SCK=0;
	SomeNop();
 	RST=1;
	SomeNop();
 	Write_Ds1302_Byte(address);
 	for (i=0;i<8;i++) 	
 	{		
		SCK=0;
		temp>>=1;	
 		if(SDA)
 		temp|=0x80;	
 		SCK=1;
	} 
 	RST=0;
	SomeNop();
 	RST=0;
	SCK=0;
	SomeNop();
	SCK=1;
	SomeNop();
	SDA=0;
	SomeNop();
	SDA=1;
	SomeNop();
	return (temp);			
}
