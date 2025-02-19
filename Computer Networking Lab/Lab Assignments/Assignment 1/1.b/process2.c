#include "msgq.h"
#include <string.h>
#include <stdlib.h>
#include <sys/msg.h>

void sort(char names[][SIZE], int n){
    char min[SIZE];
    for(int i=0; i<n; i++){
        int idx = i;
        strcpy(min, names[i]);
        for(int j=i+1; j<n; j++){
            if(strcmp(min, names[j]) > 0){
                strcpy(min, names[j]);
                idx = j;
            }
        }

        if(idx != i){
            strcpy(names[idx], names[i]);
            strcpy(names[i], min);
        }
    }
}

void main(){

    int msgid1 = msgget(1236, 0666 | IPC_CREAT);
    int msgid2 = msgget(1235, 0666 | IPC_CREAT);

    message N, name, roll;
    msgrcv(msgid1, (void*) &N, sizeof(N.msg), 1, 0);
    int n = atoi(N.msg);
    printf("Waiting to receive the names of the students (%d) from process-1.\n",n);

    char names[n][SIZE];
    for(int i=0; i<n; i++){
        msgrcv(msgid1, (void*) &name, sizeof(name.msg), 2, 0);

        strcpy(names[i], name.msg);
    }
    display(names, n, "\nStudents' Names : ");
    sort(names, n);
    display(names, n, "\nSorted Names : ");

    printf("\nSending the sorted names back to process-1\n");
    for(int i=0; i<n; i++){
        strcpy(name.msg, names[i]);
        msgsnd(msgid2, (void*) &name, sizeof(name.msg), 0);
    }
}
