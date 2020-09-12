#include <segment.h>
code unsigned char SEG_TABLE[] = {
	0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90
};
extern unsigned char SEG_CONTENT[];

void seg_disp(unsigned char i, unsigned  char val)
{
	latch_ctrl(SEG_COM_ID, 1 << i);
	latch_ctrl(SEG_SEC_ID, SEG_TABLE[val]);
}

void seg_fresh()
{
	static unsigned char i = 0;
	seg_disp(i, SEG_CONTENT[i]);
	i ++;
	if(i >= 8) i = 0; 
}