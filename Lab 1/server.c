#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#define MAXSIZE 90

int main ()
{

  int sockfd, newsockfd, retval;
  socklen_t actuallen;
  int recedbytes, sentbytes;
  struct sockaddr_in serveraddr, clientaddr;


  int a = 0;
  sockfd = socket (AF_INET, SOCK_STREAM, 0);

  if (sockfd == -1)
    {
      printf ("\nSocket creation error");
    }
	printf("Connection Started....");
  serveraddr.sin_family = AF_INET;
  serveraddr.sin_port = htons (8080);
  serveraddr.sin_addr.s_addr = htons (INADDR_ANY);
  retval =
    bind (sockfd, (struct sockaddr *) &serveraddr, sizeof (serveraddr));
  if (retval == 1)
    {
      printf ("Binding error");
      close (sockfd);
    }

  retval = listen (sockfd, 1);
  if (retval == -1)
    {
      close (sockfd);
    }

  actuallen = sizeof (clientaddr);
  newsockfd = accept (sockfd, (struct sockaddr *) &clientaddr, &actuallen);


  if (newsockfd == -1)
    {
      close (sockfd);
    }
  int size;
  recedbytes = recv(newsockfd, &size, sizeof(int), 0);
  int buff[size];
  recedbytes = recv (newsockfd, &buff, 10*sizeof(int), 0);

  if (recedbytes == -1)
    {
      close (sockfd);
      close (newsockfd);
    }
  for (int i = 0; i < size; i++)
    {
      printf ("%d  ", buff[i]);
    }
  printf ("\n");
  
  char menu[] = "SERVER MENU\n1. Search\n2. Sort\n3. Split\nEnter choice here : \0";
 
  sentbytes = send (newsockfd, &menu, sizeof (menu), 0);

  if (sentbytes == -1)
    {
      close (sockfd);
      close (newsockfd);
    }

  int choice;
  recedbytes = recv(newsockfd, &choice, sizeof(int), 0);
  printf("\n User choice is %d",choice);
  
  switch(choice){
    case 1:
     printf("");
     char message1[] = "Enter value to be found : (Output will be position if key is found, else -1)\0";
     sentbytes = send(newsockfd, &message1, sizeof(message1), 0);
     int key , pos=-1;
     recedbytes = recv(newsockfd, &key, sizeof(int),0);
     for(int i=0;i<size;i++){
     	if(key==buff[i]){
     		pos = i;
     		break;}
     }
     sentbytes = send(newsockfd, &pos, sizeof(pos),0);
     printf("Key finding operation completed.\n");
    case 2:
    printf("");
    char message2[] = "Enter 1 to sort in ascending or 2 for descending : ";
    sentbytes = send(newsockfd, &message2, sizeof(message2),0);
    int val;
    recedbytes = recv(newsockfd, &val, sizeof(int),0);
    if(val==1){
    	for (int i = 0; i < (size - 1); i++) {
    		pos = i;
			for (int j = i + 1; j < size; j++){
      			if (buff[pos] > buff[j])
        		pos = j;
    			}
    			if (pos != i){
      				int t = buff[i];
      				buff[i] = buff[pos];
      				buff[pos] = t;}
  					}
  				}
  		if(val==2){
    	for (int i = 0; i < (size - 1); i++) {
    		pos = i;
			for (int j = i + 1; j < size; j++){
      			if (buff[pos] < buff[j])
        		pos = j;
    			}
    			if (pos != i){
      				int t = buff[i];
      				buff[i] = buff[pos];
      				buff[pos] = t;}
  					}
		for(int i=0;i<size;i++){
			printf("%d ",buff[i]);
		}
		}
  	sentbytes = send(newsockfd, &buff, sizeof(buff),0);
    printf("Sorting operation completed.\n");	
    
    case 3:
        printf("");
    int odd[size], even[size];
    int k = 0, j=0;
    for (int i=0;i<size;i++){
    	if(buff[i]%2==0){
    		even[k++]=buff[i];
    	}
    	else{
    		odd[j++] = buff[i];
    	}
    }
		printf("Odd array: ");
    	for(int i=0;i<size;i++){
			printf("%d ",odd[i]);
		}
		printf("\nEven array: ");
    	for(int i=0;i<size;i++){
			printf("%d ",even[i]);
		}
		sentbytes = send(newsockfd, &odd, sizeof(odd),0);
		sentbytes = send(newsockfd, &even, sizeof(even), 0);
        printf("Splitting operation completed.\n");	
  }
  close (sockfd);
  close (newsockfd);
}



