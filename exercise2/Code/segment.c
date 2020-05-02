#include <segment.h>
#include <global.h>
#define SEG_N 8	//显示位数

u8 SegContent[] = {
	10, 10, 10, 10, 10, 10, 10, 10
};
u8 code SegTable[] = {
	0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90,
	0xFF,
	0xBF,
	0xC6,
	0x8C,
	0x86,
	0xC8
};	//数码管码表0~9,
    // 空 10
	// -  11
	// C  12
	// P  13
	// E  14
	// N  15
	
/*
u8 code SegSit[] = {
	3, 4, 5, 6, 7
};	//数码管显示位置
*/


/*
 *	显示单个数字
 *	@param
 *	sit	数字位置
 *  val 数字值
 */
void SegDisp(u8 sit, u8 val)
{
	LatchCtrl(SEG_COM_ID, 1 << sit);
	LatchCtrl(SEG_SEC_ID, SegTable[val]);
}


/*
 *	刷新数码管
 */
void SegFresh()
{
	static u8 seg_sit = 0;
	SegDisp(seg_sit, SegContent[seg_sit]);
	seg_sit ++;
	if(seg_sit == SEG_N)	seg_sit = 0;
}



	
	
	