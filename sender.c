#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>

#include "portOnFire.h"

int main(int argc, char** argv) {
    // Check argument count
    if (argc != 2) {
        fprintf(stderr, "Wrong number of arguments\n");
        fprintf(stderr, "Usage: %s <Receiver IP>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Temporary variable for general usage
    int tmp;

    // Value to send
    int val = 0;

    // Creating socket
    int fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd == -1) {
        perror("Error while creating socket");
        return EXIT_FAILURE;
    }

    // Setting the address family to AF_INET
    struct sockaddr_in recv_addr;
    recv_addr.sin_family = AF_INET;

    // Setting the receiver ip address
    recv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    if (recv_addr.sin_addr.s_addr == INADDR_NONE) {
        fprintf(stderr, "Error: invalid IP address\n");
        return EXIT_FAILURE;
    }

    // Setting the receiver port
    recv_addr.sin_port = htons(PORT_ON_FIRE);

    // Calculating length of server address data
    unsigned int recv_addr_len = sizeof(recv_addr);

    // Sending string to receiver
    do {
        tmp = sendto(fd, &val, sizeof(val), 0, (struct sockaddr *) &recv_addr, recv_addr_len);
        if (tmp == -1) {
            perror("Error while sending the data to the receiver");
        }
        val++;
    } while (val != -1);

    // Closing the socket
    tmp = close(fd);
    if (tmp == -1) {
        perror("Error while closing the socket");
    }

    return EXIT_SUCCESS;
}
