#include "global.h"
#include "STC15F2K60S2.H"
#include "intrins.h"


// 简短延时
void Delay()
{
    _nop_();
    _nop_();
    _nop_();
    _nop_();
}


/**
 *  锁存器控制
 * @param
 *  ID  控制元件序号
 * val  P0值
 */
void LatchCtrl(u8 ID, u8 val)
{
    P0 = val;
    P2 = (P2 & 0x1F) | ID << 5;
    Delay();
    P2 = P2 & 0x1F;
    Delay();
		P0 = 0x00;
}




/**
 *  系统初始化
 *  关闭蜂鸣器,LED,数码管
 */
void SysInit()
{
    LatchCtrl(ULN_ID, 0x00);
    LatchCtrl(LED_ID, 0xFF);
    LatchCtrl(SEG_COM_ID, 0x00);
}
 