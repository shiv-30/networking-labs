#include <stdio.h>
#include <winsock2.h>
#include <string.h>
#include <time.h>

#define LIMIT 100

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("PORT NOT SPECIFIED\n");
        return 1;
    }
    char *msg;                                //will just store a string.
    WSADATA wsa;                              // A datastructure that stores the Windows Socket Implementation
    SOCKET s, temp_sock;                      // Oh well, sockets....
    struct sockaddr_in server, client, empty; // Will store addresses
    int c, receive_size;
    WSAStartup(MAKEWORD(2, 2), &wsa);
    s = socket(AF_INET, SOCK_STREAM, 0);
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_family = AF_INET;
    server.sin_port = htons(atoi(argv[1]));
    bind(s, (struct sockaddr *)&server, sizeof(server));
    printf("Listening to port: %s\n", argv[1]);
    listen(s, 5);
    c = sizeof(struct sockaddr_in);
    while (1)
    {
        temp_sock = accept(s, (struct sockaddr *)&client, &c);
        time_t t;        // time_t is time data type.
        time(&t);        // gives the current time
        msg = ctime(&t); // puts the time in a readable format in a string
        send(temp_sock, msg, strlen(msg), 0);
        closesocket(temp_sock);
    }
}
