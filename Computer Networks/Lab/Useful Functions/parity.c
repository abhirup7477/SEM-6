#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define size 100

void readInput(char *str){
    printf("Enter the data : ");
    fgets(str, size, stdin);
    str[strlen(str) - 1] = '\0';
}

char parity(char *str){
    int n = strlen(str), count = 0, i;
    char ch;
    for(i=0; i<n; i++){
        if(str[i] == '1')
            count++;
    }
    if(count % 2){
        ch = '1';
        str[i++] = '1';
    }
    else{
        ch = '0';
        str[i++] = '0';
    }
    str[i] = '\0';
    return ch;
}

void main(){
    char str[size];
    readInput(str);
    char ch = parity(str);
    printf("parity = %c\n",ch);
    puts(str);
}
