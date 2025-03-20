#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <arpa/inet.h>

#define key 1234
#define port 4444
#define size 50

void main(){
    struct sockaddr_in addr;
    int sfd;
    char msg[size];

    sfd = socket(AF_INET, SOCK_STREAM, 0);

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(4444);

    connect(sfd, (struct sockaddr *)&addr, sizeof(addr));

    while(1){
        printf("Enter the data : ");
        fgets(msg, size, stdin);
        msg[strlen(msg) - 1] = '\0';

        write(sfd, msg, sizeof(msg));
        if(!strcmp(msg, "0000"))
            break;

        read(sfd, msg, sizeof(msg));
        puts(msg);
        puts("");
    }
    printf("\nClient is terminating\n");
    close(sfd);
}
