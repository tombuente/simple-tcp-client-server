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

    bind(sockfd, (struct sockaddr *) &addr, sizeof(addr));
    err = listen(sockfd, 8);
    if (err == -1) {
        perror("Error preparing to accept connections");
        exit(EXIT_FAILURE);
    }
    int client_sockfd = accept(sockfd, NULL, NULL);

    char msg[512] = "Hello from the server.";
    err = send(client_sockfd, msg, sizeof(msg), 0);
    if (err == -1) {
        perror("Error sending bytes");
        exit(EXIT_FAILURE);
    }

    close(sockfd);

    return 0;
}
