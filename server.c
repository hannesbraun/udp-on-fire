#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define FIRED_PORT 51069

enum ansi_color {
    blue = 0,
    cyan = 1,
    green = 2,
    magenta = 3,
    red = 4,
    yellow = 5
};

int main(int argc, char** argv) {
    int tmp;

    // Own address
    struct sockaddr_in srv_addr;
    my_addr.sin_family = AF_INET;
    my_addr.sin_addr.s_addr = INADDR_ANY;
    my_addr.sin_port = htons(FIRED_PORT);

    // Sender address
    struct sockaddr_in sender_addr;
    unsigned int sender_addr_len = sizeof(sender_addr);

    // Receive buffer
    int val;
    int next = 0;
    int counter = 0;

    // Create socket
    int fd_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd_socket == -1) {
        perror("Error while creating socket");
        return EXIT_FAILURE;
    }

    // Bind socket
    bind(fd_socket, (struct sockaddr *) &my_addr, sizeof(my_addr));
    
    printf("Ready to burn\n");
    
    do {
        // Receive message
        tmp = recvfrom(fd_socket, &val, sizeof(val), 0, (struct sockaddr*) &sender_addr, &sender_addr_len);
        if (tmp == -1) {
            perror("Error while receiving message");
        }

        if (val != next) {
            printf("%lld : %lld\n", next, val);
            counter++;
        }
        
        next = val + 1;

    } while(val != -1);

    // Close socket
    tmp = close(fd_socket);
    if (tmp == -1) {
        perror("Error while closing socket");
    }

    return EXIT_SUCCESS;
}
