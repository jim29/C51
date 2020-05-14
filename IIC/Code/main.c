#include <STC15F2K60S2.H>
#include <global.h>
#include <segment.h>
#include <iic.h>
#define	Addr 0x22

extern u8 SegContent[8];
bit WriteFlag = FAIL;
bit ReadFlag = FAIL;

void main()
{
	SysInit();
	WriteFlag = AT24C02_Write(Addr, SegContent, 8);
	while(WriteFlag == FAIL){
		WriteFlag = AT24C02_Write(Addr, SegContent, 8);
	}
	ReadFlag = AT24C02_Read(Addr, SegContent, 8);
	while(ReadFlag == FAIL){
		ReadFlag = AT24C02_Read(Addr, SegContent, 8);
	}
	while(1){
		if(ReadFlag == FAIL)
			LatchCtrl(LED_ID, 0x7F);
		SegFresh();
	}
}