/*
 * 	60s计时器, LED循环流水灯
 *	
 *			2020/1/22 by MRY
 */
 

#include <reg51.h>
#include <intrins.h>
#define FOSC 12000000L		// 12Mhz晶振
#define T50MS (65536 - 50000)		// 计时50ms
#define T25MS (65536 - 25000)		// 计时25ms

unsigned int t0_cnt = 0; 		// T0计数次数
unsigned int t1_cnt = 0; 		// T1计数次数
unsigned char seg_num = 0;	// 数码管显示数 0~59	
unsigned char led = 0xFE;		// LED状态

sfr AUXR = 0x8E;		// Auxiliary Register



// 数码管共阳码表 0,1,2,3,4,5,6,7,8,9
unsigned char code seg_table[] = {
	0xC0, 0xF9, 0xA4, 0xB0,
	0x99, 0x92, 0x82, 0xF8,
	0x80, 0x90};

	
/*
 * 延时xms
 */
void delay_ms(unsigned int x)
{
	unsigned int i, j;
	for (i = 0; i < x; i++)
		for (j = 0; j < 130; j++)
			;
}
	
/*
 * LED闪烁T0中断 125ms
*/
void t0_500ms () interrupt 1
{
	t0_cnt++;
	if (t0_cnt >= 5) {
		t0_cnt = 0;
		led = _crol_(led, 1);
		P0 = led;
		P2 |= 0x80;		// ABC = 100, Y7C = 1
		P2 &= 0x1F;		// ABC = 000, 锁存
	}
	else
		t0_cnt = t0_cnt;
}
	
	
	

/*
 *	数码管T1中断更新 1s
*/
void t1_1s() interrupt 3
{
		t1_cnt++;
		if (t1_cnt >= 20)	{	// 计时1s
			t1_cnt = 0; 
			if (seg_num >= 59)
				seg_num = 0;
			else
				seg_num++;
		}
		else
			t1_cnt = t1_cnt;
}
	


/*
* 数码管显示
*/
void seg_display()
{
	unsigned char shi, ge;
	shi = seg_num / 10;
	ge = seg_num % 10;
	P0 = seg_table[shi];	
	P2 |= 0xE0;				// ABC = 111, Y7C = 1
	P2 &= 0x1F;				// ABC = 000, 锁存
	P0 = 0x01;				// 十位
	P2 |= 0xD0; 			// ABC = 110, Y6C = 1
	P2 &= 0x1F;				// ABC = 000, 锁存
	delay_ms(5);
	
	P0 = seg_table[ge];
	P2 |= 0xE0;				// ABC = 111, Y7C = 1
	P2 &= 0x1F;				// ABC = 000, 锁存
	P0 = 0x02;				// 个位
	P2 |= 0xD0; 			// ABC = 110, Y6C = 1
	P2 &= 0x1F;				// ABC = 000, 锁存
	delay_ms(5);
}
	

void main()
{
	AUXR &= 0x3F;			//  12T分频模式
	TMOD = 0x00;			// 16位自动重载
	TL0 = T25MS % 256;
	TH0 = T25MS / 256;
	TL1 = T50MS % 256;
	TH1 = T50MS / 256;
	TR0 = 1;
	ET0 = 1;
	TR1 = 1;
	ET1 = 1;
	EA = 1;
	
	
	while(1) {
		seg_display();
	
	}	
	
}
