#include <sonic.h>
#include <intrins.h>


//软件延时12us
void Delay12us()		//@12.000MHz
{
	unsigned char i;

	_nop_();
	_nop_();
	i = 33;
	while (--i);
}


/*
 *  超声波测距初始化(T1计数器,不开中断)
 */
void SonicInit()
{
    AUXR |= 0xBF;		//定时器时钟12T模式
    TMOD &= 0x0F;		//设置定时器1模式,16位自动重载
    TL1 = 0;            //T1清零
    TH1 = 0;
    TF1 = 0;            //清除TF1标志      
    P11 = 1;            //初始化
}


/*
 *  发送40khz方波(频率稍大)8次
 */
void SonicSend()
{
    unsigned char i;
    for(i = 0; i < 8; i++){
        P_PWM = 1;
        Delay12us();
        P_PWM = 0;
        Delay12us();
    }
}


/*
 *  超声波接收计数，计算距离，单位mm
 */
unsigned int SonicMeasure()
{
    unsigned int ans;    //测距结果
    unsigned int time;   //计时结果
    //EA = 0;              //关中断
    SonicInit();
    SonicSend();        
    TR1 = 1;            //开始计时 
    while(P11 == 1 && TF1 == 0) {;} //等待触发/溢出
    TR1 = 0;            //停止计时
    if(TF1 == 1)    ans = 9999;    //溢出鲁棒
    else{
        time = TH1;
        time = time << 8;
        time |= TL1;
        ans = time * 0.17;
    }
    //EA = 1;             //开中断
    return ans;
}











