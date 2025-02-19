#include <stdio.h>
#include <string.h>

#define SIZE 100

typedef struct message{
  long type;
  char msg[SIZE];
}message;

int setType(message *m, int type) {
    m->type = type;
    return 0;
}

void display(char str[][SIZE], int n, char *prompt){
    printf("%s", prompt);
    for(int i=0; i<n; i++){
        printf("\"%s\" ",str[i]);
    }
    puts("");
}
