#include <stdio.h>

#define size 4
#define max 32
#define key 1234

typedef struct Message{
    long type;
    char msg[size];
}message;

void print(char *str, int n){
    for(int i=0; i<n; i++){
        printf("%c ",str[i]);
    }
    printf("\n");
}