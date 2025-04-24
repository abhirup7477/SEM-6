#include "udp.h"

void main(){
    int sfd, addr_len, n;
    struct sockaddr_in addr;
    char data[size], result[2*size];

    sfd = socket(domain, type, 0);

    addr.sin_family = domain;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(ip);

    bind(sfd, (struct sockaddr*)&addr, sizeof(addr));
    addr_len = sizeof(addr);

    while(1){
        readInput(data, "Enter the data : ", size);
        sendto(sfd, (void*)data, sizeof(data), 0, (struct sockaddr *)&addr, sizeof(addr));

        if(!strcmp(data, "0000")){
            break;
        }
        puts(data);

        n = recvfrom(sfd, (void*)result, sizeof(result), 0, (struct sockaddr *)&addr, &addr_len);
        result[n] = '\0';
        puts(result);
    }
}