#include <global.h>
#include <STC15F2K60S2.H>


/*
 *	锁存器控制
 *	@param
 *	ID	控制器序号
 *	val	P0值
 */
void LatchCtrl(u8 ID, u8 val)
{
	P0 = val;
	P2 = ID << 5;
	P2 = 0x00;
	P0 = 0x00;	//默认拉低
}

/*
 *	系统初始化
 */
void SysInit()
{
	LatchCtrl(ULN_ID, 0x00);		//关闭蜂鸣器
	LatchCtrl(LED_ID, 0xFF);		//关灯
	LatchCtrl(SEG_COM_ID, 0x00);	//关数码管
}