#include "udp.h"

void main(){
    int sfd, caddr_len, n;
    struct sockaddr_in addr, caddr;
    char data[size], result[2*size];

    sfd = socket(domain, type, 0);

    addr.sin_family = domain;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(ip);

    bind(sfd, (struct sockaddr*)&addr, sizeof(addr));
    caddr_len = sizeof(caddr);

    while(1){
        printf("Server is waiting.\n\n");
        n = recvfrom(sfd, (void*)data, sizeof(data), 0, (struct sockaddr *)&caddr, &caddr_len);
        data[n] = '\0';
        puts(data);

        if(!strcmp(data, "0000")){
            break;
        }

        strcpy(result, "Successful");
        sendto(sfd, (void*)result, sizeof(result), 0, (struct sockaddr *)&caddr, sizeof(caddr));
        puts("");
    }
}