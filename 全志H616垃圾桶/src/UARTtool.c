#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "UARTtool.h"

//串口打开和初始化
int Serial_Open(const char *device, const int baud)
{
	struct termios options;
	int myBaud;
	int status,fd;

	switch(baud)
	{
	case 9600:   myBaud = B9600;   break;
	case 115200: myBaud = B115200; break;
	default:
		return -2;
	}
	if((fd = open(device, O_RDWR | O_NOCTTY | O_NDELAY | O_NONBLOCK)) == -1)
		return -1;
	fcntl(fd, F_SETFL, O_RDWR);

	tcgetattr(fd, &options);
	cfmakeraw(&options);
	cfsetispeed(&options, myBaud);
	cfsetospeed(&options, myBaud);

	options.c_cflag |= (CLOCAL | CREAD);
	options.c_cflag &= ~PARENB;
	options.c_cflag &= ~CSTOPB;
	options.c_cflag &= ~CSIZE;
	options.c_cflag |= CS8;
	options.c_lflag &= ~(ICANON |ECHO | ECHOE | ISIG);
	options.c_oflag &= ~OPOST;
	options.c_cc[VMIN] = 0;
	options.c_cc[VTIME] = 100;

	tcsetattr(fd, TCSANOW, &options);
	ioctl(fd, TIOCMGET, &status);

	status |= TIOCM_DTR;
	status |= TIOCM_RTS;

	ioctl(fd, TIOCMSET, &status);
	usleep(10000);
	return fd;
}

//串口关闭
void Serial_Close(const int fd)
{
	close(fd);
}

//发送字符
void Serial_Putchar(const int fd, const unsigned char c)
{
	int ret;
	ret = write(fd, &c, 1);
	if(ret < 0)
		printf("Serial putchar error\n");
}

//发送字符串
void Serial_Puts(const int fd, const char *str, int len)
{
	int ret;
	ret = write(fd, str, len);
	if(ret < 0)
		printf("Serial puts error\n");
	
}


//接收字符
int Serial_Getchar(const int fd)
{
	unsigned char c;
	if((read(fd, &c, 1)) == -1)
		return -1;

	return ((int)c) & 0xFF;
}

//接收字符串
int Serial_Gets(const int fd, unsigned char *buffer)
{
	int n_read;
	n_read = read(fd, buffer, 32);
	return n_read;
}

//数据有效性
int Serial_DataAvail(const int fd)
{
	int result;
	if(ioctl(fd, FIONREAD, &result) == -1)
		return -1;
	return result;
}


