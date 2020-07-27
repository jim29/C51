#include <system.h>
#include <intrins.h>
#include <timer.h>

/*
 *  锁存器控制
 * @param
 * ID 元件序号
 * val  P0口值
 */
void LatchCtrl(unsigned char ID, unsigned char val)
{
    P0 = val;
    P2 = ID << 5;
    _nop_();
    _nop_();
    _nop_();
    P2 &= 0x1F;
    P0 = 0x00;
}

extern unsigned char SYS_STATE;
extern unsigned char SETTING_MODE;
/*
 *  系统初始化,关闭蜂鸣器,LED,继电器,数码管
 *  初始化计时器T0
 *  状态初值
 */
void SysInit()
{
    LatchCtrl(ULN_ID, 0x00);    //关闭蜂鸣器，继电器
    LatchCtrl(LED_ID, 0xFF);    //关闭LED
    LatchCtrl(SEG_COM_ID, 0x00);    //关闭数码管
    Timer0Init();
    SYS_STATE =IDLE;
    SETTING_MODE = NONE_SETTING;
}
