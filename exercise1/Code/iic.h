#ifndef _IIC_H
#define	_IIC_H

void WriteAddr(unsigned char addr, unsigned char val1, unsigned char val2);
void ReadAddr(unsigned char addr, unsigned char * val1, unsigned char * val2);
#endif
