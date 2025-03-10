#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#define MY_SOCK_PATH "/somepath"
#define LISTEN_BACKLOG 50

#define handle_error(msg) \
    do { perror(msg); exit(EXIT_FAILURE); } while (0)

int main(void)
{
    int                 sfd, r;
    struct sockaddr_un  my_addr;
   
    sfd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sfd == -1)
        handle_error("socket");

    memset(&my_addr, 0, sizeof(my_addr));
    my_addr.sun_family = AF_UNIX;
    strncpy(my_addr.sun_path, MY_SOCK_PATH,
            sizeof(my_addr.sun_path) - 1);

    r = connent(sfd, (struct sockaddr *) &my_addr,
                sizeof(my_addr));
    if (r == -1)
        handle_error("connect");

    /* Code to deal with incoming connection(s)... */

    if (close(sfd) == -1)
        handle_error("close");
}