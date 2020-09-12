#include <system.h>
#include <oled.h>
#include <picture.h>
#include <ds1302.h>


unsigned char HOUR_RUN = 22;    //ʵʱʱ����ֵ
unsigned char MIN_RUN = 3;
unsigned char SEC_RUN = 50;
unsigned char SEG_X[] = {14, 38, 70, 94};	//����λ��
void DS1302_ReadTime();
void DS1302_WriteTime();

void main()
{
	System_Init();
	Latch_Ctrl(LED_ID, 0xFE);
	Initial_M096128x64_ssd1306();
	Set_Background();
	DS1302_WriteTime();
	while(1)
	{
		DS1302_ReadTime();
		Num_Display(NUM_TAB[HOUR_RUN / 10], SEG_X[0]);
		Num_Display(NUM_TAB[HOUR_RUN % 10], SEG_X[1]);
		Num_Display(NUM_TAB[MIN_RUN / 10], SEG_X[2]);
		Num_Display(NUM_TAB[MIN_RUN % 10], SEG_X[3]);		
	}
}


/*
 *  DS1302ʱ��д��
 * @param
 * hour min sec д���Сʱ,����,��
 */
void DS1302_WriteTime()
{
    Write_Ds1302(SEC_WRITE_ADDR,  ((SEC_RUN / 10) << 4) + (SEC_RUN % 10));  //д����
    Write_Ds1302(MIN_WRITE_ADDR,  ((MIN_RUN / 10) << 4) + (MIN_RUN % 10));  //д���
    Write_Ds1302(HOUR_WRITE_ADDR, ((HOUR_RUN / 10) << 4) + (HOUR_RUN % 10)); //д��ʱ
}


/*
 *  ��ȡDS1302��ʱ����
 */
void DS1302_ReadTime()
{
    unsigned char read_data, shi, ge;
    read_data = Read_Ds1302(SEC_READ_ADDR);
    shi = read_data >> 4;
    ge = read_data & 0x0F;
    SEC_RUN = shi * 10 + ge;
    read_data = Read_Ds1302(MIN_READ_ADDR);
    shi = read_data >> 4;
    ge = read_data & 0x0F;
    MIN_RUN = shi * 10 + ge;
    read_data = Read_Ds1302(HOUR_READ_ADDR);
    shi = read_data >> 4;
    ge = read_data & 0x0F;
    HOUR_RUN = shi * 10 + ge;
}






