#include <reg52.h>
#include "MoveCar.h"
#include "DELAY.h"
#include "DefineVar.h"

void Wireless_433M()
{
	if(D0 == 1)
	{
		Go_Forward();
		Delay100ms();
	}
	else if(D1 == 1)
	{
		Go_Back();
		Delay100ms();
	}
	else if(D2 == 1)
	{
		Go_Left();
		Delay100ms();
	}
	else if(D3 == 1)
	{
		Go_Right();
		Delay100ms();
	}
}


