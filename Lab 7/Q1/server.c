#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define PORT 8081

void leakyBucket(int input[], int bucketSize, int outputRate, int n, char *result) {
    int bucket = 0, i, pos = 0;
    for (i = 0; i < n; i++) {
        if (input[i] + bucket > bucketSize) {
            pos += sprintf(result + pos, "Packet %d causes overflow\n", i+1);
        } else {
            bucket += input[i];
            pos += sprintf(result + pos, "Packet %d added to the bucket\n", i+1);
        }
        bucket -= (bucket < outputRate) ? bucket : outputRate;
    }
}

int main() {
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    int buffer[1024] = {0}; // Assuming a maximum of 1024 packets
    char result[4096] = {0}; // Buffer to store the result

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 8081
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind the socket to the port 8081
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    valread = read(new_socket, buffer, 1024*sizeof(int));
    int bucketSize = buffer[0];
    int outputRate = buffer[1];
    int n = buffer[2]; // Number of packets

    leakyBucket(buffer + 3, bucketSize, outputRate, n, result); // Process starting from the fourth element
    send(new_socket, result, strlen(result), 0);

    return 0;
}
