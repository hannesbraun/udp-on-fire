#include <arpa/inet.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

#include "portOnFire.h"

void sigintHandler(int signum);

int sigintHandled;

int main(void) {
    int tmp;

    // Initialize SIGINT handler
    struct sigaction newSigactionSigint;
    newSigactionSigint.sa_handler = &sigintHandler;
    sigintHandled = 0;
    tmp = sigaction(SIGINT, &newSigactionSigint, NULL);
    if (tmp == -1) {
        perror("Error while changing SIGINT action");
        return EXIT_FAILURE;
    }

    // Own address
    struct sockaddr_in srv_addr;
    srv_addr.sin_family = AF_INET;
    srv_addr.sin_addr.s_addr = INADDR_ANY;
    srv_addr.sin_port = htons(PORT_ON_FIRE);

    // Sender address
    struct sockaddr_in sender_addr;
    unsigned int sender_addr_len = sizeof(sender_addr);

    // Receive buffer
    int val;
    int next = 0;

    // Create socket
    int fd_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd_socket == -1) {
        perror("Error while creating socket");
        return EXIT_FAILURE;
    }

    // Bind socket
    tmp = bind(fd_socket, (struct sockaddr *) &srv_addr, sizeof(srv_addr));
    if (tmp == -1) {
        perror("Error while binding socket");
        return EXIT_FAILURE;
    }

    printf("Ready to burn\n");

    do {
        // Receive message
        tmp = recvfrom(fd_socket, &val, sizeof(val), 0, (struct sockaddr*) &sender_addr, &sender_addr_len);
        if (tmp == -1) {
            perror("Error while receiving message");
        }

        if (val != next) {
            printf("%d : %d\n", next, val);
        }

        next = val + 1;

    } while(val != -1 && sigintHandled == 0);

    // Close socket
    tmp = close(fd_socket);
    if (tmp == -1) {
        perror("Error while closing socket");
    }

    return EXIT_SUCCESS;
}

void sigintHandler(int signum) {
    // Suppress unused parameter warning
    (void) signum;

    sigintHandled++;
    if (sigintHandled > 1) {
        exit(EXIT_FAILURE);
    }
}
