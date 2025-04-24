#include "header.h"

void *sending(void *arg){
    details *d = (details *)arg;
    struct sockaddr_in caddr = d->addr;
    int sfd = d->sfd;
    int len = d->len;
    char msg[size];

    while(1){
        readInput(msg, "", size);
        sendto(sfd, (void*)msg, sizeof(msg), 0, (struct sockaddr *)&caddr, len);

        sleep(1);
    }
    pthread_exit(NULL);
}

void *receiving(void *arg){
    details *d = (details*) arg;
    struct sockaddr_in caddr = d->addr;
    int sfd = d->sfd;
    int len = d->len;
    char msg[size];
    int n;

    while(1){
        n = recvfrom(sfd, (void*)msg, sizeof(msg), 0, (struct sockaddr *)&caddr, &len);
        msg[n] = '\0';
        printf("Received data : %s\n",msg);
        sleep(1);
    }
    pthread_exit(NULL);
}

void main(){
    int sfd;
    struct sockaddr_in addr, caddr;
    details d;

    sfd = socket (domain, type, 0);

    addr.sin_family = domain;
    addr.sin_port = htons(port1);
    addr.sin_addr.s_addr = inet_addr(ip1);

    caddr.sin_family = domain;
    caddr.sin_port = htons(port2);
    caddr.sin_addr.s_addr = inet_addr(ip2);

    d.addr = caddr;
    d.sfd = sfd;
    d.len = sizeof(caddr);

    bind(sfd, (struct sockaddr *)&addr, sizeof(addr));

    pthread_t th1, th2;
    pthread_create(&th1, NULL, (void*)sending, (void*)&d);
    pthread_create(&th2, NULL, (void*)receiving, (void*)&d);

    pthread_join(th1, NULL);
    pthread_join(th2, NULL);
}