#include <global.h>
#include <STC15F2K60S2.h>



/* 			
@param	ID 锁存器编号
	val P0值16进制
*/
void LatchControl(u8 ID, u8 val)
{
	P2 &= 0x1F;	
	P0 = val;
	P2 |= ID << 5;
	P2 &= 0x1F;
}


/*
@param	

*/
void InitBuzzer()
{
	LatchControl(ULN_ID, 0x00);
	
}



