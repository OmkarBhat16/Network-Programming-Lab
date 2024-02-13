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
#define MAXSIZE 50

int main() {
    int sockfd, retval;
    int recedbytes, sentbytes;
    struct sockaddr_in serveraddr;
    char buff[200];
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("\nSocket Creation Error");
    }
    //printf("%i", sockfd);
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(3388);
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    retval = connect(sockfd, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
    
    if (retval == -1) {
        printf("Connection error\n");
    }

    printf("Fully connected");
    recedbytes = recv(sockfd, &buff, sizeof(buff), 0);
    puts(buff);
    printf("\n");
    
    int clientChoice;
    scanf("%d",&clientChoice);

    sentbytes = send(sockfd, &clientChoice, sizeof(clientChoice), 0);
    if (sentbytes == -1) {
        printf("!!");
        close(sockfd);
    }

    recedbytes = recv(sockfd, &buff, sizeof(buff), 0);
    puts(buff);
    printf("\n");

}