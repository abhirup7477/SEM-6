#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define size 20

void readInput(char *str, char *prompt){
    printf("%s",prompt);
    fgets(str, size, stdin);
    str[strlen(str) - 1] = '\0';
}

void bitstuffing(char *str, char *result){
    int n = strlen(str), i=0, j=0, count = 0;
    while(i < n){
        result[j++] = str[i];
        if(str[i] == '0'){
            if(count == 4){
                result[j++] = '1';
                count = 0;
            }
            else{
                count ++;
            }
        }
        else{
            count = 0;
        }
        i++;
    }
    result[j] = '\0';
}

void main(){
    char str[size], result[2*size];
    readInput(str, "Enter the data : ");
    bitstuffing(str, result);
    puts(result);
}
