/*
  程序说明: IIC总线驱动程序
  软件环境: Keil uVision 4.10 
  硬件环境: CT107单片机综合实训平台 8051，12MHz
  日    期: 2011-8-9
*/
#include <iic.h>
#include "reg52.h"
#include "intrins.h"

#define DELAY_TIME 5

#define SlaveAddrW 0xA0
#define SlaveAddrR 0xA1

//总线引脚定义
sbit SDA = P2^1;  /* 数据线 */
sbit SCL = P2^0;  /* 时钟线 */

void IIC_Delay(unsigned char i)
{
    do{_nop_();}
    while(i--);        
}
//总线启动条件
void IIC_Start(void)
{
    SDA = 1;
    SCL = 1;
    IIC_Delay(DELAY_TIME);
    SDA = 0;
    IIC_Delay(DELAY_TIME);
    SCL = 0;	
}

//总线停止条件
void IIC_Stop(void)
{
    SDA = 0;
    SCL = 1;
    IIC_Delay(DELAY_TIME);
    SDA = 1;
    IIC_Delay(DELAY_TIME);
}

//发送应答
void IIC_SendAck(bit ackbit)
{
    SCL = 0;
    SDA = ackbit;  					// 0：应答，1：非应答
    IIC_Delay(DELAY_TIME);
    SCL = 1;
    IIC_Delay(DELAY_TIME);
    SCL = 0; 
    SDA = 1;
    IIC_Delay(DELAY_TIME);
}

//等待应答
bit IIC_WaitAck(void)
{
    bit ackbit;
	unsigned char i;
    SCL  = 1;
	for(i = 0; i < 200; i++){
		IIC_Delay(DELAY_TIME);
		ackbit = SDA;
		if(ackbit == 0){
			SCL = 0;
			return SUCS;
		}
	}
    return FAIL;
}

//通过I2C总线发送数据
void IIC_SendByte(unsigned char byt)
{
    unsigned char i;

    for(i=0; i<8; i++)
    {
        SCL  = 0;
        IIC_Delay(DELAY_TIME);
        if(byt & 0x80) SDA  = 1;
        else SDA  = 0;
        IIC_Delay(DELAY_TIME);
        SCL = 1;
        byt <<= 1;
        IIC_Delay(DELAY_TIME);
    }
    SCL  = 0;  
}

//从I2C总线上接收数据
unsigned char IIC_RecByte(void)
{
    unsigned char i, da;
    for(i=0; i<8; i++)
    {   
    	SCL = 1;
	IIC_Delay(DELAY_TIME);
	da <<= 1;
	if(SDA) da |= 1;
	SCL = 0;
	IIC_Delay(DELAY_TIME);
    }
    return da;    
}


/*	
 *	写入AT24C02(Page Write)
 *	@param
 *	addrn 首地址
 *	datan 数据序列
 *	n	  字节数
 *	@return
 *	FAIL/SUCS	
 */
bit AT24C02_Write(unsigned char addrn, unsigned char* datan, unsigned char n)
{	
	bit ack_f;
	unsigned char i;
	IIC_Start();
	IIC_SendByte(SlaveAddrW);
	ack_f = IIC_WaitAck();
	if(ack_f == FAIL)	return FAIL;
	IIC_SendByte(addrn);
	ack_f = IIC_WaitAck();
	if(ack_f == FAIL)	return FAIL;
	for(i = 0; i < n; i++){
		IIC_SendByte(datan[i]);
		ack_f = IIC_WaitAck();
		if(ack_f == FAIL)	return FAIL;
	}
	IIC_Stop();
	return SUCS;
}


/*	
 *	读取AT24C02(Sequential Read)
 *	@param
 *	addrn 首地址
 *	datan 数据序列
 *	n	  字节数
 *	@return
 *	FAIL/SUCS	
 */
bit AT24C02_Read(unsigned char addrn, unsigned char* datan, unsigned char n)
{	
	bit ack_f;
	unsigned char i;
	//Dummy Write
	IIC_Start();
	IIC_SendByte(SlaveAddrW);
	ack_f = IIC_WaitAck();
	if(ack_f == FAIL)	return FAIL;
	IIC_SendByte(addrn);
	ack_f = IIC_WaitAck();
	if(ack_f == FAIL)	return FAIL;
	//Read
	IIC_Start();
	IIC_SendByte(SlaveAddrR);
	ack_f = IIC_WaitAck();
	if(ack_f == FAIL)	return FAIL;
	for(i = 0; i < n - 1; i++){
		datan[i] = IIC_RecByte();
		IIC_SendAck(0);
	}
	datan[n-1] = IIC_RecByte();
	IIC_SendAck(1);
	IIC_Stop();
	return SUCS;
}

