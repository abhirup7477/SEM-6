#include "udp.h"

void main(){
    int sfd, len, n;
    struct sockaddr_in addr;
    char data[size], result[2*size];

    sfd = socket(domain, type, 0);
    printf("sfd = %d\n",sfd);

    addr.sin_family = domain;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(ip);

    len = sizeof(addr);

    while(1){
        readInput(data, "\nEnter the data : ", size);
        sendto(sfd, (void*)data, sizeof(data), 0, (struct sockaddr*)&addr, len);


        if(!strcmp(data, "0000")){
            break;
        }
        puts(data);
        strcpy(result, "Success");

        n = recvfrom(sfd, (void*)result, sizeof(result), 0, (struct sockaddr *)&addr, &len);
        result[n] = '\0';
        puts(result);
    }
}