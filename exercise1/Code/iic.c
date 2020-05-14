/*
  ����˵��: IIC������������
  ��������: Keil uVision 4.10 
  Ӳ������: CT107��Ƭ���ۺ�ʵѵƽ̨ 8051��12MHz
  ��    ��: 2011-8-9
*/

#include "reg52.h"
#include "intrins.h"

#define DELAY_TIME 5

#define SlaveAddrW 0xA0
#define SlaveAddrR 0xA1

//�������Ŷ���
sbit SDA = P2^1;  /* ������ */
sbit SCL = P2^0;  /* ʱ���� */

void IIC_Delay(unsigned char i)
{
    do{_nop_();}
    while(i--);        
}
//������������
void IIC_Start(void)
{
    SDA = 1;
    SCL = 1;
    IIC_Delay(DELAY_TIME);
    SDA = 0;
    IIC_Delay(DELAY_TIME);
    SCL = 0;	
}

//����ֹͣ����
void IIC_Stop(void)
{
    SDA = 0;
    SCL = 1;
    IIC_Delay(DELAY_TIME);
    SDA = 1;
    IIC_Delay(DELAY_TIME);
}

//����Ӧ��
void IIC_SendAck(bit ackbit)
{
    SCL = 0;
    SDA = ackbit;  					// 0��Ӧ��1����Ӧ��
    IIC_Delay(DELAY_TIME);
    SCL = 1;
    IIC_Delay(DELAY_TIME);
    SCL = 0; 
    SDA = 1;
    IIC_Delay(DELAY_TIME);
}

//�ȴ�Ӧ��
bit IIC_WaitAck(void)
{
    bit ackbit;
	
    SCL  = 1;
    IIC_Delay(DELAY_TIME);
    ackbit = SDA;
    SCL = 0;
    IIC_Delay(DELAY_TIME);
    return ackbit;
}

//ͨ��I2C���߷�������
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

//��I2C�����Ͻ�������
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
	д���ַ����
	@param
	addr	��ַ0~FF
	val1	д����ֵ1
	val2	д����ֵ2
*/
void WriteAddr(unsigned char addr, unsigned char val1, unsigned char val2)
{
	IIC_Start();
	IIC_SendByte(SlaveAddrW);
	if(IIC_WaitAck());
	IIC_SendByte(addr);
	if(IIC_WaitAck());
	IIC_SendByte(val1);
	if(IIC_WaitAck());
	IIC_SendByte(val2);
	if(IIC_WaitAck());
	IIC_Stop();
}


/*
	��ȡ��ַ����
	@param
	addr	��ַ0~FF
	val1	��ȡ��ֵ1
	val2	��ȡ��ֵ2
*/
void ReadAddr(unsigned char addr, unsigned char * val1, unsigned char * val2)
{

	IIC_Start();
	IIC_SendByte(SlaveAddrW);
	if(IIC_WaitAck());
	IIC_SendByte(addr);
	if(IIC_WaitAck());
	IIC_Start();
	IIC_SendByte(SlaveAddrR);
	if(IIC_WaitAck());
	*val1 = IIC_RecByte();
	IIC_SendAck(0);
	*val2 = IIC_RecByte();
	IIC_SendAck(1);
	IIC_Stop();
	
}


