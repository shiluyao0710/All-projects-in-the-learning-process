#include "socket.h"

int socket_init(char *ip,  int port)
{
    int sockfd;
    struct sockaddr_in serv_addr;

    // create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        printf("ERROR: Failed to create socket\n");
        return -1;
    }

    // set server address
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    if (inet_aton(ip, &serv_addr.sin_addr) == 0) {
        printf("ERROR: Invalid IP address\n");
        return -1;
    }

    //bind socket
    if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("ERROR: Failed to bind socket\n");
        return -1;
    }

    //listen socket
    if (listen(sockfd, 1) < 0) {
        printf("ERROR: Failed to listen socket\n");
        return -1;
    }

    return sockfd;
}
