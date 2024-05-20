#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

#include "oledShow.h"

#define OLED_I2C "/dev/i2c-3"
#define TEXTLEN 20

void oled_demo(struct display_info *disp, unsigned char *buffer) 
{
	char text[TEXTLEN];
	switch(buffer[2])
	{
		case 0x41:
			strcpy(text, "Dry Garbage");
			break;
		case 0x42:
			strcpy(text, "Wet Garbage");
			break;
		case 0x43:
			strcpy(text, "Recycle Garbage");
			break;
		case 0x44:
			strcpy(text, "Hazardous Garbage");
			break;
		default:
			strcpy(text, "Unknown Garbage");
			break;
	}
	disp->font = font1;
	oled_putstrto(disp, 0, 10, "This Trash is:");
	oled_putstrto(disp, 0, 30, text);
	oled_putstrto(disp, 0, 54, "*****************");
	oled_send_buffer(disp);
}

void show_error(int err, int add)
{
	printf("\nERROR: %i, %i\n\n", err, add);
}

void show_usage(char *progname) 
{
	printf("\nUsage:\n%s <I2C bus device node >\n", progname);
}

void OLED_Show_Text(unsigned char *buffer)
{
	int e;
	char filename[32];
	struct display_info disp;

	memset(&disp, 0, sizeof(disp));
	sprintf(filename, "%s", OLED_I2C);
	disp.address = OLED_I2C_ADDR;
	disp.font = font2;

	e = oled_open(&disp, filename);

	if (e < 0) 
		show_error(1, e);
	else 
	{
		e = oled_init(&disp);
		if (e < 0) 
			show_error(2, e);
		else 
		{
			oled_clear(&disp);
			oled_demo(&disp, buffer);
		}
	}
}
