#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <arpa/inet.h>

#define key 1234
#define port 4444
#define size 50

void bitstuffing(char *str, char *result){
    int n = strlen(str), i=0, j=0, count = 0,flag = 0;
    while(i < n){
        result[j++] = str[i];
        if(str[i] == '0'){
		count = 0;
		flag = 1;
	}
        else{
        	count ++;
		if(count == 5 && flag == 1){
			result[j++] = '0';
			flag = 0;
		}
        }
        i++;
    }
    result[j] = '\0';
}

void main(){
    struct sockaddr_in addr , caddr;
    int sfd, cfd, caddr_len;
    char msg[2*size], result[2*size];

    sfd = socket(AF_INET, SOCK_STREAM, 0);

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(port);

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

        bitstuffing(msg, result);
        strcpy(msg, result);
        printf("Processed data : %s\n",msg);
        write(cfd, msg, sizeof(msg));
        puts("");
    }
    printf("Server is terminating\n");
    usleep(1000);
    close(cfd);
    unlink(path);
}
