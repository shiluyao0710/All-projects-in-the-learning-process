#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "HelpDisplay.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "command.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <netdb.h>
#include <sys/time.h>

//buffer size
#define COMMANDSIZE 128
#define CMDSIZE 16
#define FILESIZE 32
#define PATHSIZE 64
#define DATASIZE 40960

//flag
#define ERRORCODE -1
#define ERROREXIT 1
#define NORMALEXIT 0

#define PERMISSION 0777

//socket message struct
struct Message
{
	char command[COMMANDSIZE];
	char cmd[CMDSIZE];
	char filename_one[FILESIZE];
	char filename_two[FILESIZE];
	unsigned long int  filesize;
	char data[DATASIZE];
};

//Command Switcher Function
int Cmd_Switcher(struct Message *message)
{
	//client
	if(strcmp(message->cmd, "display") == 0)      return DISPLAY;	
	else if(strcmp(message->cmd, "lls") == 0 && strcmp(message->filename_one, "-al") == 0) return VIEW_LOCAL_ALL_FILE;
	else if(strcmp(message->cmd, "lls") == 0)     return VIEW_LOCAL_FILE;
	else if(strcmp(message->cmd, "lcat") == 0)    return DISPLAY_CURRENT_FILE_CONTENT;
	else if(strcmp(message->cmd, "lwc") == 0)     return STATISTICAL_LOCAL_FILE;
	else if(strcmp(message->cmd, "lpwd") == 0)    return VIEW_CURRENT_LOCAL_PATH;
	else if(strcmp(message->cmd, "lrm") == 0)     return DELETE_LOCAL_FILE;
	else if(strcmp(message->cmd, "lmkdir") == 0)  return CREAT_LOCAL_DIR;
	else if(strcmp(message->cmd, "ltouch") == 0)  return CREAT_LOCAL_FILE;
	else if(strcmp(message->cmd, "lcd") == 0)     return SWITCH_LOCAL_DIR;
	else if(strcmp(message->cmd, "lmv") == 0)     return RENAME_LOCAL_FILE_DIR;
	
	//server
	else if(strcmp(message->cmd, "ls") == 0 && strcmp(message->filename_one, "-al") == 0) return VIEW_SERVER_ALL_FILE;
	else if(strcmp(message->cmd, "get") == 0)     return DOWNLOAD_FILE;
	else if(strcmp(message->cmd, "put") == 0)     return UPLOAD_FILE;
	else if(strcmp(message->cmd, "ls") == 0)      return VIEW_SERVER_FILE;
	else if(strcmp(message->cmd, "cd") == 0)      return SWITCH_SERVER_FILE;
	else if(strcmp(message->cmd, "mv") == 0)      return RENAME_SERVER_FILE_DIR;
	else if(strcmp(message->cmd, "mkdir") == 0)   return CREATE_SERVER_DIR;
	else if(strcmp(message->cmd, "touch") == 0)   return CREATE_SERVER_FILE;
	else if(strcmp(message->cmd, "pwd") == 0)     return VIEW_CURRENT_FILE_PATH;
	else if(strcmp(message->cmd, "cat") == 0)     return DISPLAY_SERVER_CURRENT_FILE_CONTENT;
	else if(strcmp(message->cmd, "rm") == 0)      return DELETE_SERVER_FILE;
	else if(strcmp(message->cmd, "wc") == 0)      return STATISTICAL_FILE_CONTENT;
	
	//other
	else if(strcmp(message->cmd, "quit") == 0)    return QUIT;
	else                                    return FAULT;
}

//String Cutting Function
void Message_Divide(struct Message *message)
{
	char *token;
	char command[COMMANDSIZE];
	message->command[strcspn(message->command, "\n")] = '\0';
	strcpy(command, message->command);
	token = strtok(message->command, " ");
	if (token != NULL) 
	{
		strcpy(message->cmd, token);
		token = strtok(NULL, " ");
		if (token != NULL) 
		{
			strcpy(message->filename_one, token);
			token = strtok(NULL, " ");
			if (token != NULL) 
			{
				strcpy(message->filename_two, token);
			}
		}
	}
	strcpy(message->command, command);
}

