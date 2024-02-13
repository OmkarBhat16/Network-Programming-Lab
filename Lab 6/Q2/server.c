#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <time.h>
#define MAXSIZE 90

void main() {
    int sockfd, newsockfd, retval;
    socklen_t actuallen;
    int recedbytes, sentbytes;
    struct sockaddr_in serveraddr, clientaddr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd == -1) {
        printf("\nSocket creation error\n");
    }

    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(3388);
    serveraddr.sin_addr.s_addr = htons(INADDR_ANY);
    retval = bind(sockfd, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
    if (retval == 1) {
        printf("\nBinding error\n");
        close(sockfd);
    }

    retval = listen(sockfd, 1);
    if (retval == -1) {
        close(sockfd);
    }
    printf("Fully connected\n");

    actuallen = sizeof(clientaddr);
    newsockfd = accept(sockfd, (struct sockaddr*)&clientaddr, &actuallen);

    if (newsockfd == -1) {
        close(sockfd);
    }

    char buff[50];
    sentbytes = send(newsockfd, &buff, sizeof(buff), 0);
    if (sentbytes == -1) {
        close(sockfd);
        close(newsockfd);
    }

    int clientChoice; 
    recedbytes = recv(newsockfd, &clientChoice, sizeof(clientChoice), 0);
    if (recedbytes == -1) {
        close(sockfd);
        close(newsockfd);
    }   

    close(sockfd);
    close(newsockfd);
}