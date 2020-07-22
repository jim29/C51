#include <segment.h>


//数码管码表 0~9
code unsigned char segment_table[] = {
    0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90
};


/*
 *  数码管显示单个字符
 * @param
 *  index   显示位置 0~7
 *  val     显示数值 0~9
 */
void SegmentDisp(unsigned char index, unsigned char val)
{
    LatchCtrl(SEG_COM_ID, 1 << index);
    LatchCtrl(SEG_SEC_ID, segment_table[val]);
}


/*
 *  数码管刷新显示
 */
void SegmentFresh(unsigned char index[], unsigned char content[])
{
    static unsigned char i = 0; //静态存储显示位置
    if(i >= SEG_INDEX_MAX)  i = 0;
    SegmentDisp(index[i], content[i]);
    i ++;    
}