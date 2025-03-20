#include "udp.h"

void main(){
    int sfd, addr_len, n;
    struct sockaddr_in addr;
    char buff[size];
    sfd = socket(AF_INET, SOCK_DGRAM, 0);

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(ip);
    addr.sin_port = htons(port);

    addr_len = sizeof(addr);

    while(1){
        printf("Enter the string : ");
        fgets(buff, size, stdin);
        buff[strlen(buff) - 1] = '\0';

        sendto(sfd, (void*)buff, sizeof(buff), 0, (struct sockaddr *)&addr, sizeof(addr));

        if(!strcmp(buff, "0000"))
            break;

        n = recvfrom(sfd, (void*)buff, sizeof(buff), 0, (struct sockaddr *)&addr, &addr_len);
        buff[n] = '\0';
        puts(buff);
        puts("");
    }
    printf("\nClient is terminating\n");
    close(sfd);
}