#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <unistd.h>

#define size 100
#define ip1 "127.0.0.1"
#define ip2 "127.0.0.1"
#define port1 4444
#define port2 5555
#define domain AF_INET
#define type SOCK_DGRAM

typedef struct Client_Details{
    struct sockaddr_in addr;
    int len;
    int sfd;
}details;

void readInput(char *msg, char *prompt, int n){
    printf("%s", prompt);
    fgets(msg, n, stdin);
    msg[strlen(msg) - 1] = '\0';
}