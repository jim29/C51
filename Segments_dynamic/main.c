/*
 * 	动态数码管显示
 *	
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
		for (num = 1; num <= 8; num++) {
			P2 = P2 | 0xE0;				// ABC = 111, Y7C = 1
			P0 = seg_table[num];	// 显示num
			P2 = P2 & 0x1F;				// ABC = 000, 锁存
			P0 = 0x00;						// 消影
			P2 = P2 | 0xD0; 			// ABC = 110, Y6C = 1
			// 依次点亮位
			switch(num) {
				case 1: P0 = 0x01;
								break;
				case 2: P0 = 0x02;
								break;
				case 3:	P0 = 0x04;
								break;
				case 4: P0 = 0x08;
								break;
				case 5: P0 = 0x10;
								break;
				case 6: P0 = 0x20;
								break;
				case 7: P0 = 0x40;
								break;
				case 8: P0 = 0x80;
								break;
				default:
								P0 = 0x01;
			}
			P2 = P2 & 0x1F;				// ABC = 000, 锁存
			delay_ms(1);
		}
	}

}
