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

main() {
    int sockfd, retval;
    int recedbytes, sentbytes;
    struct sockaddr_in serveraddr;
    char buff[200];
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("\nSocket Creation Error");
    }
    printf("%i", sockfd);
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(3388);
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    retval = connect(sockfd, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
    
    if (retval == -1) {
        printf("Connection error");
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

    switch(clientChoice){
        case 1:
            printf("");
            int reg_num; 
            scanf("%d",&reg_num); 
            sentbytes = send(sockfd, &reg_num, sizeof(reg_num), 0);
            break;
        case 2:
            printf("");
            char name[50];
            scanf("%s",name);
            sentbytes = send(sockfd, &name, sizeof(name), 0);
            break;
        case 3:
            printf("");
            char subCode[50];
            scanf("%s",subCode);
            sentbytes = send(sockfd, &subCode, sizeof(subCode), 0);
            break;
        default: 
            printf("Invalid Case");
            close(sockfd);

    }
}
