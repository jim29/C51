#ifndef _IIC_H
#define _IIC_H

#define FAIL 0
#define SUCS 1

bit AT24C02_Write(unsigned char addrn, unsigned char* datan, unsigned char n);
bit AT24C02_Read(unsigned char addrn, unsigned char* datan, unsigned char n);
#endif