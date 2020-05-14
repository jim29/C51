#include <reg51.h>
#include <intrins.h>
#include <uart.h>
#include <math.h>


extern bit uart_busy;
unsigned char buffer;


void main()
{
	UartInit();
	SendString("Please enter the number:\r\n");
	while(1){
		SendString("Please enter the number:\r\n");
	}
}


/*----------------------------
UART 中断服务程序
-----------------------------*/
void Uart() interrupt 4
{
    if (RI)
    {
        RI = 0;                 //清除RI位
		buffer = SBUF;
    }
    if (TI)
    {
        TI = 0;                 //清除TI位
        uart_busy = 0;               //清忙标志
    }
}

