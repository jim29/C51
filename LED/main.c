/*
 * LED 流水灯三种模式连续切换
 *		2020/1/19 by MRY
 *
*/

#include <reg51.h>
#include <intrins.h>

#define uchar unsigned char
#define uint unsigned int



/*
 *	延时0.8s                 
 *	时钟12Mhz
 *	
*/

void delay()
{
	uint i, j;
	for (i = 0; i < 1000; i++) {
		for (j = 0; j < 100; j++){
					;
		}
	}			
}


void flow_right()
{
	uchar count = 8;
	uchar aa = 0xFE;
	while(count--) {
		delay();
		P2 = ((P2 & 0x1F) | 0x80);	// P2 = b100X XXXX 138译码Y4. LE = H
		P0 = aa;		
		P2 &= 0x1F;									// P2 = b000X XXXX LE = L
		aa = _cror_(aa, 1);
	}
}

void flow_left()
{
	uchar count = 8;
	uchar aa = 0xFE;
	while(count--) {
	delay();
	P2 = ((P2 & 0x1F) | 0x80);	// P2 = b100X XXXX 138译码Y4. LE = H
	P0 = aa;		
	P2 &= 0x1F;									// P2 = b000X XXXX LE = L
	aa = _crol_(aa, 1);
	}
}

void bling_led()
{
	delay();
	P2 = ((P2 & 0x1F) | 0x80);	// P2 = b100X XXXX 138译码Y4. LE = H
	P0 = 0xFF;		
	P2 &= 0x1F;									// P2 = b000X XXXX LE = L
	delay();
	P2 = ((P2 & 0x1F) | 0x80);	// P2 = b100X XXXX 138译码Y4. LE = H
	P0 = 0x00;		
	P2 &= 0x1F;									// P2 = b000X XXXX LE = L
}


/*************************************
*				main code
**************************************/

void main()
{
	
	const uchar idle = 0;
	const uchar flow_r = 1;
	const uchar flow_l = 2;
	const uchar bling = 3;
	uchar state = idle;
	uchar count = 8;
	while (1){
		switch (state) {
		case 0:
				state = flow_r;
				break;
		case 1:{
				flow_right();
				state = flow_l;
				break;
			}
		case 2:{
				flow_left();
				state = bling;
				break;
			}
		case 3:{
				count = 3;
				while(count--)
					bling_led();
				state = flow_r;
				break;
			}				
		default:
				state = idle;
				
	}
	
	}
}
		
		

