#ifndef _IIC_H
#define _IIC_H

#define FAIL 0	//ACK判断
#define SUCS 1

void IIC_Start(void);
void IIC_Stop(void);
void IIC_SendAck(bit ackbit);	
bit IIC_WaitAck(void);	
void IIC_SendByte(unsigned char byt);
unsigned char IIC_RecByte(void);

#endif