#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define size 100

void readInput(char *str){
    printf("Enter the data : ");
    fgets(str, size, stdin);
    str[strlen(str) - 1] = '\0';
}

void reverse(char *str){
    int n = strlen(str);
    char ch;
    for(int i=0; i<n/2; i++){
        ch = str[i];
        str[i] = str[n-i-1];
        str[n-i-1] = ch;
    }
}

void toBin(int n, char *str){
    int i=0;
    while(n != 0){
        if((n & 1))
            str[i++] = '1';
        else
            str[i++] = '0';

        n = n >> 1;
    }
    reverse(str);
}

void main(){
    char str[size], bin[size], oct[size], hex[size];
    readInput(str);

    int n = atoi(str);
    printf("n = %d\n",n);

    toBin(n, bin);
    puts(bin);

    sprintf(oct, "%o", n);
    sprintf(hex, "%X", n);

    puts(oct);
    puts(hex);
}
