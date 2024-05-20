#include "UARTtool.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <netinet/tcp.h>
#include "garbageClass.h"
#include "oledShow.h"
#include "mjpgServiceCheck.h"
#include "sg90.h"
#include "socket.h"

#define UART_PORT "/dev/ttyS5"
#define BAUDRATE 115200
#define LNE 6

#define WGET_CMD "wget http://127.0.0.1:8080/?action=snapshot -O /home/orangepi/codes/smart_garbage_recognize/tempjpg/test.jpg "
#define PICTURE_PATH "/home/orangepi/codes/smart_garbage_recognize/tempjpg/test.jpg"

int fd;
pthread_mutex_t lock;
pthread_cond_t cond;

void *thread_sg90(void *arg)
{
    unsigned char *buffer = (unsigned char *)arg;
    pthread_detach(pthread_self());
    if(buffer[2] == 0x41 || buffer[2] == 0x42 || buffer[2] == 0x43 || buffer[2] == 0x44)
    {
        sg90_run(PIN);
        delay(2000);
        sg90_stop(PIN);
    }
    pthread_exit(NULL);
}

void *thread_oled_show(void *arg)
{
    unsigned char *buffer = (unsigned char *)arg;
    pthread_detach(pthread_self());
    OLED_Show_Text(buffer);
    pthread_exit(NULL);
}

void *thread_voice_send(void *arg)
{
    unsigned char *buffer = (unsigned char *)arg;
    pthread_detach(pthread_self());
    if(buffer != NULL)
        Serial_Puts(fd, buffer, LNE);
    pthread_exit(NULL);
}

void *thread_voice_get()
{
    unsigned char buffer[LNE] = {0xAA, 0x55, 0x46, 0x00, 0x55, 0xAA};
    if((fd = Serial_Open(UART_PORT, BAUDRATE)) == -1)
    {
        printf("open %s error", UART_PORT);
        Serial_Close(fd);
        pthread_exit(NULL);
    }
    while(1)
    {
        memset(buffer, 0, LNE);
        Serial_Gets(fd, buffer);
        if(buffer[2] == 0x46)
        {  
            pthread_mutex_lock(&lock);
            pthread_cond_signal(&cond);
            pthread_mutex_unlock(&lock);
        }
    }
    Serial_Close(fd);
    pthread_exit(NULL);
}

void *thread_aliyun_garbage_classify()
{
    int i;
    int ret;
    int del;
    pthread_t oled_show_thread;
    pthread_t sg90_thread;
    pthread_t voice_send_thread;
    unsigned char buffer[LNE] = {0xAA, 0x55, 0x46, 0x00, 0x55, 0xAA};
    while(1)
    {
        pthread_mutex_lock(&lock);
        pthread_cond_wait(&cond, &lock);
        pthread_mutex_unlock(&lock);
        if((del = remove(PICTURE_PATH)) == -1)
        {
            perror("remove failed");
        }
        system(WGET_CMD);
        ret = garbage_classify();
        switch(ret)
        {
            case DRY_GARBAGE:
                buffer[2] = 0x41;
                break;
            case WET_GARBAGE:
                buffer[2] = 0x42;
                break;
            case RECYCLE_GARBAGE:   
                buffer[2] = 0x43;
                break;
            case HAZARDOUS_GARBAGE:
                buffer[2] = 0x44;
                break;
            default:
                buffer[2] = 0x45;
                break;
        }
        pthread_create(&oled_show_thread, NULL, thread_oled_show, (void *)buffer);
        pthread_create(&sg90_thread, NULL, thread_sg90, (void *)buffer);
        pthread_create(&voice_send_thread, NULL, thread_voice_send, (void *)buffer);
    }
    pthread_exit(NULL);
}

