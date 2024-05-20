#ifndef GARBAGECLASS_H
#define GARBAGECLASS_H

#include <stdio.h>
#include <stdlib.h>
#include "garbage.h"

#define DRY_GARBAGE 1
#define WET_GARBAGE 2
#define RECYCLE_GARBAGE 3
#define HAZARDOUS_GARBAGE 4
#define OTHER_GARBAGE 5

int garbage_classify();

#endif // GARBAGECLASS_H