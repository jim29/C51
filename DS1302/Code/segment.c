#include "global.h"
#include "STC15F2K60S2.H"
#include "segment.h"

u8 SegContent[] = {0, 1, 2, 3, 4, 5, 6, 7};

const u8 SEGTABLE[] = {
    0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90
    };  //数码管表  0~9


/**
 *  单位数字显示
 * @param
 * sit  显示位置
 * val  显示值
 */
void SegDisp(u8 sit, u8 val)
{
    LatchCtrl(SEG_COM_ID, 1 << sit);    //阳极
    LatchCtrl(SEG_SEC_ID, SEGTABLE[val]);
}


/**
 *  刷新数码管
 */
void SegFresh()
{
    static u8 i = 0;
    SegDisp(i, SegContent[i]);
    i ++;
    if (i >= 8) i = 0;
} 



