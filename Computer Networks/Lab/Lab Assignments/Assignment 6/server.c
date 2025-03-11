#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <arpa/inet.h>

#define key 1234
#define port 4444
#define size 50
#define path "socket_path"

int isValid(char *str){
    int i, j, count=0, n = strlen(str), sum=0;
    for(i=0; i<n; i++){
        if(!isdigit(str[i]) && str[i]!='.'){
            //puts("Condition - 1");
            return 0;
        }
        else if(isdigit(str[i])){
            //puts("Condition - 2");
            sum = sum * 10 + (str[i]-'0');
        }
        else{
            //puts("Condition - 3");
            count++;
            if(count > 3)
                return 0;
            else if(sum > 255)
                return 0;
            sum = 0;

        }
    }
    if(count < 3)
        return 0;
    return 1;
}

void main(){
    struct sockaddr_in addr, caddr;
    int sfd, cfd, caddr_len, ans;
    char msg[size];
    unlink(path);

    sfd = socket(AF_INET, SOCK_STREAM, 0);

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(4444);

    bind(sfd, (struct sockaddr *) &addr, sizeof(addr));
    listen(sfd, 1);

    caddr_len = sizeof(caddr);
    cfd = accept(sfd, (struct sockaddr *)&addr, &caddr_len);

    while(1){
        printf("Server is waiting\n\n");

        read(cfd, msg, sizeof(msg));
        if(!strcmp(msg, "0000"))
            break;
        printf("Received data : %s\n",msg);

        ans = isValid(msg);
        if(ans)
            strcpy(msg, "Valid ip address!");
        else 
            strcpy(msg, "Invalid ip address!");

        puts(msg);
        write(cfd, msg, sizeof(msg));
        puts("");
    }
    printf("Server is terminating\n");
    usleep(1000);
    close(cfd);
    unlink(path);
}
