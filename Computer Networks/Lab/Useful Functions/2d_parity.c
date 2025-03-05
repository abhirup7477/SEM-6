#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define size 100

void readInput(char str[][size], int n){
    for(int i=0; i<n; i++){
        printf("Enter the data : ");
        fgets(str[i], size, stdin);
        str[i][strlen(str[i]) - 1] = '\0';
    }
}

void print(char str[][size], int n){
    for(int i=0; i<n; i++){
        for(int j=0; j<strlen(str[i]); j++){
            printf("%c ",str[i][j]);
        }
        printf("\n");
    }
}

void parity(char str[][size], int n){
    int i, j, count;
    for(i=0; i<n; i++){
        count = 0;
        for(j=0; j<strlen(str[i]); j++){
            if(str[i][j] == '1'){
                count ++;
            }
        }
        if(count % 2){
            str[i][j++] = '1';
        }
        else{
            str[i][j++] = '0';
        }
        str[i][j] = '\0';
    }

    for(i=0; i<=3; i++){
        count = 0;
        for(j=0; j<5; j++){
            if(str[j][i] == '1'){
                count++;
            }
        }
        if(count % 2){
            str[j++][i] = '1';
        }
        else{
            str[j++][i] = '0';
        }
        str[j][i] = '\0';
    }
}

void main(){
    char str[5][size];
    readInput(str, 5);
    print(str, 5);

    parity(str, 5);
    printf("\nParity : \n");
    print(str, 6);
}
