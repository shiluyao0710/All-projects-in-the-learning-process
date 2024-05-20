#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "garbage.h"
#include "garbageClass.h"


int garbage_classify()
{
    int ret = OTHER_GARBAGE;
	char *category = NULL;
	
	category = garbage_category(category);
	//printf("category=%s\n",category);
    if(strcmp(category,"干垃圾") == 0)
        ret = DRY_GARBAGE;
    else if(strcmp(category,"湿垃圾") == 0)
        ret = WET_GARBAGE;
    else if(strcmp(category,"可回收垃圾") == 0) 
        ret = RECYCLE_GARBAGE;
    else if(strcmp(category,"有害垃圾") == 0)
        ret = HAZARDOUS_GARBAGE;
    else
        ret = OTHER_GARBAGE;
	free(category);
	return ret;
}
