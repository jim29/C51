//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//中景园电子
//店铺地址：http://shop73023976.taobao.com/?spm=2013.1.0.0.M4PqC2
//
//  文 件 名   : main.c
//  版 本 号   : v2.0
//  作    者   : HuangKai
//  生成日期   : 2014-0101
//  最近修改   : 
//  功能描述   : OLED IIC接口演示例程(51系列)
//              说明: 
//              ----------------------------------------------------------------
//              GND    电源地
//              VCC  接5V或3.3v电源
//              D0   P1^0（SCL_OL）
//              D1   P1^1（SDA_OL）
//              RES  接高
//              DC   接地
//              CS   接地                
//              ----------------------------------------------------------------
// 修改历史   :
// 日    期   : 
// 作    者   : HuangKai
// 修改内容   : 创建文件
//版权所有，盗版必究。
//Copyright(C) 中景园电子2014/3/16
//All rights reserved
//******************************************************************************/
#include <oled.h>


/**********************************************
//IIC Start
**********************************************/
void IIC_Start()
{
   SCL_OL = high;		
   SDA_OL = high;
   SDA_OL = low;
   SCL_OL = low;
}

/**********************************************
//IIC Stop
**********************************************/
void IIC_Stop()
{
   SCL_OL = low;
   SDA_OL = low;
   SCL_OL = high;
   SDA_OL = high;
}
/**********************************************
// IIC Write byte
**********************************************/
void Write_IIC_Byte(unsigned char IIC_Byte)
{
	unsigned char i;
	for(i=0;i<8;i++)		
	{
		if(IIC_Byte & 0x80)
		SDA_OL=high;
		else
		SDA_OL=low;
		SCL_OL=high;
		SCL_OL=low;
		IIC_Byte<<=1;
	}
	SDA_OL=1;
	SCL_OL=1;
	SCL_OL=0;
}
/**********************************************
// IIC Write Command
**********************************************/
void Write_IIC_Command(unsigned char IIC_Command)
{
   IIC_Start();
   Write_IIC_Byte(0x78);            //Slave address,SA0=0
   Write_IIC_Byte(0x00);			//write command
   Write_IIC_Byte(IIC_Command); 
   IIC_Stop();
}
/**********************************************
// IIC Write Data
**********************************************/
void Write_IIC_Data(unsigned char IIC_Data)
{
   IIC_Start();
   Write_IIC_Byte(0x78);			//D/C#=0; R/W#=0
   Write_IIC_Byte(0x40);			//write data
   Write_IIC_Byte(IIC_Data);
   IIC_Stop();
}
/********************************************
// Set_Background
********************************************/
void Set_Background()
{
	unsigned char m,n;
	for(m=0;m<8;m++)
	{
		Write_IIC_Command(0xb0+m);		//page0-page1
		Write_IIC_Command(0x00);		//low column start address
		Write_IIC_Command(0x10);		//high column start address
		for(n=0;n<128;n++)
		{
			if((n == 63 || n == 64 || n== 65) && (m == 2))
			{
				Write_IIC_Data(0x38);
			}
			else if((n == 63 || n == 64 || n== 65) && (m == 5))
			{
				Write_IIC_Data(0x70);
			}
			else Write_IIC_Data(0x00);
		}
	}
}


/**************OLED Init*************/
void Initial_M096128x64_ssd1306()
{
	Write_IIC_Command(0xAE);   //display off
	Write_IIC_Command(0x20);	//Set Memory Addressing Mode	
	Write_IIC_Command(0x10);	//00,Horizontal Addressing Mode;01,Vertical Addressing Mode;10,Page Addressing Mode (RESET);11,Invalid
	Write_IIC_Command(0xb0);	//Set Page Start Address for Page Addressing Mode,0-7
	Write_IIC_Command(0xc8);	//Set COM Output Scan Direction
	Write_IIC_Command(0x00);//---set low column address
	Write_IIC_Command(0x10);//---set high column address
	Write_IIC_Command(0x40);//--set start line address
	Write_IIC_Command(0x81);//--set contrast control register
	Write_IIC_Command(0xdf);
	Write_IIC_Command(0xa1);//--set segment re-map 0 to 127
	Write_IIC_Command(0xa6);//--set normal display
	Write_IIC_Command(0xa8);//--set multiplex ratio(1 to 64)
	Write_IIC_Command(0x3F);//
	Write_IIC_Command(0xa4);//0xa4,Output follows RAM content;0xa5,Output ignores RAM content
	Write_IIC_Command(0xd3);//-set display offset
	Write_IIC_Command(0x00);//-not offset
	Write_IIC_Command(0xd5);//--set display clock divide ratio/oscillator frequency
	Write_IIC_Command(0xf0);//--set divide ratio
	Write_IIC_Command(0xd9);//--set pre-charge period
	Write_IIC_Command(0x22); //
	Write_IIC_Command(0xda);//--set com pins hardware configuration
	Write_IIC_Command(0x12);
	Write_IIC_Command(0xdb);//--set vcomh
	Write_IIC_Command(0x20);//0x20,0.77xVcc
	Write_IIC_Command(0x8d);//--set DC-DC enable
	Write_IIC_Command(0x14);//
	Write_IIC_Command(0xaf);//--turn on oled panel 
}

/*
*	设置显示数字	测试
* val[]	显示数据矩阵
* x			col位置 SEG_X
*/
void Num_Display(unsigned char val[], unsigned char x)
{
	unsigned char m,n,i = 0;
	for(m=1;m<7;m++)
	{
		Write_IIC_Command(0xb0+m);		//page-page7
		Write_IIC_Command(0x00 + (x % 16));		//low column start address
		Write_IIC_Command(0x10 + (x / 16));		//high column start address
		for(n = 0; n < 21; n++)
		{
			Write_IIC_Data(val[i]);
			i ++;
		}
	}
}


/*数字灭*/
void Num_OFF(unsigned char x)
{
	unsigned char m,n,i = 0;
	for(m=1;m<7;m++)
	{
		Write_IIC_Command(0xb0+m);		//page-page7
		Write_IIC_Command(0x00 + (x % 16));		//low column start address
		Write_IIC_Command(0x10 + (x / 16));		//high column start address
		for(n = 0; n < 21; n++)
		{
			Write_IIC_Data(0x00);
			i ++;
		}
	}
}

