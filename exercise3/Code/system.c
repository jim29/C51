#include <system.h>
#include <STC15F2K60S2.h>
#include <INTRINS.H>

/*
 *  锁存器控制，赋值锁存P0口
 * @param
 *  ID  控制元件的Y值
 *  val P0口值
 */ 
void LatchCtrl(unsigned char ID, unsigned char val)
{
    P0 = val;
    P2 |= ID << 5;
    _nop_();
    _nop_();
    _nop_();
    P2 &= 0x1F;
}


/*
 *  系统初始化,关闭LED,关闭蜂鸣器,关闭继电器，关闭数码管
 * 
 */
void SysInit()
{
    LatchCtrl(ULN_ID, 0x00);
    LatchCtrl(LED_ID, 0xFF);
    LatchCtrl(SEG_COM_ID, 0x00);
}