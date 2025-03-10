#include <stdio.h>
#include <string.h>
#include <sys/msg.h>
#include "msgq.h"

void print_reverse(char *str){
    int n = strlen(str);
    for(int i=n-1; i>=0; i--)
        printf("%c",str[i]);
    printf("\n");
}

void main(){
    message roll;
    roll.type = 1;
    int fd = msgget(key, 0666|IPC_CREAT);
    
    char str[max];
    int i, j;
    while(1){
        printf("Receiver is waiting\n\n");

        msgrcv(fd, (void *)&roll, sizeof(roll.msg), 1, 0);
        // print(roll.msg, size);
        if(!strcmp(roll.msg, "000"))
            break;

        // printf("After break\n");
        for(i=0; i<size; i++){
            str[i] = roll.msg[i];
        }
        for(i=size; i<max; i++){
            msgrcv(fd, (void *)&roll, sizeof(roll.msg), 1, 0);
            if(!strcmp(roll.msg, "ok"))
                break;
            // print(roll.msg, size);
            for(j=0; j<size; j++){
                str[i++] = roll.msg[j];
            }
            i --;
        }
        printf("Received data : ");
        puts(str);
        printf("Reverse : ");
        print_reverse(str);
        puts("");
    }
    printf("Receiver is terminating\n");
}