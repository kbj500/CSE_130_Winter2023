#include "asgn2_helper_funcs.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main(int argc, char *argv[]) {

    //printf("\n args : %d", argc);
    if (argc != 2) {
        printf("Invalid port\n");
        return 1;
    }

    char *num = argv[1];

    for (unsigned int i = 0; i < strlen(num); i++) {

        if (!isdigit(num[i])) {
            printf("Invalid port\n");
            return 1;
        }
    }

    int port;

    sscanf(num, "%d", &port);

    if (!(port >= 1 && port <= 65535)) {
        printf("Invalid port\n");
        return 1;
    }

    printf("\n Port: %d\n", port);

    Listener_Socket *sock = malloc(sizeof(Listener_Socket));

    int port_valid = listener_init(sock, port);

    printf("\n %d \n", port_valid);
}
