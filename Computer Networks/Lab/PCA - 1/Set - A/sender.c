#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/msg.h>
#include "msgq.h"

void main(){
    message roll;
    roll.type = 1;
    int fd = msgget(key, 0666|IPC_CREAT), n, j;
    
    char str[max];
    while(1){
        printf("Enter the roll number : ");
        fgets(str, max, stdin);
        str[strlen(str) - 1] = '\0';

        if(!strcmp(str, "000")){
            strcpy(roll.msg, str);
            msgsnd(fd, (void*) &roll, sizeof(roll.msg), 0);
            break;
        }   

        n = strlen(str);
        for(int i=0; i<=n; i++){
            for(j=0; j<size; j++){
                roll.msg[j] = str[i++];
            }
            // print(roll.msg, size);
            msgsnd(fd, (void*) &roll, sizeof(roll.msg), 0);
            i --;
        }
        strcpy(roll.msg, "ok");
        msgsnd(fd, (void*) &roll, sizeof(roll.msg), 0);
        puts("");
    }
    printf("\nSender is terminating\n");
    sleep(1);
    msgctl(fd, IPC_RMID, 0);
}