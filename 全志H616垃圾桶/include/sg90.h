#ifndef __SG90_H__
#define __SG90_H__

#include <wiringPi.h>
#include <softPwm.h>

#define PIN 7

void sg90_run(int pwm_pin);

void sg90_stop(int pwm_pin);

#endif