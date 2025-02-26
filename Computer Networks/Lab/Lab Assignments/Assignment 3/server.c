#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <sys/socket.h>
#include <sys/un.h>

#define size 20

int addRedundantBits(char *data, char *divisor,  char *result){
	int n = strlen(divisor) - 1;
	strcpy(result, data);
	int j = strlen(data);
	for(int i=1; i<=n; i++){
		result[j++] = '0';
	}
	result[j] = '\0';
	return n;
}

int convert_decimal(char *str){
	int n = 0;
	int i, len = strlen(str), j=0;
	for(i=len-1; i>=0; i--){
		int r = (str[i] - '0') * pow(2, j++);
		n += r;
	}
	return n;
}

void reverse(char *str){
	int len = strlen(str);
	for(int i=0; i<len/2; i++){
		char temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
	}
}

void convert_binary(int n, char *str){
    int x = n;
	int i = 0;
	while(n != 0){
		int r = n % 2;
		str[i++] = r + '0';
		n /= 2;
	}
	str[i] = '\0';
	reverse(str);
}

void crc(char *data, char *divisor, char *result){
	int r = addRedundantBits(data, divisor, result);
    
    int divisor_len = strlen(divisor), i;
    char dvnd[divisor_len+1], dvsr[divisor_len+1], rmndr[divisor_len];
    int end = divisor_len, result_len = strlen(result);

    for(i=0; i<end; i++){
        dvnd[i] = result[i];
    }
    dvnd[end] = '\0';
    
    int num = convert_decimal(dvnd);
    int d = convert_decimal(divisor);
    int res, frst;
    char str1[100], str2[100], str3[100];
    while(end <= result_len){
        frst = num;
        
        frst = log2(frst) + 1;
        if(frst == divisor_len)
            res = num ^ d;
        else 
            res = num ^ 0;

        num = res;
        res = res << 1;

        if(end != result_len)
            num = res | (result[end] - '0');

        convert_binary(num, str1);
        convert_binary(res, str3);

        end++;
    }
    res = convert_decimal(result);
    res += num;
    convert_binary(res, result);
    puts(result);
}

void main(){
	char path[14] = "socket_path";
	struct sockaddr_un addr, client_addr;
	int client_addr_len;
	unlink(path);

	int sfd = socket(AF_UNIX, SOCK_STREAM, 0);

	addr.sun_family = AF_UNIX;
	strcpy(addr.sun_path, path);
	bind(sfd, (struct sockaddr *) &addr, sizeof(addr));
	listen(sfd, 10);

	client_addr_len = sizeof(client_addr);
	int cfd = accept(sfd, (struct sockaddr *) &client_addr, &client_addr_len);
	if(cfd == -1){
		perror("Accept faliure\n");
		exit(1);
	}
	
	char data[size], divisor[size], result[2 * size];
	while(1){
		puts("Server is waiting");

		read(cfd, data, sizeof(data));
		read(cfd, divisor, sizeof(divisor));

		if(!strcmp(data, "end") || !strcmp(divisor, "end")){
			break;
		}

		crc(data, divisor, result);
		printf("\nDividend = %s\n",data);
		printf("Divisor = %s\n",divisor);
		printf("Result = %s\n",result);
		write(cfd, result, sizeof(result));
		puts("");
	}
	
	puts("\nerver is terminating\n");

	close(cfd);
	unlink(path);
}
