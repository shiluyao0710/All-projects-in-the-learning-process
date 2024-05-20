#ifndef MJPGSERVICECHECK_H
#define MJPGSERVICECHECK_H

#define MJPG_SERVICE_CHECK_SUCCESS 0
#define MJPG_SERVICE_CHECK_FAILURE 1

#define CMD "ps -ax|grep mjpg_streamer|grep -v grep"

int mjpgServiceCheck();

#endif // MJPGSERVICECHECK_H