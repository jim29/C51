/* 模拟题 */
#include <system.h>
#include <iic.h>
#include <segment.h>

code unsigned char ADDR_READ = 0xA1;
code unsigned char ADDR_WRITE = 0xA0;

unsigned char prom_read(unsigned char addr);
void prom_write(unsigned char addr, unsigned char val);
void delay_5ms();
unsigned char num;
unsigned char SEG_CONTENT[] = {0, 0, 0, 0, 0, 0, 0, 0};

void main()
{
	system_init();
	prom_write(0x00, 12);
	prom_write(0x01, 34);
	prom_write(0x02, 56);
	prom_write(0x03, 78);
	num = prom_read(0x00);
	num = prom_read(0x01);
	num = prom_read(0x02);
	num = prom_read(0x03);
	while(1){
		SEG_CONTENT[0] = num / 10;
		SEG_CONTENT[1] = num % 10;
		seg_fresh();
		delay_5ms();
	}
}


//写入一个字节ROM
void prom_write(unsigned char addr, unsigned char val)
{
	iic_init();
	iic_start();
	iic_write_byte(ADDR_WRITE);
	iic_wait_ack();
	iic_write_byte(addr);
	iic_wait_ack();
	iic_write_byte(val);
	iic_wait_ack();
	iic_stop();
	delay_5ms();
}



//读取1个字节ROM
unsigned char prom_read(unsigned char addr)
{
	unsigned char ans;
	iic_init();
	iic_start();
	iic_write_byte(ADDR_WRITE);
	iic_wait_ack();
	iic_write_byte(addr);
	iic_wait_ack();
	iic_start();
	iic_write_byte(ADDR_READ);
	iic_wait_ack();
	ans = iic_read_byte();
	iic_wait_no_ack();
	iic_stop();
	return ans;
}


//等待5ms
void delay_5ms()
{
	unsigned char i, j;

	i = 59;
	j = 90;
	do
	{
		while (--j);
	} while (--i);
}

