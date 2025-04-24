#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>


#define size 100
#define ip "239.0.0.1"
#define port 8888
#define domain AF_INET
#define type SOCK_DGRAM

int sfd, mlen, reuse = 1;
struct sockaddr_in addr, maddr;
struct ip_mreq mreq;
char name[size];
int flag = 0;

void *sending(void *arg){
    struct sockaddr_in saddr = maddr;;
    int slen = sizeof(saddr);
    char msg[size], input[size];
    while(1){
        fgets(input, size, stdin);
        input[strlen(input) - 1] = '\0';

        flag = 1;

        strcpy(msg, name);
        strcat(msg, " : ");
        strcat(msg, input);

        sendto(sfd, (void*)msg, sizeof(msg), 0, (struct sockaddr*)&saddr, slen);
    }
    pthread_exit(NULL);
}

void *receiving(void *arg){
    struct sockaddr_in raddr = maddr;
    int rlen = sizeof(raddr);
    char msg[size];

    while(1){
        int n = recvfrom(sfd, (void*)msg, sizeof(msg), 0, (struct sockaddr*)&raddr, &rlen);
        msg[n] = '\0';
        if(!flag){
            puts(msg);
        }
        flag = 0;
    }
    pthread_exit(NULL);
}

int main(int argc, char const *argv[])
{
    strcpy(name, argv[1]);
    sfd = socket(domain, type, 0);

    addr.sin_family = domain;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    maddr.sin_family = domain;
    maddr.sin_port = htons(port);
    maddr.sin_addr.s_addr = inet_addr(ip);
    mlen = sizeof(maddr);

    setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
    bind(sfd, (struct sockaddr *)&addr, sizeof(addr));

    mreq.imr_multiaddr.s_addr = inet_addr(ip);
    mreq.imr_interface.s_addr = INADDR_ANY;
    setsockopt(sfd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq));

    pthread_t th1, th2;
    pthread_create(&th1, NULL, (void*)sending, NULL);
    pthread_create(&th2, NULL, (void*)receiving, NULL);

    pthread_join(th1, NULL);
    pthread_join(th2, NULL);

    return 0;
}
