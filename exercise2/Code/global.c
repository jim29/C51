#include <global.h>
#include <STC15F2K60S2.h>

/*
 *	138，573锁存控制
 *	@param 
 * 	ID	元件序号
 *	val P0值 16进制
 */
void LatchCtrl(u8 ID, u8 val)
{
	P0 = val;
	P2 = ID << 5;
	P2 = 0x00;
	P0 = 0x00;
}


/*
 *  初始化系统，关闭蜂鸣器,数码管，LED
 *	@param
 *
 */
 void SysInit()
 {
	 LatchCtrl(ULN_ID, 0x00);
	 LatchCtrl(SEG_COM_ID, 0x00);
	 LatchCtrl(LED_ID, 0xFF);
 }