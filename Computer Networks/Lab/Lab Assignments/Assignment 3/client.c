#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>

#define size 20

void readInput(char *str, char *prompt, int n){
	printf("%s", prompt);
	fgets(str, n, stdin);
	str[strlen(str) - 1] = '\0';
}

void main(){
	char path[14] = "socket_path";
	struct sockaddr_un addr;

	int sfd = socket(AF_UNIX, SOCK_STREAM, 0);

	addr.sun_family = AF_UNIX;
	strcpy(addr.sun_path, path);
	int r = connect(sfd, (struct sockaddr *) &addr, sizeof(addr));

	if(r == -1){
		perror("Connect faliure\n");
		exit(1);
	}
	
	char data[size], divisor[size], result[2 * size];
	while(1){
		readInput(data, "Enter the data : ", size);
		readInput(divisor, "Enter the divisor : ", size);

		write(sfd, data, sizeof(data));
		write(sfd, divisor, sizeof(divisor));

		// puts(data);
		// puts(divisor);

		if(!strcmp(data, "end") || !strcmp(divisor, "end")){
			break;
		}
		
		read(sfd, result, sizeof(result));
		printf("\nData = %s\n",data);
		printf("Divisor = %s\n",divisor);
		printf("Result = %s\n",result);
		puts("");
	}
	
	puts("\nServer is terminating\n");

	close(sfd);
	unlink(path);
}
