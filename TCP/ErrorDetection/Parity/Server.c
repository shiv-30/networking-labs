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
    int c, receive_size1, receive_size2;
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
        char *inp, *prt;
        int counter = 0;
        inp = (char *)calloc(LIMIT, sizeof(char));
        prt = (char *)calloc(LIMIT, sizeof(char));
        receive_size1 = recv(temp_sock, inp, LIMIT, 0);
        receive_size2 = recv(temp_sock, prt, LIMIT, 0);
        inp[receive_size1 - 1] = '\0';
        prt[receive_size2 - 1] = '\0';
        int point = 0;
        while (inp[point] != '\0')
        {
            if (inp[point] == '1')
                counter++;
            point++;
        }
        if (counter % 2 == (prt[point] - '0'))
        {
            msg = "EVEN PARITY: OK";
            send(temp_sock, msg, strlen(msg), 0);
        }
        else
        {
            msg = "EVEN PARITY: NOT OK";
            send(temp_sock, msg, strlen(msg), 0);
        }
        closesocket(temp_sock);
    }
}
