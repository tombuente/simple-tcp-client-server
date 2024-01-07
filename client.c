#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int err;

int main(void) {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(9001);
    addr.sin_addr.s_addr = INADDR_ANY;

    err = connect(sockfd, (struct sockaddr *) &addr, sizeof(addr));
    if (err == -1) {
        perror("Error connecting to server");
        exit(EXIT_FAILURE);
    }

    char resbuf[512];
    err = recv(sockfd, &resbuf, sizeof(resbuf), 0);
    if (err == -1) {
        perror("Error receiving bytes");
        exit(EXIT_FAILURE);
    }

    printf("Response: %s\n", resbuf);

    close(sockfd);

    return 0;
}
