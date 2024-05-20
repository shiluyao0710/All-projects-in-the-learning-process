#ifndef _UARTTOOL_H
#define _UARTTOOL_H

int Serial_Open(const char *device, const int baud);

//串口关闭
void Serial_Close(const int fd);

//发送字符
void Serial_Putchar(const int fd, const unsigned char c);

//发送字符串
void Serial_Puts(const int fd, const char *str, int len);

//接收字符
int Serial_Getchar(const int fd);

//接收字符串
int Serial_Gets(const int fd, unsigned char *str);

//数据有效性
int Serial_DataAvail(const int fd);

#endif
