#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <arpa/inet.h>
#include <pthread.h>

#define size 100
#define domain AF_INET
#define type SOCK_STREAM
#define ip "127.0.0.1"
#define port 5555

typedef struct ClientsDetails{
    int cfd, i;
}client;

void readInput(char *str, char *prompt, int n){
    printf("%s", prompt);
    fgets(str, n, stdin);
    str[strlen(str) - 1] = '\0';
}