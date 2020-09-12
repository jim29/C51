#ifndef	_IIC_H
#define	_IIC_H
#include <system.h>
#define SCL	P20
#define SDA	P21

void iic_init();
void iic_start();
void iic_send_ack();
void iic_stop();
void iic_write_byte(unsigned char val);
unsigned char iic_read_byte();
void iic_wait_ack();
void iic_wait_no_ack();
#endif