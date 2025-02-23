#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include "parity.h"

#define BACKLOG 5

void main(){
    char path[14] = "socket";
    unlink(path);

    struct sockaddr_un addr, client_addr;
    int client_addr_len;
    addr.sun_family = AF_UNIX;
    strcpy(addr.sun_path, path);

    int sktfd = socket(AF_UNIX, SOCK_STREAM, 0);
    bind(sktfd, (struct sockaddr *) &addr, sizeof(addr));
    listen(sktfd, BACKLOG);

    client_addr_len = sizeof(client_addr);
    int cfd = accept(sktfd, (struct sockaddr *) &client_addr, &client_addr_len);

    while(1){
        char str[size-1], parity[size];
        read(cfd, str, sizeof(str));

        if(!strcmp(str, "end")){
            write(cfd, str, sizeof(str));
            break;
        }

        display(str, "Reveived data : ", 0);
        char p = countParity(str, parity);
        display(parity, "Modified data: ", 1);
        printf("Parity = %c\n",p);
        
        write(cfd, parity, sizeof(parity));
        puts("");
    }

    printf("Server program terminating\n");

    close(cfd);
    unlink(path);
}
