#include "tcp.h"

void bitstuffing(char *str, char *result){
    int i, j=0, count = 0, flag = 0;
    int n = strlen(str);
    for(i=0; i<n; i++){
        result[j++] = str[i];
        if(str[i] == '0'){
            count = 0;
            flag = 1;
        }
        else{
            count++;
            if(count == 5 && flag == 1){
                result[j++] = '0';
                flag = 0;
            }
        }
    }
    result[j] = '\0';
}

void *evaluate(void *arg){
    client c = *((client *)arg);
    char msg[size], result[2*size];

    while(1){
        read(c.cfd, msg, sizeof(msg));

        if(!strcmp(msg, "0000"))
            break;
        
        printf("Client - %d\n",c.i);
        puts(msg);
        bitstuffing(msg, result);
        puts(result);
        write(c.cfd, result, sizeof(result));
        puts("");
    }
    pthread_exit(NULL);
}

int main(){
    int sfd, cfd, len;
    struct sockaddr_in addr, caddr;

    addr.sin_family = domain;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(ip);

    sfd = socket(domain, type, 0);
    bind(sfd, (struct sockaddr *)&addr, sizeof(addr));
    listen(sfd, 5);

    len = sizeof(caddr);
    client c;
    c.i = 0;
    pthread_t th;
    while(1){
        cfd = accept(sfd, (struct sockaddr *)&caddr, &len);
        c.cfd = cfd;
        ++c.i;
        pthread_create(&th, NULL, (void *)evaluate, (void *)&c);
        printf("Tread created for client-%d\n",c.i);
    }

    return 0;
}