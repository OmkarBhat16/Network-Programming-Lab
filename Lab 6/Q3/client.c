#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define PORT 8080

int main() {
    struct sockaddr_in serv_addr;
    int sock = 0, valread;
    int data[4] = {1, 0, 1, 1}; // Example data
    int hammingCode[7] = {0};

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }

    send(sock, data, 4*sizeof(int), 0);
    printf("Data sent: %d%d%d%d\n", data[0], data[1], data[2], data[3]);

    valread = read(sock, hammingCode, 7*sizeof(int));
    printf("Hamming Code received: ");
    for (int i = 0; i < 7; i++) {
        printf("%d", hammingCode[i]);
    }
    printf("\n");

    return 0;
}
