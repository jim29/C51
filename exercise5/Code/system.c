#include <system.h>
#include <intrins.h>

void some_nop()
{
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
}



void latch_ctrl(unsigned char ID, unsigned char val)
{
	P0 = val;
	P2 = P2 | (ID << 5);
	some_nop();
	P2 = P2 & 0x1F;
	P0 = 0x00;
}


void system_init()
{
	latch_ctrl(LED_ID, 0xFF);
	latch_ctrl(SEG_COM_ID, 0x00);
	latch_ctrl(ULN_ID, 0x00);
}