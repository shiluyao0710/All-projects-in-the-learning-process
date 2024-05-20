#include <stdio.h>
#include <string.h>
#include "mjpgServiceCheck.h"

int mjpgServiceCheck()
{
   char buffer[128];
   FILE *fp;
   fp = popen(CMD, "r");
   if (fp == NULL) {
      printf("Failed to run command\n");
      return MJPG_SERVICE_CHECK_FAILURE;
   }
   fgets(buffer, sizeof(buffer), fp);
   if (strstr(buffer, "mjpg_streamer") == NULL) {
      return MJPG_SERVICE_CHECK_FAILURE;
   }
   pclose(fp);
   return  MJPG_SERVICE_CHECK_SUCCESS;
}