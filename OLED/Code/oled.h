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
//              D0   P1^0（SCL）
//              D1   P1^1（SDA）
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



#ifndef	__OLED_H
#define	__OLED_H
#include <system.h>

#define high 1
#define low 0



/*************Pin Define***************/
sbit SCL_OL = P3^4;
sbit SDA_OL = P3^5;


void Initial_M096128x64_ssd1306();
void Set_Background();
void Num_Display(unsigned char val[], unsigned char x);
void Num_OFF(unsigned char x);





#endif