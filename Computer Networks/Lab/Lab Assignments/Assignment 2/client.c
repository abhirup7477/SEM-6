#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include "parity.h"

#define BACKLOG 5

void main(){
    char path[14] = "socket";

    struct sockaddr_un addr, client_addr;
    int client_addr_len;
    addr.sun_family = AF_UNIX;
    strcpy(addr.sun_path, path);

    int sktfd = socket(AF_UNIX, SOCK_STREAM, 0);
    int result = connect(sktfd, (struct sockaddr *) &addr, sizeof(addr));
    if(result == -1)
        puts("ERROR");

    char str[size-1], parity[size];
    while(1){
        printf("Input : ");
        fgets(str, size-2, stdin);
        str[strlen(str) - 1] = '\0';

        write(sktfd, str, sizeof(str));
        read(sktfd, parity, sizeof(parity));

        if(!strcmp(parity, "end")){
            break;
        }
        display(str, "Input data : ", 0);
        display(parity, "Modified data : ", 1);
        puts("");
    }

    printf("\nClient program terminating\n");

    close(sktfd);
    unlink(path);
}