void Send_Message_Server(int server_fd, struct Message *message)
{
	//printf("len:%ld,filesize:%ld\n",strlen(message->data), message->filesize);
	if((write(server_fd, message, sizeof(struct Message))) == ERRORCODE)
    {
        perror("write server error");
        exit(ERROREXIT);
    }
}

void Recv_Message_Server(struct Message *message, int server_fd, int cmd)
{
	int i = 0;
	int flag = 0;
	ssize_t n_read;
	unsigned long int size = 1;
	if(cmd == RW)
	{
		while(strlen(message->data) == 0)
		{
			if((read(server_fd, message, sizeof(struct Message))) == ERRORCODE)
			{
				perror("read file failed");
				exit(ERROREXIT);
			} 
		}
	}
	if(cmd == DOWNLOAD)
	{
		while(1)
		{
			//i++;
			if((n_read = read(server_fd, message, sizeof(struct Message))) == ERRORCODE)
			{
				perror("read file failed");
				exit(ERROREXIT);
			} 
			//printf("now %d :data:%ld,filesize:%ld\n",i, strlen(message->data),message->filesize);
			 if(strlen(message->data) > 0 && flag == 0)
			{
				size = message->filesize;
			 	flag = 1;
			}
			//printf("size:%ld\n",size);
			if(strlen(message->data) == size)
				break;
		}
	}
	
}

int File_Exit(struct Message *message)
{
	char pathname[PATHSIZE];
	memset(pathname, 0, sizeof(pathname));
	sprintf(pathname, "./%s", message->filename_one);
	if((access(pathname, F_OK)) == ERRORCODE)
		return NO;
	return YES;
}

int Get_File_Size(int fd)
{
	struct stat fileStat;
	if (fstat(fd, &fileStat) == -1)
	 {
		perror("fstat");
		exit(ERROREXIT);
	}
	return fileStat.st_size;
}


//Command Handler Function
int Cmd_Handler(struct Message *message, int server_fd)
{
	int fd;
	int n_read;
	char pathname[PATHSIZE];
	memset(pathname, 0, sizeof(pathname));
	//command action
	switch(Cmd_Switcher(message))
	{
		//client command
		case VIEW_LOCAL_FILE:
		case CREAT_LOCAL_DIR:
		case CREAT_LOCAL_FILE:
		case VIEW_LOCAL_ALL_FILE:
		case VIEW_CURRENT_LOCAL_PATH:
			system(message->command + 1);
			break;
		case SWITCH_LOCAL_DIR:
			chdir(message->filename_one);
			break;
		case DELETE_LOCAL_FILE:
			if((File_Exit(message)) == NO)
			{
				printf("file does not exit!\n");
				break;
			}
			sprintf(message->command, "rm -rf %s",message->filename_one);
			system(message->command);
			break;
		case RENAME_LOCAL_FILE_DIR:
		case STATISTICAL_LOCAL_FILE:
		case DISPLAY_CURRENT_FILE_CONTENT:
			if((File_Exit(message)) == NO)
			{
				printf("file does not exit!\n");
				break;
			}
			system(message->command + 1);
			break;
		//help
		case DISPLAY:
			Display();
			break;
		//server command
		case CREATE_SERVER_DIR:
		case CREATE_SERVER_FILE:
			Send_Message_Server(server_fd, message);
			break;
		case VIEW_SERVER_ALL_FILE:
		case VIEW_SERVER_FILE:
		case VIEW_CURRENT_FILE_PATH:
		case DISPLAY_SERVER_CURRENT_FILE_CONTENT:
		case STATISTICAL_FILE_CONTENT:
		case SWITCH_SERVER_FILE:
		case RENAME_SERVER_FILE_DIR:
		case DELETE_SERVER_FILE:
			Send_Message_Server(server_fd, message);
			return RW;
		//upload file
		case UPLOAD_FILE:
			sprintf(pathname, "./%s", message->filename_one);
			if((File_Exit(message)) == NO)
			{
				printf("file does not exit!\n");
				break;
			}
			if((fd = open(pathname, O_RDWR, PERMISSION)) == ERRORCODE)
			{
				perror("open file error");
				exit(ERROREXIT);
			}
			message->filesize = Get_File_Size(fd);
			if((n_read = read(fd, message->data, message->filesize)) < 0)
			{
				perror("read file error");
				exit(ERROREXIT);
			}
			Send_Message_Server(server_fd, message);
			close(fd);
			break;
		//download file
		case DOWNLOAD_FILE:
			Send_Message_Server(server_fd, message);
			return DOWNLOAD;
		//other command
		case QUIT:
			exit(NORMALEXIT);
			break;
		case FAULT:
			printf("command input error\n");
			break;
		default :
			break;
	}
	return UNTREATED;
}

