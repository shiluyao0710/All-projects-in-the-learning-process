#include <reg52.h>
#include "DELAY.h"
#include "MoveCar.h"
#include "SpeedDisplay.h"
#include "DefineVar.h"
#include "UART.h"
#include "Wireless433M.h"

void Indicator_Light()
{
	unsigned char i;
	for(i=0;i<3;i++)
	{
		D5 = LOW;
		D6 = LOW;
		Delay1000ms();
		D5 = HIGH;
		D6 = HIGH;
		Delay1000ms();
	}
}

void main()
{
	Indicator_Light();
	UART_Init();
	Time0_Init();
	Wireless_433M();
	while(1)
	{
		Wireless_433M();
		Stop();
	}
}
