#include <arpa/inet.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
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

    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(3389);
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    retval = connect(sockfd, (struct sockaddr*)&serveraddr, sizeof(serveraddr));

    if (retval == -1) {
        printf("Connection error\n");
    }

    printf("Fully connected\n");

    printf("Enter size of array : ");
    int n;
    scanf("%d", &n);
    int arr[n + 2];
    int t = n + 2;
    sentbytes = send(sockfd, &t, sizeof(t), 0);
    if (sentbytes == -1) {
        printf("!!");
        close(sockfd);
    }

    int oneCount = 0;
    printf("Enter the binary array : ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
        if (arr[i] == 1) oneCount++;
        if (arr[i] != 0 && arr[i] != 1) arr[i] = 0;
    }
    printf("oneCount = %d\n", oneCount);
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    printf("\nEnter 1 for Odd and 2 for Even parity : ");
    int parity;
    scanf("%d", &parity);
    printf("%d",parity);
    parity %= 2;
    printf("%d",parity);
    if (parity == 1) {
        arr[n + 1] = 1;
        if (oneCount % 2 == 1) {
            arr[n] = 0;
        } else {
            arr[n] = 1;
        }
    } else if (parity == 0) {
        arr[n + 1] = 2;
        if (oneCount % 2 == 1) {
            arr[n] = 1;
        } else {
            arr[n] = 0;
        }
    }
    printf("\n");
    for (int i = 0; i < n + 2; i++) {
        printf("%d ", arr[i]);
    }

    sentbytes = send(sockfd, &arr, sizeof(arr), 0);
    if (sentbytes == -1) {
        printf("!!");
        close(sockfd);
    }

    int res;
    recedbytes = recv(sockfd, &res, sizeof(res), 0);

    printf("\n Result = %s", res==1?"True":"False");
}