void Return_Value_Handler(int ret, int server_fd)
{
	int fd;
	char pathname[PATHSIZE];
	struct Message message;
	memset(pathname, 0, sizeof(pathname));
	memset(&message, 0, sizeof(struct Message));
	switch(ret)
	{
		case RW:
			Recv_Message_Server(&message, server_fd, RW);
			printf("%s\n",message.data);
			fflush(stdout);
			break;
		case DOWNLOAD:
			Recv_Message_Server(&message, server_fd, DOWNLOAD);
			sprintf(pathname, "./%s", message.filename_one);
			if (strlen(message.filename_one) == 0) 
			{
				printf("file name empty\n");
				exit(ERROREXIT);
			} 
			if((fd = open(pathname, O_CREAT|O_RDWR, PERMISSION)) == ERRORCODE)
			{
				perror("open file failed");
				exit(ERROREXIT);
			}
			if((write(fd, message.data, message.filesize)) == ERRORCODE)
			{
				perror("write file error");
				exit(ERROREXIT);
			}
			close(fd);
			break;
		default :
			break;
	}	
}

int Socket_Build(char *param1, char *param2)
{
	int server_fd;
	struct sockaddr_in server_addr;
	//socket
	if((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == ERRORCODE)
	{
		perror("socket");
		exit(ERROREXIT);
	}
	//connect
	memset(&server_addr, 0, sizeof(struct sockaddr_in));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(atoi(param2));
	inet_aton(param1, &server_addr.sin_addr);
	if((connect(server_fd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr))) == ERRORCODE)
	{
		perror("connect");
		exit(ERROREXIT);
	}
	return server_fd;
}

//Entry Function
int main(int argc, char *argv[]) 
{
	int ret_value;
	int server_fd;
	struct Message message;
	//param
	if(argc != 3)
	{
		printf("argv %s <missing param ip port>\n",argv[0]);
		exit(ERROREXIT);
	}
	server_fd = Socket_Build(argv[1],argv[2]);
	printf("successfully connected...\n");
	//receive user message
	while(1)
	{
		memset(&message, 0, sizeof(struct Message));		
		printf(">>>");
		fgets(message.command, sizeof(message.command), stdin);
		if(message.command[0] != '\n')
		{
			//printf("divide before command:%s,cmd:%s,filename_one:%s,filename_two:%s,filesize:%ld,data:%s\n",message.command,message.cmd,message.filename_one,message.filename_two,message.filesize,message.data);
			Message_Divide(&message);
			//printf("divide after command:%s,cmd:%s,filename_one:%s,filename_two:%s,filesize:%ld,data:%s\n",message.command,message.cmd,message.filename_one,message.filename_two,message.filesize,message.data);
			ret_value = Cmd_Handler(&message, server_fd);
			Return_Value_Handler(ret_value, server_fd);
		}
	}
	close(server_fd);
	return 0;
}

