#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define size 20

void readInput(char *str, char *prompt){
    printf("%s", prompt);
    fgets(str, size-1, stdin);
    str[strlen(str) - 1] = '\0';
}

int padding(char *data, char *divisor, char *result){
    int dvsr_len = strlen(divisor);
    strcpy(result, data);
    int n = dvsr_len - 1;

    int i = strlen(data), j;
    for( j = 0; j<n; j++)
        result[i++] = '0';
    result[i] = '\0';
    printf("padding : %s\n",result);
    return n;
}

int toDec(char *str){
    int j = 0, i, n = 0;
    for(i=strlen(str)-1; i>=0; i--){
        int r = (str[i] - '0') * pow(2, j++);
        n += r;
    }
    printf("%s => %d\n",str, n);
    return n;
}

void reverse(char *str){
    int n = strlen(str);
    char ch;
    for(int i = 0; i<n/2; i++){
        ch = str[n-i-1];
        str[n-i-1] = str[i];
        str[i] = ch;
    }
}

void toBin(int n, char *str){
    int i = 0;
    while(n != 0){
        if(n & 1)
            str[i++] = '1';
        else 
            str[i++] = '0';
        n = n >> 1;
    }
    reverse(str);
}

void crc(char *data, char *divisor, char *result){
    padding(data, divisor, result);

    int dvsr_len = strlen(divisor);
    int end = dvsr_len;
    char dvnd[end];

    for(int i=0; i<end; i++)
        dvnd[i] = result[i];
    dvnd[end] = '\0';

    int num = toDec(dvnd);
    int d = toDec(divisor);
    int res = 0, frst;

    while(end <= strlen(result)){
        frst = num;

        frst = frst >> (dvsr_len - 1);
        if(frst == 1)
            res = num ^ d;
        else 
            res = num ^ 0;

        if(end == strlen(result))
            break;

        num = res << 1;
        num = num | (result[end] - '0');
        
        end++;
    }

    num = toDec(result) + res;
    toBin(num, result);
}

void main(){
    char data[size], divisor[size], result[2*size];

    readInput(data, "Enter the data : ");
    readInput(divisor, "Enter the divisor : ");

    crc(data, divisor, result);
    printf("result = %s\n",result);
}
