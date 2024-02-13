#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include <arpa/inet.h>
#include <stdlib.h>
#define MAXSIZE 50

void main ()
{
  int sockfd, retval;
  int recedbytes, sentbytes;
  struct sockaddr_in serveraddr;
  sockfd = socket (AF_INET, SOCK_STREAM, 0);
  if (sockfd == -1)
    {
      printf ("\nSocket Creation Error");
    }
    
  printf ("%i\n", sockfd);
  serveraddr.sin_family = AF_INET;
  serveraddr.sin_port = htons (8080);
  serveraddr.sin_addr.s_addr = inet_addr ("127.0.0.1");
  
  retval = connect (sockfd, (struct sockaddr *) &serveraddr, sizeof (serveraddr));
  if (retval == -1){
      printf ("Connection error\n");}
      
  printf("Enter the size of array here : \n");
  int size;
  scanf("%d",&size);
  sentbytes = send(sockfd, &size , sizeof(int),0);
  int buff[size];	
  printf ("Beginning the program... size of array = %d\n",size);
  printf ("enter the array here : \n");
  for (int i = 0; i < size; i++)
    { printf("%d	",i);
      scanf("%d",&buff[i]);
      if(i==size-1)
      	break;
    }

  sentbytes = send (sockfd, &buff, size*sizeof(int), 0);

  if (sentbytes == -1){
      printf ("!!");
      close (sockfd);}
      
 char recved[2000];
  recedbytes = recv (sockfd, &recved, sizeof(recved) , 0);
  puts(recved);
  printf("\n");

 int choice;
 scanf("%d",&choice);
 sentbytes = send( sockfd, &choice,sizeof(int),0);
 
 recedbytes = recv(sockfd,&recved,sizeof(recved),0);
 puts(recved);
 switch(choice){
 	case 1:
    	printf("");
 		int key,pos;
 		scanf("%d",&key);
 		sentbytes = send(sockfd,&key,sizeof(key),0);
 		recedbytes = recv(sockfd,&pos,sizeof(int),0);
 		printf("\nKey found at : %d\n",pos);
 	case 2:
 		printf("");
 		int val;
 		scanf("%d",&val);
 		sentbytes = send(sockfd,&val,sizeof(val),0);
 		recedbytes = recv(sockfd,&buff,sizeof(buff),0);
 		printf("Sorted Array : ");
 		for(int i=0;i<size;i++){
 			printf("%d ",buff[i]);
 		}
	case 3:
		printf("");
		int odd[size], even[size];
		recedbytes = recv(sockfd,&odd,sizeof(odd),0);
		recedbytes = recv(sockfd,&even,sizeof(even),0);
		printf("Odd array: ");
    	for(int i=0;i<size;i++){
			printf("%d ",odd[i]);
		}
		printf("\nEven array: ");
    	for(int i=0;i<size;i++){
			printf("%d ",even[i]);
		}
 }
  printf ("\n");
  close (sockfd);
}

