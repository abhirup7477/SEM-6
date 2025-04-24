#include "udp.h"

void *sending(void *arg){
    char msg[size];
    details *d = (details *)arg;
    struct sockaddr_in caddr = d->addr;
    int sfd = d->sfd;
    int len = d->len;

    while(1){
        readInput(msg, "", size);
        sendto(sfd, (void*)msg, sizeof(msg), 0, (struct sockaddr *)&caddr, len);
        if(!strcmp(msg, "exit")){
            printf("Exiting...\n");
            break;
        }
        sleep(1);
    }
    pthread_exit(NULL);
}

void *receiving(void *arg){
    char msg[size];
    details *d = (details*) arg;
    struct sockaddr_in caddr = d->addr;
    int sfd = d->sfd;
    int len = d->len;
    int n;

    while(1){
        n = recvfrom(sfd, (void*)msg, sizeof(msg), 0, (struct sockaddr *)&caddr, &len);
        msg[n] = '\0';
        if(!strcmp(msg, "exit")){
            printf("Exiting...\n");
            break;
        }
        printf("Received daat : %s\n",msg);
        sleep(1);
    }
    pthread_exit(NULL);
}

void main(){
    int sfd;
    struct sockaddr_in addr, caddr;
    details *d = (details *)malloc(sizeof(details));
    sfd = socket (domain, type, 0);
    if (sfd < 0) {
        perror("Socket creation failed");
    }

    addr.sin_family = domain;
    addr.sin_port = htons(port2);
    addr.sin_addr.s_addr = inet_addr(ip2);

    caddr.sin_family = domain;
    caddr.sin_port = htons(port1);
    caddr.sin_addr.s_addr = inet_addr(ip1);

    if(bind(sfd, (struct sockaddr *)&addr, sizeof(addr)) == 1){
        perror("Bind failed");
    }

    d->sfd = sfd;
    d->addr = caddr;
    d->len = sizeof(caddr);

    pthread_t reader, writer;
    printf("Thread creation\n");
    pthread_create(&reader, NULL, (void *)sending, (void *)d);
    pthread_create(&writer, NULL, (void *)receiving, (void *)d);

    pthread_join(reader, NULL);
    pthread_join(writer, NULL);
}