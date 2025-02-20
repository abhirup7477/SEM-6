#include <stdio.h>
#include <string.h>

#define size 12

char countParity(char *str, char *parity){
   int count = 0, len = strlen(str);
   strcpy(parity, str);
   char p;
   for(int i=0; i < len; i++){
        if(str[i] == '1')
            count++;
   }
   if(count % 2){
       p = '1';
   }
   else{
       p = '0';
   }
   parity[len] = p;
   parity[len+1] = '\0';

   return p;
}

void display(char *str, char *prompt, int type){
    int len = strlen(str), i = 0;
    printf("%s",prompt);
    for(i=0; i<len-1; i++)
        printf("%c ",str[i]);
    if(type == 0)
        printf("%c\n",str[i]);
    else 
        printf("(%c)\n",str[i]);
}
