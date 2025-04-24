#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define size 100
#define domain AF_INET
#define type SOCK_DGRAM
#define port 4444
#define ip "127.0.0.1"

void readInput(char *str, char *prompt, int n){
    printf("%s", prompt);
    fgets(str, n, stdin);
    str[strlen(str) - 1] = '\0';
}