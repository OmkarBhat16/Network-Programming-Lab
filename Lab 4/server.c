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

typedef struct Subjects{
    char Sub[50];
    int Marks;
};

struct Student{
    char Name[50];
    char Addr[100];
    char Dept[50];
    int Registration;
    int Sem;
    char Section;
    struct Subjects Subject[10]; 
}students[10];

void main() {
    time_t t;
    srand((unsigned)time(&t));
    char nameList[50][9] = {"Leola Miley","Fredrick Suniti","Rosalynne Gina","Lucian Briony","Keila Cindra","Isidore Osbert","Sushila Loreen","Rollie Allegra","Anuradha Mikki"};
    char subList[50][9] = {"Math","Chem","Phy","CS","Social","English","Language","French","Sanksrit"};
    char deptList[50][9] = {"Humanities","Computer Science","Information Technology","Mechanical","Chemical","Electrical and Electronics","Civil","Aeronautical","Automobile"};
    char addrList[50][4] = {"8457 Gleichner Ways, Bauchside, ID 51454","Apt. 965 17055 Carroll Throughway, Herzogton","3790 Marion Island, North Raymouth","Suite 892 3006 Swift Islands, Port Sung"};
    int regList[9] = {220911264, 220911265, 220911270, 123154123, 57275829, 108547358, 64838743, 309358811, 55560049};
    for(int i=0;i<10;i++){
        strcpy(students[i].Name,nameList[rand()%9]);
        strcpy(students[i].Addr,addrList[rand()%4]); 
        strcpy(students[i].Dept,deptList[rand()%9]); 
        students[i].Registration = regList[rand()%9];
        students[i].Sem = rand()%9;
        students[i].Section = (char)(rand()%10)+32;
        for(int j = 0 ; j< rand()%10; j++){
            strcpy(students[i].Subject[j].Sub,subList[rand()%9]);
            students[i].Subject[j].Marks = rand()%50 + 40;
        }
    }
    /*
    for(int i=0;i<10;i++){
        printf("%d : %s\n%s\n%s\n\n",i,students[i].Name,students[i].Addr,students[i].Dept);
    }
    */
    printf("Fully connected\n");
    int sockfd, newsockfd, retval;
    socklen_t actuallen;
    int recedbytes, sentbytes;
    struct sockaddr_in serveraddr, clientaddr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd == -1) {
        printf("\nSocket creation error");
    }

    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(3388);
    serveraddr.sin_addr.s_addr = htons(INADDR_ANY);
    retval = bind(sockfd, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
    if (retval == 1) {
        printf("Binding error");
        close(sockfd);
    }

    retval = listen(sockfd, 1);
    if (retval == -1) {
        close(sockfd);
    }

    actuallen = sizeof(clientaddr);
    newsockfd = accept(sockfd, (struct sockaddr*)&clientaddr, &actuallen);

    if (newsockfd == -1) {
        close(sockfd);
    }

    char buff[] = "SERVER MENU :\nEnter student\n    1. Registration Number\n    2. Name of Student\n    3. Subject Code\n Enter Here : ";
    printf("%s",buff);
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
    printf("%d\n",clientChoice);
    char serverResponse[200] = "Invalid Response";
    switch(clientChoice){
        case 1:
            strcpy(serverResponse,"Enter Registration Number of student : \n");
            sentbytes = send(newsockfd, &serverResponse, sizeof(serverResponse), 0);
            int regNum;
            recedbytes = recv(newsockfd, &regNum, sizeof(regNum), 0);
            printf("%d",regNum);
            pid_t childpid;
            if((childpid = fork()) == 0 ){

            }
            break;
        case 2:
            strcpy(serverResponse,"Enter Name of student : \n");
            sentbytes = send(newsockfd, &serverResponse, sizeof(serverResponse), 0);
            char name[50];
            recedbytes = recv(newsockfd, &name, sizeof(name), 0);
            printf("%s",name);

            break;
        case 3:
            strcpy(serverResponse,"Enter Subject Name : \n");
            sentbytes = send(newsockfd, &serverResponse, sizeof(serverResponse), 0);
            char subCode[50];
            recedbytes = recv(newsockfd, &subCode, sizeof(subCode), 0);
            printf("%s",subCode);

            break;
        default:    
            sentbytes = send(newsockfd, &serverResponse, sizeof(serverResponse), 0);
    }

    close(sockfd);
    close(newsockfd);
}
