#include <iic.h>

//100us延时
void delay()		//@12.000MHz
{
	unsigned char i, j;

	i = 2;
	j = 39;
	do
	{
		while (--j);
	} while (--i);
}


//IIC初始化
void iic_init()
{
	SCL = 1;
	SDA = 1;
	delay();
}


//IIC启动信号
void iic_start()
{
	SCL = 1;
	SDA = 1;
	delay();
	SDA = 0;
	delay();
}


//IIC应答
void iic_send_ack()
{
	SCL = 0;
	delay();
	SDA = 1;
	delay();
}


//IIC停止
void iic_stop()
{
	SDA = 0;
	SCL = 1;
	delay();
	SDA = 1;
	delay();
}


//写一个字节
void iic_write_byte(unsigned char val)
{
	unsigned char i;
	SCL = 0;
	delay();
	for(i = 0; i < 8; i++){
		SDA = (val & 0x80) ? 1 : 0;
		val = val << 1;
		SCL = 1;
		delay();
		SCL = 0;
		delay();
	}
}


//读一个字节
unsigned char iic_read_byte()
{
	unsigned char i, ans = 0;
	for(i = 0; i < 8; i++){
		SCL = 1;
		delay();
		ans = (ans << 1) | SDA;
		SCL = 0;
		delay();
	}
	return ans;
}


//等待应答
void iic_wait_ack()
{
	SCL = 1;
	delay();
	while(SDA == 1); //等待拉低
	SCL = 0;
	delay();
}

void iic_wait_no_ack()
{
	SCL = 1;
	delay();
	while(SDA == 0); //等待拉高
	SCL = 0;
	delay();
}


