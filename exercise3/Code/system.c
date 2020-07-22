#include <system.h>
#include <intrins.h>

int SYSTICK;    //系统时钟，100us刷新
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
 *  系统TICK计时器，分时切片
 */
void Timer_0_Init(void)		//100微秒@12.000MHz
{
	AUXR |= 0x80;		//定时器时钟1T模式
	TMOD &= 0xF0;		//设置定时器模式
	TL0 = 0x50;		//设置定时初值
	TH0 = 0xFB;		//设置定时初值
	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时器0开始计时
    ET0 = 1;        //打开T0中断
    EA = 1;         //打开全局中断
}


/*
 *  系统初始化,关闭LED,关闭蜂鸣器,关闭继电器，关闭数码管,打开T0计时器
 */
void SysInit()
{
    LatchCtrl(ULN_ID, 0x00);
    LatchCtrl(LED_ID, 0xFF);
    LatchCtrl(SEG_COM_ID, 0x00);
    Timer_0_Init();
}


