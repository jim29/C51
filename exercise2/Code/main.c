#include <STC15F2K60S2.h>
#include <intrins.h>
#include <global.h>
#include <segment.h>
#include <timer.h>
#include <onewire.h>
#include <relay.h>
#include <keyboard.h>
#include <iic.h>
#define Address 0x22

u16 SysTick = 0;
u8 KeyPressed = NONE;
u8 State = IDLE;
extern u8 SegContent[];	//数码管显示内容
u8 PW_Saved[] = {8, 8, 8, 8, 8, 8};	//保存的密码(本地)
u8 PW_Input[] = {10,10,10,10,10,10};//输入的数字
u8 InputCnt = 0;//输入个数
u8 WaitFlag = 0;//等待5s
u16 WaitCnt = 0;
u8 ChangeFlag = 0;


void HandleEvent(u8 key);
void IdleInit();
void OpenInit();
void Delay5000ms();
void SaveNewPW();


bit WriteFlag = FAIL;
bit ReadFlag = FAIL;


/*----------------------
-------main-------------
-----------------------*/
void main()
{
	//初始化
	SysInit();
	Timer0Init();
	IdleInit();
	//读取存储的密码
	ReadFlag = AT24C02_Read(Address, PW_Saved, 6);
	while(ReadFlag == FAIL){
		ReadFlag = AT24C02_Read(Address, PW_Saved, 6);
	}
	while(1){
		u16 SysTickTmp = SysTick;
		
		//10ms扫描键盘
		if(SysTick % 20 == 0){	
			KeyPressed = KeyBoardScan();
			if(KeyPressed != NONE)		HandleEvent(KeyPressed);
		}
		//计时器判定
		if(WaitFlag == 1){
			WaitCnt ++;
			if(WaitCnt >= 10000){ //5s
				State = IDLE;
				IdleInit();
			}
		}
		//20s设定溢出
		if(SysTick > 40000)	SysTick = 0;
		while(SysTickTmp == SysTick);
	}
}


// 500us 系统刷新
void T0Inter() interrupt 1
{
	SysTick ++;
	//数码管刷新 3ms
	if(SysTick % 6 == 0)	
		SegFresh();
}	


/*
 *	处理按键事件
 */
void HandleEvent(u8 key)
{
	u8 i = 0; 
	//输入的是数字
	if(key <= 9){
		//输入模式
		if(State == INPUT_MOD){
			//挪动数字
			for(i = 3; i <= 7; i++){
				SegContent[i-1] = SegContent[i];
			}
			SegContent[7] = key;
			InputCnt ++;
			if(InputCnt == 6){
				//输入完成，检查密码
				for(i = 2; i <= 7; i++){
					if(SegContent[i] != PW_Saved[i-2]){//出现错误
						LatchCtrl(LED_ID, 0xFE);//L1亮
						Delay5000ms();//亮5s
						LatchCtrl(LED_ID, 0xFF);
						State = IDLE;
						IdleInit();
						break;
					}
				}
				if(i == 8){//输入正确
					State = OPEN_MOD;
					OpenInit();
				}
			}
		}
		//更换密码模式
		else if(State == CHANGE_MOD && ChangeFlag == 0){
			//挪动数字
			for(i = 3; i <= 7; i++){
				SegContent[i-1] = SegContent[i];
			}
			SegContent[7] = key;
			InputCnt ++;
			if(InputCnt == 6){
				//输入完成
				ChangeFlag = 1;	
			}
		}
		else
			;
	}
	//输入的是指令
	else{
		if(key == INPUT){
			if(State == IDLE){
				State = INPUT_MOD;
				SegContent[0] = 11;	//"-"
				LatchCtrl(LED_ID, 0xBF);//L7亮
			}
		}
		else if(key == CHANGE){
			if(State == OPEN_MOD){
				State = CHANGE_MOD;
				SegContent[0] = 12;//"C"
				WaitFlag = 0; //中断计时
				WaitCnt = 0;
				LatchCtrl(LED_ID, 0x7F);//L8亮
				for(i = 1; i < 8; i++)	//清屏
					SegContent[i] = 10;
			}
			else if(State == CHANGE_MOD && ChangeFlag == 1){
				//存储新密码
				SaveNewPW();
				//更新完成，退出进入开门界面
				ChangeFlag = 0;
				State = OPEN_MOD;
				OpenInit();
			}
		}
		else if(key == CLEAR){
			if(State == INPUT_MOD || State == CHANGE_MOD){
				InputCnt = 0;
				ChangeFlag = 0;
				for(i = 1; i < 8; i++)
					SegContent[i] = 10;
			}
		}
		else{
			;
		}
	}
}
 
 
/*
 * Idle模式处理
 */
void IdleInit()
{
	u8 i;
	InputCnt = 0;
	Relay_m1();
	LatchCtrl(LED_ID, 0xFF);
	InputCnt = 0;
	WaitCnt = 0;
	WaitFlag = 0;
	for(i = 0; i < 8; i++)
		SegContent[i] = 10;
}

/*
 * 开门模式处理
 */
void OpenInit()
{
	InputCnt = 0;
	LatchCtrl(LED_ID, 0xFF);
	//显示OPEN
	SegContent[0] = 0;
	SegContent[1] = 10;
	SegContent[2] = 10;
	SegContent[3] = 10;
	SegContent[4] = 0;
	SegContent[5] = 13;
	SegContent[6] = 14;
	SegContent[7] = 15;
	Relay_m2();//打开继电器
	WaitFlag = 1; //开始等待
}

/*
 *	延时5s
 */ 
void Delay5000ms()		//@11.0592MHz
{
	unsigned char i, j, k;

	_nop_();
	_nop_();
	i = 211;
	j = 30;
	k = 11;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}
 
 
/*
 *	存储新密码
 */
void SaveNewPW()
{
	u8 i;
	//本地更新
	for(i = 0; i < 6; i++)
		PW_Saved[i] = SegContent[i+2];
	//Flash更新
	WriteFlag = AT24C02_Write(Address, PW_Saved, 6);
	while(WriteFlag == FAIL){
		WriteFlag = AT24C02_Write(Address, PW_Saved, 6);
	}
}
 



 
 
 