#include <system.h>
#include <intrins.h>




/*
 *	锁存器控制元件
 *	ID	元件序号	val P0数值
 */
void Latch_Ctrl(unsigned char ID, unsigned char val)
{
	P0 = val;
	P2 = ID << 5;
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	P2 = P2 & 0x1F;
}


/* 系统初始化 */
void System_Init()
{
	Latch_Ctrl(LED_ID, 0xFF);	//关闭LED灯
	Latch_Ctrl(ULN_ID, 0x00);	//关闭蜂鸣器，继电器
	Latch_Ctrl(SEG_COM_ID, 0x00);	//关闭数码管
}


/* Delay */
