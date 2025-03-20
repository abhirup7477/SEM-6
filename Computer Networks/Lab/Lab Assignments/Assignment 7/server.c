#include "udp.h"

void main(){
    int sfd, caddr_len, n;
    struct sockaddr_in addr, caddr;
    char buff[size];
    sfd = socket(AF_INET, SOCK_DGRAM, 0);

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(ip);
    addr.sin_port = htons(port);

    caddr_len = sizeof(caddr);

    bind(sfd, (struct sockaddr*)&addr, sizeof(addr));

    while(1){
        printf("Server is waiting.\n\n");
        n = recvfrom(sfd, (void*)buff, sizeof(buff), 0, (struct sockaddr *)&caddr, &caddr_len);
        buff[n] = '\0';

        if(!strcmp(buff, "0000"))
            break;
        puts(buff);

        strcpy(buff, "Success");
        sendto(sfd, (void*)buff, sizeof(buff), 0, (struct sockaddr *)&caddr, sizeof(caddr));
        puts("");
    }
    printf("\nServer is terminating\n");
    close(sfd);
}