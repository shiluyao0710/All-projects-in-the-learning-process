#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "command.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <netdb.h>

#define COMMANDSIZE 128
#define CMDSIZE 16
#define FILESIZE 32
#define PATHSIZE 64
#define WCSIZE 96
#define LSASIZE 96

#define DATASIZE 40960

//flag
#define ERRORCODE -1
#define ERROREXIT 1
#define NORMALEXIT 0

#define PERMISSION 0777


struct Message
{
	char command[COMMANDSIZE];
	char cmd[CMDSIZE];
	char filename_one[FILESIZE];
	char filename_two[FILESIZE];
	long unsigned int  filesize;
	char data[DATASIZE];
};

int Cmd_Switcher(struct Message *message)
{
	//server
	if(strlen(message->cmd) == 0)                 return NOTHING;
	else if(strcmp(message->cmd, "ls") == 0       && strcmp(message->filename_one,"-al") ==0) return VIEW_SERVER_ALL_FILE;
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

int Count_File_Dir()
{
    int filecount,dircount;
    FILE *write_popen;
	char command[32];
	char buf[10];
    sprintf(command,"ls -l | grep \"^-\" | wc -l");
    if((write_popen = popen(command, "r")) == NULL)
    {
		perror("popen failed");
        exit(ERROREXIT);
	}
    fread(buf,1,10,write_popen);
    filecount = atoi(buf);
	memset(command, 0, sizeof(command));
	memset(buf, 0, sizeof(buf));
	sprintf(command,"ls -l | grep \"^d\" | wc -l");
    if((write_popen = popen(command, "r")) == NULL)
	{
		perror("popen failed");
        exit(ERROREXIT);
	}
    fread(buf,1,10,write_popen);
    dircount = atoi(buf);
	return filecount + dircount +2;
}

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

void Send_Message_Client(int client_fd, struct Message *message)
{
	//printf("strlen:%ld,filesize:%ld\n",strlen(message->data),message->filesize);
	//printf("before command:%s,cmd:%s,filename_one:%s,filename_two:%s,filesize:%ld,data:%s\n",message->command,message->cmd,message->filename_one,message->filename_two,message->filesize,message->data);
	if((write(client_fd, message, sizeof(struct Message))) == ERRORCODE)
    {
        perror("write server error");
        exit(ERROREXIT);
    }
	//printf("after command:%s,cmd:%s,filename_one:%s,filename_two:%s,filesize:%ld,data:%s\n",message->command,message->cmd,message->filename_one,message->filename_two,message->filesize,message->data);
}

int File_Exit(struct Message *message)
{
	char pathname[PATHSIZE];
	memset(pathname, 0, sizeof(pathname));
	sprintf(pathname, "./%s", message->filename_one);
	//printf("file access command:%s,cmd:%s,filename_one:%s,filename_two:%s,filesize:%d,data:%s\n",message->command,message->cmd,message->filename_one,message->filename_two,message->filesize,message->data);
	if((access(pathname, F_OK)) == ERRORCODE)
		return NO;
	else
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

void Popen_Write(struct Message *message ,int cmd)
{
	int fd;
	FILE *popen_write = NULL;
	char pathname[PATHSIZE];
	char command [COMMANDSIZE];
	memset(pathname, 0, sizeof(pathname));
	memset(command, 0, sizeof(command));
	switch(cmd)
	{
		case VIEW_SERVER_ALL_FILE:
			sprintf(command, "%s %s", message->cmd, message->filename_one);
			if((popen_write = popen(command, "r")) == NULL)
			{
				perror("popen failed");		
				exit(ERROREXIT);
			}
			message->filesize = (Count_File_Dir() * LSASIZE);
			break;
		case VIEW_CURRENT_FILE_PATH:
			if((popen_write = popen(message->cmd, "r")) == NULL)
			{
				perror("popen failed");
				exit(ERROREXIT);
			}
			message->filesize = PATHSIZE;
			break;
		case VIEW_SERVER_FILE:
			if((popen_write = popen(message->cmd, "r")) == NULL)
			{
				perror("popen failed");
				exit(ERROREXIT);
			}
			message->filesize = (Count_File_Dir() * FILESIZE);
			break;
		case STATISTICAL_FILE_CONTENT:
			sprintf(command, "%s %s", message->cmd, message->filename_one);
			if((popen_write = popen(command, "r")) == NULL)
			{
				perror("popen failed");
				exit(ERROREXIT);
			}
			message->filesize = WCSIZE;
			break;
		case DISPLAY_SERVER_CURRENT_FILE_CONTENT:
			sprintf(pathname, "./%s", message->filename_one);
			sprintf(command, "%s %s", message->cmd, message->filename_one);
			if((popen_write = popen(command, "r")) == NULL)
			{
				perror("popen failed");
				exit(ERROREXIT);
			}
			fd = open(pathname, O_RDONLY, PERMISSION);
			message->filesize = Get_File_Size(fd);
			close(fd);
			break;
	}
	fread(message->data, 1, message->filesize, popen_write);
	pclose(popen_write);
}

void Cmd_Handler(struct Message *message, int client_fd)
{
	int fd;
	int n_read;
	char pathname[PATHSIZE];
	struct Message othermessage;
	memset(pathname, 0, sizeof(pathname));
	memset(&othermessage, 0, sizeof(struct Message));
	printf(">>>%s\n", message->cmd);
	switch (Cmd_Switcher(message))
	{
	// server command
	case VIEW_SERVER_ALL_FILE:
		Popen_Write(message, VIEW_SERVER_ALL_FILE);
		Send_Message_Client(client_fd, message);
		break;
	case VIEW_CURRENT_FILE_PATH:
		Popen_Write(message, VIEW_CURRENT_FILE_PATH);
		Send_Message_Client(client_fd, message);
		break;
	case VIEW_SERVER_FILE:
		Popen_Write(message, VIEW_SERVER_FILE);
		Send_Message_Client(client_fd, message);
		break;
	case STATISTICAL_FILE_CONTENT:
		if((File_Exit(message)) == NO)
		{
			strcpy(othermessage.data, "file does not exit!");
			othermessage.filesize= strlen(othermessage.data);
			Send_Message_Client(client_fd, &othermessage);
			break;
		}
		else
		{
			Popen_Write(message, STATISTICAL_FILE_CONTENT);
			Send_Message_Client(client_fd, message);
			break;
		}
	case DISPLAY_SERVER_CURRENT_FILE_CONTENT:
		if((File_Exit(message)) == NO)
		{
			strcpy(othermessage.data, "file does not exit!");
			othermessage.filesize= strlen(othermessage.data);
			Send_Message_Client(client_fd, &othermessage);
			break;
		}
		else
		{
			Popen_Write(message, DISPLAY_SERVER_CURRENT_FILE_CONTENT);
			Send_Message_Client(client_fd, message);
			break;
		}
	case SWITCH_SERVER_FILE:
		if((File_Exit(message)) == NO)
		{
			strcpy(othermessage.data, "file does not exit!");
			othermessage.filesize= strlen(othermessage.data);
		}
		else
		{
			chdir(message->filename_one);
			strcpy(othermessage.data, "Succeeded in switching directory!");
			othermessage.filesize= strlen(othermessage.data);
		}
		Send_Message_Client(client_fd, &othermessage);
		break;
	case RENAME_SERVER_FILE_DIR:
		if((File_Exit(message)) == NO)
		{
			strcpy(othermessage.data, "file does not exit!");
			othermessage.filesize= strlen(othermessage.data);
		}
		else
		{
			sprintf(message->command, "mv %s %s", message->filename_one, message->filename_two);
			system(message->command);
			strcpy(othermessage.data, "Rename successfully!");
			othermessage.filesize= strlen(othermessage.data);
		}
		Send_Message_Client(client_fd, &othermessage);
		break;
	case CREATE_SERVER_DIR:
	case CREATE_SERVER_FILE:
		sprintf(message->command, "%s %s", message->cmd, message->filename_one);
		system(message->command);
		break;
	case DELETE_SERVER_FILE:
		if((File_Exit(message)) == NO)
		{
			strcpy(othermessage.data, "file does not exit!");
			othermessage.filesize= strlen(othermessage.data);
		}
		else
		{
			sprintf(message->command, "rm -rf %s", message->filename_one);
			system(message->command);
			strcpy(othermessage.data, "Successfully deleted!");
			othermessage.filesize= strlen(othermessage.data);
		}
		Send_Message_Client(client_fd, &othermessage);
		break;
	case UPLOAD_FILE:
		sprintf(pathname, "./%s", message->filename_one);
		if((fd = open(pathname, O_CREAT|O_RDWR, PERMISSION)) ==ERRORCODE)
		{
			perror("open upload file failed");
			exit(ERROREXIT);
		}
		if((write(fd, message->data, message->filesize)) == ERRORCODE)
		{
			perror("write file failed");
			exit(ERROREXIT);
		}
		close(fd);
		break;
	case DOWNLOAD_FILE:
		sprintf(pathname, "./%s", message->filename_one);
		//printf("download command:%s,cmd:%s,filename_one:%s,filename_two:%s,filesize:%d,data:%s\n",message->command,message->cmd,message->filename_one,message->filename_two,message->filesize,message->data);
		if((File_Exit(message)) == NO)
		{
			strcpy(othermessage.data, "file does not exit!");
			othermessage.filesize= strlen(othermessage.data);
			Send_Message_Client(client_fd, &othermessage);
			break;
		}
		//printf("file_exit command:%s,cmd:%s,filename_one:%s,filename_two:%s,filesize:%d,data:%s\n",message->command,message->cmd,message->filename_one,message->filename_two,message->filesize,message->data);
		if((fd = open(pathname, O_RDWR, PERMISSION)) == ERRORCODE)
		{
			perror("open download file failed");
			exit(ERROREXIT);
		}
		message->filesize = Get_File_Size(fd);
		if((n_read = read(fd, message->data, message->filesize)) < 0)
		{
			perror("read download file failed");
			exit(ERROREXIT);
		}
		Send_Message_Client(client_fd, message);
		close(fd);
		break;
	case QUIT:
		exit(NORMALEXIT);
		break;
	case FAULT:
		strcpy(othermessage.data,"command input error");
		othermessage.filesize= strlen(othermessage.data);
		Send_Message_Client(client_fd, &othermessage);
		break;
	default:
		break;
	}

}

int Socket_Build(char *param)
{
	int server_fd;
	struct sockaddr_in server_addr;
	// socket
	if((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == ERRORCODE)
	{
		perror("socket");
		exit(ERROREXIT);
	}
	// connect
	memset(&server_addr, 0, sizeof(struct sockaddr_in));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(atoi(param));
	inet_aton("192.168.1.112", &server_addr.sin_addr);
	if((bind(server_fd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr_in))) == ERRORCODE)
	{
		perror("bind");
		exit(ERRORCODE);
	}
	if((listen(server_fd, 5)) == ERRORCODE)
	{
		perror("listen");
		exit(ERRORCODE);
	}
	printf("Listening all client ......\n");
	return server_fd;
}

//Entry Function
int main(int argc, char*argv[])
{
	int i;
	int flag;
	ssize_t n_read;
	unsigned long int size;
	pid_t pid;
	int ret_value;
	int client_len;
	int server_fd, client_fd;
	struct sockaddr_in client_addr;
	struct Message message;
	memset(&client_addr, 0, sizeof(struct sockaddr_in));
	// param
	if (argc != 2)
	{
	 	printf("argv %s <missing params port>\n", argv[0]);
	 	exit(ERROREXIT);
	}
	server_fd = Socket_Build(argv[1]);
	client_len = sizeof(struct sockaddr_in);
	// send message
	while(1)
	{
		if((client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_len)) == ERRORCODE)
		{
			perror("accept");
			exit(ERRORCODE);
		}
		//client handler
		pid = fork();
		if (pid == 0)
		{
			printf("one client is connected!\n");
			while (1)
			{
				read(client_fd, &message, sizeof(struct Message));
				if (strlen(message.cmd) > 0)
				{
					//printf("server divide before command:%s,cmd:%s,filename_one:%s,filename_two:%s,filesize:%ld,data:%s\n",message.command,message.cmd,message.filename_one,message.filename_two,message.filesize,message.data);
					Message_Divide(&message);
					//printf("server divide after command:%s,cmd:%s,filename_one:%s,filename_two:%s,filesize:%ld,data:%s\n",message.command,message.cmd,message.filename_one,message.filename_two,message.filesize,message.data);
					Cmd_Handler(&message, client_fd);
				}
			}
			close(client_fd);
		}
	}
	close(server_fd);
	return 0;
}
