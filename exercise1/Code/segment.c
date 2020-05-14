#include <segment.h>
#include <global.h>
#include <STC15F2K60S2.h>

u8 code SegTable[] = {
	0xc0,	0xf9, 0xa4,	0xb0, 0x99,	0x92, 0x82, 0xf8,	0x80,	0x90	//共阳段码表0~9
};
u8 code ComTable[] = {
	0x01,	0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80	//位选码0~8
};

	
/*
	数码管显示（单）
	@param	
	COM 位码，10进制1~8
	val	段码，10进制0~9
*/
void SegDisplay(u8 COM, u8 val)
{
	LatchControl(SEG_COM_ID, ComTable[COM - 1]);
	LatchControl(SEG_SEC_ID, SegTable[val]);
}


