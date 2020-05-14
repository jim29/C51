#include <segment.h>
#include <reg51.h>



// 数码管共阳码表 0,1,2,3,4,5,6,7,8,9
unsigned char code seg_table[] = {
	0xC0, 0xF9, 0xA4, 0xB0,
	0x99, 0x92, 0x82, 0xF8,
	0x80, 0x90};






// =====延时ms======
void DelayMs(unsigned char xms)
{
	unsigned char i, j;
	for (i = 0; i < 120; i ++)
		for (j = 0; j < xms; j++)
			;
}




// ======数码管显示=======
// 输入显示数字 uchar 两位
void SegDisplay(unsigned char num)
{
	unsigned char ge, shi;
	ge = num % 10;
	shi = num / 10;
	
	
	// 显示十位
	P0 = 0x40;		// com7 = 1
	// P2 = 110x XXXX
	P2 |= 0xC0;		// 置1
	P2 &= 0xDF;		// 置0
	P2 = 0x00;		
	P0 = seg_table[shi];
	// P2 = 111x XXXX
	P2 |= 0xE0;		// 置1
	P2 = 0x00;
	DelayMs(5);
	
	
	// 显示个位
	P0 = 0x80;		// com8 = 1
	// P2 = 110x XXXX
	P2 |= 0xC0;		// 置1
	P2 &= 0xDF;		// 置0
	P2 = 0x00;
	P0 = seg_table[ge];
	// P2 = 111x XXXX
	P2 |= 0xE0;		// 置1
	P2 = 0x00;
	DelayMs(5);
}