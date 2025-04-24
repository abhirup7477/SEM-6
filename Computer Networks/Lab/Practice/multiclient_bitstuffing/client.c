#include "tcp.h"

void *evaluate(void *arg){
    client c = *((client *)arg);
    char msg[size];

    while(1){
        read(c.cfd, msg, sizeof(msg));

        if(!strcmp(msg, "0000"))
            break;
        
        puts(msg);
        strcpy(msg, "success");
        write(c.cfd, msg, sizeof(msg));
    }
    pthread_exit(NULL);
}

int main(){
    int sfd;
    struct sockaddr_in addr;

    addr.sin_family = domain;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(ip);

    sfd = socket(domain, type, 0);

    int r = connect(sfd, (struct sockaddr *)&addr, sizeof(addr));
    char msg[size], result[2*size];
    while(1){
        readInput(msg, "Data : ", size);
        write(sfd, msg, sizeof(msg));
        if(!strcmp(msg, "0000"))
            break;
        read(sfd, result, sizeof(result));
        puts(result);
    }

    return 0;
}