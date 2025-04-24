#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

#define ip1 "127.0.0.1"
#define ip2 "127.0.0.1"
#define port1 4444
#define port2 5555
#define domain AF_INET
#define type SOCK_DGRAM
#define size 100

typedef struct client_details{
    struct sockaddr_in addr;
    int sfd, len;
}details;

void readInput(char *msg, char *prompt, int n){
    printf("%s", prompt);
    fgets(msg, n, stdin);
    msg[strlen(msg) - 1] = '\0';
}