#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/types.h>

int main (void)
{

    char *message = "testing123";
    int bcast = 1;
    int bytes;
    int descriptor;
    struct sockaddr_in listeners;
    struct hostent *host;

    inet_pton(AF_INET, "127.0.0.1", &(listeners.sin_addr));
    listeners.sin_family = AF_INET;
    listeners.sin_port = htons(2525);

    if((descriptor = socket(AF_INET, SOCK_DGRAM, 0)) == -1){
        perror("socket failed to open.");
        exit(1);
    }

    if (setsockopt(descriptor, SOL_SOCKET, SO_BROADCAST, &bcast, sizeof(int)) == -1){
        perror("failed to set as broadcast.");
        exit(1);
    }

    if ( (bytes = sendto(descriptor, message, strlen(message), 0, (struct sockaddr *)&listeners, sizeof(listeners))) == -1 ){
        perror("failed to send");
        exit(1);
    }

    puts("reached the end...");
}
