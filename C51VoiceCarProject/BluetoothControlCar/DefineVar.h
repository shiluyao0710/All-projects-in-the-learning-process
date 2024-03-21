#ifndef _DEFINEVAR_H
#define _DEFINEVAR_H

#define GOFORWARD '0'
#define GOBACK '1'
#define GOLEFT '2'
#define GORIGHT '3'

#define HIGH 1
#define LOW 0

typedef unsigned char u8;

sbit  D5 = P3^7;
sbit  D6 = P3^6;

sbit A1_Right = P0^0;
sbit A2_Right = P0^1;
sbit B1_Left = P0^3;
sbit B2_Left = P0^2;

sbit D0 = P0^4;
sbit D1 = P0^5;
sbit D2 = P0^6;
sbit D3 = P0^7;


#endif
