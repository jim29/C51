/*
 * 	静态数码管显示
 *	循环0.5ms 依次显示0~9
 *			2020/1/21 by MRY
 */
 

#include <reg51.h>

// 数码管共阳码表 0,1,2,3,4,5,6,7,8,9
unsigned char code seg_table[] = {
	0xC0, 0xF9, 0xA4, 0xB0,
	0x99, 0x92, 0x82, 0xF8,
	0x80, 0x90};


// 延时Xms
void delay_ms(unsigned int x)
{
	unsigned int i, j;
	for (i = 0; i <= x; i++)
		for(j = 0; j <= 120; j++)
			;
}



void main()
{
	while(1) {
		unsigned char num;		
		for (num = 0; num <= 9; num++) {
			P2 = P2 | 0xE0;				// ABC = 111, Y7C = 1
			P0 = seg_table[num];	// 显示num
			P2 = P2 & 0x1F;				// ABC = 000, 锁存
			P2 = P2 | 0xD0; 			// ABC = 110, Y6C = 1
			P0 = 0xFF;						// 点亮所有位
			P2 = P2 & 0x1F;				// ABC = 000, 锁存
			delay_ms(1000);
		}
	}

}
