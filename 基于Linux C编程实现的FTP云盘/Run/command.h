#ifndef _COMMAND_H
#define _COMMAND_H

/*********************HEAD FILE****************************/




/*********************LOCAL MACRO DEFINITION********************/
#define SWITCH_LOCAL_DIR 1
#define VIEW_LOCAL_FILE 2
#define RENAME_LOCAL_FILE_DIR 3
#define CREAT_LOCAL_DIR 4
#define CREAT_LOCAL_FILE 5
#define VIEW_CURRENT_LOCAL_PATH 6
#define DISPLAY_CURRENT_FILE_CONTENT 7
#define DELETE_LOCAL_FILE 8
#define STATISTICAL_LOCAL_FILE 9
#define VIEW_LOCAL_ALL_FILE 10

/*********************SERVER MACRO DEFINITION********************/
#define DOWNLOAD_FILE 11
#define UPLOAD_FILE 12
#define VIEW_SERVER_FILE 13
#define SWITCH_SERVER_FILE 14
#define RENAME_SERVER_FILE_DIR 15
#define CREATE_SERVER_DIR 16
#define CREATE_SERVER_FILE 17
#define VIEW_FILE_PERMISSION 18
#define VIEW_CURRENT_FILE_PATH 19
#define DISPLAY_SERVER_CURRENT_FILE_CONTENT 20
#define DELETE_SERVER_FILE 21
#define STATISTICAL_FILE_CONTENT 22
#define VIEW_SERVER_ALL_FILE 23

#define QUIT 31
#define DISPLAY 32 
#define FAULT 33
#define NOTHING 34

/*********************Return Value Handler********************/
#define RW 41
#define ORNW 42
#define UPLOAD 43
#define DOWNLOAD 44
#define UNTREATED 45
#define ACCESS 46
#define FILEIFEXIT 47

#define YES 1
#define NO 0

#define DOWNLOAD_FILE_RELY 24
#define CREATE_TYPE 25


#endif

