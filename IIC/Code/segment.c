#include <global.h>
#include <STC15F2K60S2.H>
#include <segment.h>

u8 code SegTable[] = {
	0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90, 0xFF
};	//数码管0~9, 空

u8 SegContent[] = {1, 2, 3, 4, 10, 10, 10, 10};

/*
 *	数码管单位显示
 * @param
 * sit 显示位置 0~7
 * val 显示值
 */
void SegDisp(u8 sit, u8 val)
{
	LatchCtrl(SEG_SEC_ID, 0xFF);
	LatchCtrl(SEG_COM_ID, 1 << sit);
	LatchCtrl(SEG_SEC_ID, SegTable[val]);  
}

/*
 *	数码管刷新
 */
void SegFresh()
{
	static i = 0;
	SegDisp(i, SegContent[i]);
	i ++;
	if(i == 8)	i = 0;
}