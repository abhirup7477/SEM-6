#include "msgq.h"
#include <stdlib.h>
#include <string.h>
#include <sys/msg.h>
#include <unistd.h>


void readInput(char str[], char *inputPrompt, int size) {
    printf("%s",inputPrompt);
    fgets(str, size, stdin);
    str[strlen(str) - 1] = '\0';
}

void main(){
    char num[10];
    printf("Enter the number of students : ");
    fgets(num, 10, stdin);
    num[strlen(num) - 1] = '\0';

    int msgid1 = msgget(1236, 0666 | IPC_CREAT);
    int msgid2 = msgget(1235, 0666 | IPC_CREAT);

    int n = atoi(num);

    message N, name, roll;

    setType(&N, 1);
    setType(&name, 2);
    setType(&roll, 3);

    strcpy(N.msg, num);
    msgsnd(msgid1, (void*) &N, sizeof(N.msg), 0);
    msgsnd(msgid1, (void*) &N, sizeof(N.msg), 0);

    char str1[SIZE], str2[SIZE];
    char rolls[n][SIZE], names[n][SIZE];

    printf("\nEnter the details of %d students\n",n);
    for(int i=1; i<=n; i++){
        printf("\nStudent - %d\n",i);
        printf("-------------------\n");

        readInput(str1, "Enter name: ", SIZE);
        strcpy(name.msg, str1);
        msgsnd(msgid1, (void*) &name, sizeof(name.msg), 0);

        readInput(str2, "Enter roll: ", SIZE);
        strcpy(roll.msg, str2);
        msgsnd(msgid1, (void*) &roll, sizeof(roll.msg), 0);
    }

    for(int i=0; i<n; i++){
        msgrcv(msgid2, (void*) &name, sizeof(name.msg), 2, 0);
        strcpy(names[i], name.msg);

        msgrcv(msgid2, (void*) &roll, sizeof(roll.msg), 3, 0);
        strcpy(rolls[i], roll.msg);
    }

    printf("\nWaiting to receive the sorted names and roll numbers from process-2 and process-3 recespectively\n");
    display(names, n, "\nSorted names : ");
    display(rolls, n, "\nSorted roll numbers : ");

    sleep(2);
    msgctl(msgid1, IPC_RMID, 0);
}
