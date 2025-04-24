#include "udp.h"

struct sockaddr_in addr, caddr;
int sfd, caddr_len;

void *sending(void *arg){
    char msg[size];
    while(1){
        fgets(msg, size, stdin);
        msg[strlen(msg) - 1] = '\0';
        sendto(sfd, (void *)msg, sizeof(msg), 0, (struct sockaddr *)&caddr, (sizeof(caddr)));
        printf("Data : %s\n\n",msg);
    }
}

void *receiving(void *arg){
    char msg[size];
    caddr_len = sizeof(caddr);
    int n;
    while(1){
        n = recvfrom(sfd, (void*)msg, (sizeof(msg)), 0, (struct sockaddr *)&caddr, &caddr_len);
        msg[n] = '\0';
        printf("Received data : %s\n\n",msg);
        sleep(1);
    }
    pthread_exit(NULL);
}

void main(){
    sfd = socket (AF_INET, SOCK_DGRAM, 0);

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(ip);
    addr.sin_port = htons(port2);

    caddr.sin_family = AF_INET;
    caddr.sin_addr.s_addr = inet_addr(ip);
    caddr.sin_port = htons(port1);

    bind(sfd, (struct sockaddr *)&addr, sizeof(addr));

    pthread_t th1, th2;
    pthread_create(&th1, NULL, (void *)sending, NULL);
    pthread_create(&th2, NULL, (void *)receiving, NULL);

    pthread_join(th1, NULL);
    pthread_join(th2, NULL);
}