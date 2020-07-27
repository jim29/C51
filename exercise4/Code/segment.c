#include <segment.h>

//数码管表 0~9  '-' 'C' 空
code unsigned char SEG_TABLE[] = {
    0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0xBF,0xC6,0xFF
};

/*
 *  单个数码管显示
 * @param
 * i    显示位置    0~7
 * val  显示数值    0~12
 */
void SegDisp(unsigned char i, unsigned char val)
{
    LatchCtrl(SEG_COM_ID, 1 << i);
    LatchCtrl(SEG_SEC_ID, SEG_TABLE[val]);
}


/*
 *  刷新8位数码管
 * @param
 * content[]    显示的8位数字
 */
void SegFresh(unsigned char content[])
{
    static unsigned char i = 0;
    if(i >= 8)  i = 0;
    SegDisp(i, content[i]);
    i ++;
}