void *thread_socket_server()
{
    int serverfd;
    int clientfd;
    int client_len;
    int n_read;
    char recv_buf[8];
    struct sockaddr_in clientaddr;
    int keepalive = 1;          // 开启TCP KeepAlive功能
    int keepidle = 5;        // tcp_keepalive_time
    int keepcnt = 3;            // tcp_keepalive_probes
    int keepintvl = 3;         // tcp_keepalive_intvl
    serverfd = socket_init(IP, PORT);
    if(serverfd == -1)
    {
        perror("socket init failed");
        close(serverfd);
        pthread_exit(NULL);
    }
    client_len = sizeof(clientaddr);
    while(1)
    {
        if((clientfd = accept(serverfd, (struct sockaddr *)&clientaddr, &client_len)) == -1)
        {
            perror("accept failed");
            continue;
        }
        printf("client connected\n");
        setsockopt(clientfd, SOL_SOCKET, SO_KEEPALIVE, (void *)&keepalive, sizeof(keepalive));
        setsockopt(clientfd, SOL_TCP, TCP_KEEPIDLE, (void *) &keepidle, sizeof (keepidle));
        setsockopt(clientfd, SOL_TCP, TCP_KEEPCNT, (void *)&keepcnt, sizeof (keepcnt));
        setsockopt(clientfd, SOL_TCP, TCP_KEEPINTVL, (void *)&keepintvl, sizeof (keepintvl));
        while(1)
        {
            memset(recv_buf, 0, sizeof(recv_buf));
            n_read = recv(clientfd, recv_buf, 8, 0);
            if(n_read == -1)
            {
                perror("recv failed");
                break;
            }
            if(n_read == 0)
            {
                printf("client disconnected\n");
                break;
            }
            printf("recv: %s\n", recv_buf);
            if(strcmp(recv_buf, "start") == 0)
            {
                pthread_mutex_lock(&lock);
                pthread_cond_signal(&cond);
                pthread_mutex_unlock(&lock);
            }
        }
    }
    close(clientfd);
    close(serverfd);
    pthread_exit(NULL);
}

int main(void)
{
    pthread_t voice_get_thread;
    pthread_t aliyun_garbage_classify_thread;
    pthread_t socket_server_thread;
    garbage_init();
    wiringPiSetup();
    if(mjpgServiceCheck() == MJPG_SERVICE_CHECK_FAILURE)
    {
        printf("mjpg service not running\n");
        return -1;
    }
    pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&cond, NULL);
    
    pthread_create(&voice_get_thread, NULL, thread_voice_get, NULL);
    pthread_create(&aliyun_garbage_classify_thread, NULL, thread_aliyun_garbage_classify, NULL);
    pthread_create(&socket_server_thread, NULL, thread_socket_server, NULL);

    pthread_join(voice_get_thread, NULL);
    pthread_join(aliyun_garbage_classify_thread, NULL);
    pthread_join(socket_server_thread, NULL);

    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&cond);

    garbage_final();
    return 0;
}


//普通版本
// 找错方案：    printf("%s|%s|%d: buffer[2]=0x%x\n", __FILE__, __func__, __LINE__,buffer[2]);
#if 0
int main(void)
{
    int i;
    int fd;
    int ret;
    int del;
    unsigned char buffer[LNE] = {0xAA, 0x55, 0x46, 0x00, 0x55, 0xAA};
    garbage_init();
    wiringPiSetup();
    if((fd = Serial_Open(UART_PORT, BAUDRATE)) == -1)
    {
        printf("open %s error", UART_PORT);
        return -1;
    }
    if(mjpgServiceCheck() == MJPG_SERVICE_CHECK_FAILURE)
    {
        printf("mjpg service not running\n");
        return -1;
    }
    while(1)
    {
        memset(buffer, 0, LNE);
        Serial_Gets(fd, buffer);
        if(buffer[2] != 0x46)
            continue;
        del = remove(PICTURE_PATH);
        if(del == -1)
        {
            perror("remove failed");
        }
        printf("remove %d\n", del);
        system(WGET_CMD);
        ret = garbage_classify();
        printf("ret = %d\n", ret);

        switch(ret)
        {
            case DRY_GARBAGE:
                buffer[2] = 0x41;
                OLED_Show_Text("Dry Garbage");
                 sg90_run(PIN);
                 delay(2000);
                 sg90_stop(PIN);
                break;
            case WET_GARBAGE:
                buffer[2] = 0x42;
                OLED_Show_Text("Wet Garbage");
                 sg90_run(PIN);
                 delay(2000);
                 sg90_stop(PIN);
                break;
            case RECYCLE_GARBAGE:
                buffer[2] = 0x43;
                OLED_Show_Text("Recycle Garbage");
                 sg90_run(PIN);
                 delay(2000);
                 sg90_stop(PIN);
                break;
            case HAZARDOUS_GARBAGE:
                buffer[2] = 0x44;
                OLED_Show_Text("Hazardous Garbage");
                 sg90_run(PIN);
                 delay(2000);
                 sg90_stop(PIN);
                break;
            default:
                buffer[2] = 0x45;
                OLED_Show_Text("Unknown Garbage");
                break;
        }
        for(i = 0; i < LNE; i++)
        {
            printf("%02X ", buffer[i]);
        }
        printf("\n");
        Serial_Puts(fd, buffer, LNE);
    }
    garbage_final();
    Serial_Close(fd);
    return 0;

}

#endif
