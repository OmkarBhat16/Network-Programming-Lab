#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define PORT 8082

void tokenBucket(int input[], int bucketSize, int tokenRate, int n) {
    int tokens = bucketSize, i;
    for (i = 0; i < n; i++) {
        printf("Packet %d arrives\n", i+1);
        if (input[i] <= tokens) {
            printf("Packet %d transmitted\n", i+1);
            tokens -= input[i];
        } else {
            printf("Packet %d discarded\n", i+1);
        }
        tokens += tokenRate;
        if (tokens > bucketSize) tokens = bucketSize; // Cap tokens to bucket size
    }
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    int buffer[1024] = {0}; // Assuming a maximum of 1024 packets

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == 0) {
        printf("Socket creation failed\n");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        printf("Setsockopt failed\n");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        printf("Bind failed\n");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        printf("Listen failed\n");
        exit(EXIT_FAILURE);
    }

    new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
    if (new_socket < 0) {
        printf("Accept failed\n");
        exit(EXIT_FAILURE);
    }

    read(new_socket, buffer, 1024 * sizeof(int));
    int bucketSize = buffer[0];
    int tokenRate = buffer[1];
    int n = buffer[2];

    tokenBucket(buffer + 3, bucketSize, tokenRate, n);

    printf("Token bucket processing completed.\n");

    return 0;
}
