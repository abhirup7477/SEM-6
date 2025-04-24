#include "udp.h"

void main(){
    int sfd, len, n;
    struct sockaddr_in addr, caddr;
    char data[size], result[2*size];

    sfd = socket(domain, type, 0);
    printf("sfd = %d\n",sfd);

    addr.sin_family = domain;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(ip);

    if(bind(sfd, (struct sockaddr *)&addr, sizeof(addr)) == -1){
        printf("Bind failed!\n");
        exit(1);
    }

    len = sizeof(caddr);

    while(1){
        printf("Server is waiting\n\n");
        n = recvfrom(sfd, (void*)data, sizeof(data), 0, (struct sockaddr *)&caddr, &len);
        data[n] = '\0';

        if(!strcmp(data, "0000")){
            break;
        }
        puts(data);
        strcpy(result, "Success");

        sendto(sfd, (void*)result, sizeof(result), 0, (struct sockaddr*)&caddr, len);
        puts("");
    }
}