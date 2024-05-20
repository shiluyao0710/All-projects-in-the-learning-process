#ifndef OLEDSHOW_H
#define OLEDSHOW_H

#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

#include "oled.h"
#include "font.h"

void oled_demo(struct display_info *disp, unsigned char *buffer);

void show_error(int err, int add);

void show_usage(char *progname);

void OLED_Show_Text(unsigned char *buffer);

#endif