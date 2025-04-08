#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <signal.h>


const int BUFFER_SIZE = 32;


struct clientDetails {
	struct sockaddr_in sock_addr;
	int sockfd;
};


void handle_error(const char *msg);
void handle_signal(int sigNum);
void *readMessage(void *args);
void *writeMessage(void *args);


int main(int argc, char **argv) {
	signal(SIGINT, handle_signal);

  struct sockaddr_in my_sock_addr, other_sock_addr;
  socklen_t sock_size;
	char *myIP, *otherIP;
	int sockfd, myPort, otherPort;
	pthread_t reader, writer;
	struct clientDetails details;

	myIP = (char *)malloc(sizeof(char) * BUFFER_SIZE);
	otherIP = (char *)malloc(sizeof(char) * BUFFER_SIZE);

	printf("Enter your IP Address: ");
	scanf("%s", myIP);
	printf("Enter your port: ");
	scanf("%d", &myPort);
	printf("Enter friend's IP Address: ");
	scanf("%s", otherIP);
	printf("Enter friend's port: ");
	scanf("%d", &otherPort);

  sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  if (sockfd == -1) {
    handle_error("socket");
  }

  my_sock_addr.sin_family = AF_INET;
  my_sock_addr.sin_port = htons(myPort);
  my_sock_addr.sin_addr.s_addr = inet_addr(myIP);

  sock_size = sizeof(my_sock_addr);

	if (bind(sockfd, (struct sockaddr *)&my_sock_addr, sock_size) == -1) {
		handle_error("bind");
	}

  other_sock_addr.sin_family = AF_INET;
  other_sock_addr.sin_port = htons(otherPort);
  other_sock_addr.sin_addr.s_addr = inet_addr(otherIP);

	details.sock_addr = other_sock_addr;
	details.sockfd = sockfd;

	pthread_create(&reader, NULL, &readMessage, (void *)&details);
	pthread_create(&writer, NULL, &writeMessage, (void *)&details);

	pthread_join(reader, NULL);
	pthread_join(writer, NULL);

  if (close(sockfd) == -1) {
    handle_error("close");
  }

  printf("Terminating client...\n");

  return EXIT_SUCCESS;
}


void handle_error(const char *msg) {
  fprintf(stderr, "%s failed with error: %d", msg, errno);
  exit(EXIT_FAILURE);
}


void handle_signal(int sigNum) {
	if (sigNum == SIGINT) {
		puts("\nClient terminating");
		exit(EXIT_SUCCESS);
	}
}


void *readMessage(void *args) {
	struct clientDetails details = *((struct clientDetails *)args);
	int sockfd = details.sockfd, sock_size;
	struct sockaddr_in sock_addr = details.sock_addr;

	char *buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE);
	sock_size = sizeof(sock_addr);

	while (1) {
		if (recvfrom(sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&sock_addr, &sock_size) == -1) {
			handle_error("sendto");
		}
		printf("Data recv: %s\n", buffer);
		sleep(1);
	}

	free(buffer);

	pthread_exit(NULL);
}


void *writeMessage(void *args) {
	struct clientDetails details = *((struct clientDetails *)args);
	int sockfd = details.sockfd, sock_size;
	struct sockaddr_in sock_addr = details.sock_addr;

	char *buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE);
	sock_size = sizeof(sock_addr);

	while (1) {
		fgets(buffer, BUFFER_SIZE, stdin);

		if (sendto(sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&sock_addr, sock_size) == -1) {
			handle_error("sendto");
		}
		printf("Data sent: %s\n", buffer);

		sleep(1);
	}

	free(buffer);

	pthread_exit(NULL);
}
