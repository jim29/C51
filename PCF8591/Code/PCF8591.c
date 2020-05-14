#include <global.h>
#include <intrins.h>
#include <STC15F2K60S2.h>
#include <iic.h>

#define SlaveAddrW 0x90
#define SlaveAddrR 0x91

/*
 *	初始化PCF8591
 *	@param
 * 	channel 读取的通道
 */
void PCF8591_Init(u8 channel)
{
	IIC_Start();
	IIC_SendByte(SlaveAddrW);
	IIC_WaitAck();	
	IIC_SendByte(channel);	//关闭DA,AD通道选择
	IIC_WaitAck();
	IIC_SendByte(0x00);	//DA拉低
	IIC_WaitAck();
	IIC_Stop();
}

/*
 *	读取AD
 *	@return
 *	1Byte数据
 */
u8 PCF8591_Read()
{
	u8 da;
	IIC_Start();
	IIC_SendByte(SlaveAddrR);
	IIC_WaitAck();
	da = IIC_RecByte();
	IIC_SendAck(1);
	IIC_Stop();
	return da;
}
