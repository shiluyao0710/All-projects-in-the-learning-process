#include <reg52.h>
#include "DELAY.h"
#include "DefineVar.h"

void Go_Forward()
{
	A1_Right = LOW;
	A2_Right = HIGH;
	B1_Left = LOW;
	B2_Left = HIGH;
}

void Go_Back()
{
	A1_Right = HIGH;
	A2_Right = LOW;
	B1_Left = HIGH;
	B2_Left = LOW;
}

void Go_Left()
{
	A1_Right = LOW;
	A2_Right = LOW;
	B1_Left = LOW;
	B2_Left = HIGH;
}

void Go_Right()
{
	A1_Right = LOW;
	A2_Right = HIGH;
	B1_Left = LOW;
	B2_Left = LOW;
}

void Stop()
{
	A1_Right = LOW;
	A2_Right = LOW;
	B1_Left = LOW;
	B2_Left = LOW;
}
