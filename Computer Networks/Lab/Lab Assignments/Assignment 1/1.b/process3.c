#include "msgq.h"
#include <string.h>
#include <stdlib.h>
#include <sys/msg.h>

void sort(int rollNos[], char rolls[][SIZE], int n){
    char str[SIZE];
    for(int i=0; i<n; i++){
        int idx = i;
        int min = rollNos[i];
        for(int j=i+1; j<n; j++){
            if(min > rollNos[j]){
                min = rollNos[j];
                idx = j;
            }
        }

        if(idx != i){
            rollNos[idx] = rollNos[i];
            rollNos[i] = min;

            strcpy(str, rolls[idx]);
            strcpy(rolls[idx], rolls[i]);
            strcpy(rolls[i], str);
        }
    }
}

void main(){

    int msgid1 = msgget(1236, 0666 | IPC_CREAT);
    int msgid2 = msgget(1235, 0666 | IPC_CREAT);

    message N, name, roll;
    msgrcv(msgid1, (void*) &N, sizeof(N.msg), 1, 0);
    int n = atoi(N.msg);
    printf("Waiting to receive the roll numbers of the students (%d) from process-1.\n",n);

    char rolls[n][SIZE];
    int rollNos[n];

    for(int i=0; i<n; i++){
        msgrcv(msgid1, (void*) &roll, sizeof(roll.msg), 3, 0);

        strcpy(rolls[i], roll.msg);
        rollNos[i] = atoi(roll.msg);
    }
    display(rolls, n, "\nRoll Numbers : ");
    sort(rollNos, rolls, n);
    display(rolls, n, "\nSorted Roll Numbers : ");

    printf("\nSending the sorted roll numbers back to process-1\n");
    for(int i=0; i<n; i++){
        strcpy(roll.msg, rolls[i]);
        msgsnd(msgid2, (void*) &roll, sizeof(roll.msg), 0);
    }
}
