#include <stdio.h>
#include <string.h>
#include <math.h>

#define size 30

void readInput(char *str, char *prompt, int n){
    printf("%s",prompt);
    fgets(str, n, stdin);
    str[strlen(str) - 1] = '\0';
}

void hammingCode(char *str, char *result){
    int m, n, r=0, i, j, k, l, count;
    m = strlen(str);
    while(pow(2, r) < (m + r + 1))
        r++;
    // printf("r = %d\n",r);
    
    n = m + r;
    j = r - 1;
    k = 0;
    for(i=0; i<n; i++){
        if(n-i == pow(2, j)){
            result[i] = 'r';
            j--;
        }
        else 
            result[i] = str[k++];
    }
    result[i] = '\0';
    puts(result);

    k = 0;
    while(k < r){
        j = pow(2, k);
        i = n - j;
        // printf("i = n-j = %d\n",i);
        l = 1;
        count = 0;
        while(i >= 0){
            if(result[i] == '1')
                count++;
            // printf("i = %d  count = %d\n", i, count);
            if(l == j){
                i -= (j+1);
                l = 1;
            }
            else{
                i--;
                l++;
            }
        }
        if(count%2 == 1)
            result[n-j] = '1';
        else 
            result[n-j] = '0';
        printf("r[%d] = %c\n",j, result[n-j]);
        k++;
    }
    puts(result);
}

void main(){
    char str[size], result[2*size];
    while(1){
        readInput(str, "Enter the data : ", size);
        hammingCode(str, result); 
        puts("");
    }
}