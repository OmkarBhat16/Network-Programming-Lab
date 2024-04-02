#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define PORT 8081

int main() {
    struct sockaddr_in serv_addr;
    int sock = 0, valread;
    int buffer[1024] = {10, 1, 9, 4, 4, 4, 4, 4, 4, 4, 4, 4}; // Example: bucketSize, outputRate, n, packets...
    char result[4096] = {0};

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }

    send(sock, buffer, sizeof(buffer), 0);
    valread = read(sock, result, 4096);
    printf("%s", result);

    return 0;
}
