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
    serveraddr.sin_port = htons(3389);
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

    int size = 0;
    recedbytes = recv(newsockfd, &size, sizeof(size), 0);
    if (recedbytes == -1) {
        close(sockfd);
        close(newsockfd);
    } 
    printf("%d\n",size);

    int buff[size];
    recedbytes = recv(newsockfd, &buff, sizeof(buff), 0);
    if (recedbytes == -1) {
        close(sockfd);
        close(newsockfd);
    }  

    for(int i=0;i<size;i++){
        printf("%d ",buff[i]);
    }

    int parity = buff[size-1];
    int oneCount;
    for(int i=0;i<size-1;i++){
        if(buff[i]==1)
            oneCount++;
    }
    int unCorrupted;
    if(parity==1 ){
        if(oneCount%2==1)
            unCorrupted = 1;
        else
        unCorrupted = 0;
    } 
    else if(parity==2){
        if(oneCount%2==0)
            unCorrupted = 1;
        else
        unCorrupted = 1;
    }
    printf("%d",unCorrupted);

    sentbytes = send(newsockfd, &unCorrupted, sizeof(unCorrupted), 0);
    if (sentbytes == -1) {
        close(sockfd);
        close(newsockfd);
    }

    close(sockfd);
    close(newsockfd);
}