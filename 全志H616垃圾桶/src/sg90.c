#include "sg90.h"

 //根据公式：PWMfreq = 1 x 10^6 / (100 x range) ，要得到PWM频率为50Hz，则range为200，即周期分为200步，控制精度相比硬件PWM较低。

void sg90_run(int pwm_pin)
{
	pinMode(pwm_pin, OUTPUT);
	softPwmCreate(pwm_pin, 0, 200);		
	softPwmWrite(pwm_pin, 10);
	delay(1000);
	softPwmStop(pwm_pin);
}

void sg90_stop(int pwm_pin)
{
	pinMode(pwm_pin, OUTPUT);
	softPwmCreate(pwm_pin, 0, 200);
	softPwmWrite(pwm_pin, 15);
	delay(1000);
	softPwmStop(pwm_pin);
}

