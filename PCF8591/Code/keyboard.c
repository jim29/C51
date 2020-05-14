#include <keyboard.h>
#include <STC15F2K60S2.h>
#include <global.h>	
#include <intrins.h>

/*
 *	延时30ms
 */
void Delay30ms()		//@11.0592MHz
{
	unsigned char i, j, k;

	_nop_();
	_nop_();
	i = 2;
	j = 67;
	k = 183;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}





/*
 *	扫描矩阵键盘
 *	@return 
 *	u8 事件序号
 */
u8 KeyBoardScan()
{
	u8 tmp;
	u8 key = NONE;
	//第一列
	P44 = 0; P42 = 1;
	P3 = 0x3F;
	tmp = P3 & 0x0F;
	if(tmp != 0x0F){
		Delay30ms();
		tmp = P3 & 0x0F;
		if(tmp != 0x0F){
			switch (tmp){
				case 0x0E:	key = NUM_0;
							break;
				case 0x0D:	key = NUM_4;
							break;
				case 0x0B:	key = NUM_8;
							break;
				case 0x07:	key = NONE;
							break;
				default:	key = NONE;
			}
			while(tmp != 0x0F){
				tmp = P3 & 0x0F;
			}
			return key;
		}
	}
	//第二列
	P42 = 0; P44 = 1;
	P3 = 0x3F;
	tmp = P3 & 0x0F;
	if(tmp != 0x0F){
		Delay30ms();
		tmp = P3 & 0x0F;
		if(tmp != 0x0F){
			switch (tmp){
				case 0x0E:	key = NUM_1;
							break;
				case 0x0D:	key = NUM_5;
							break;
				case 0x0B:	key = NUM_9;
							break;
				case 0x07:	key = CLEAR;
							break;
				default:	key = NONE;
			}
			while(tmp != 0x0F){
				tmp = P3 & 0x0F;
			}
			return key;
		}
	}
	//第三列
	P3 = 0x1F;
	tmp = P3 & 0x0F;
	if(tmp != 0x0F){
		Delay30ms();
		tmp = P3 & 0x0F;
		if(tmp != 0x0F){
			switch (tmp){
				case 0x0E:	key = NUM_2;
							break;
				case 0x0D:	key = NUM_6;
							break;
				case 0x0B:	key = NONE;
							break;
				case 0x07:	key = CHANGE;
							break;
				default:	key = NONE;
			}
			while(tmp != 0x0F){
				tmp = P3 & 0x0F;
			}
			return key;
		}
	}
	//第四列
	P3 = 0x2F;
	tmp = P3 & 0x0F;
	if(tmp != 0x0F){
		Delay30ms();
		tmp = P3 & 0x0F;
		if(tmp != 0x0F){
			switch (tmp){
				case 0x0E:	key = NUM_3;
							break;
				case 0x0D:	key = NUM_7;
							break;
				case 0x0B:	key = NONE;
							break;
				case 0x07:	key = INPUT;
							break;
				default:	key = NONE;
			}
			while(tmp != 0x0F){
				tmp = P3 & 0x0F;
			}
			return key;
		}
	}
	return NONE;
}




