#include <stdio.h>
#include <winsock2.h>
#include <string.h>

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
    s = socket(AF_INET, SOCK_DGRAM, 0);
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_family = AF_INET;
    server.sin_port = htons(atoi(argv[1]));
    bind(s, (struct sockaddr *)&server, sizeof(server));
    printf("Listening to port: %s\n", argv[1]);
    printf("Enter \'q\' to exit chat\n================\n");
    while (1)
    {
        c = sizeof(struct sockaddr_in);
        msg = (char *)calloc(LIMIT, sizeof(char));
        receive_size = recvfrom(s, msg, LIMIT, 0, (struct sockaddr *)&client, &c);
        msg[receive_size] = '\0';
        if (msg[0] == 'q' && msg[1] == '\n')
        { // This means client is quitting early.
            printf("CLIENT[%s:%d] has left the chat\n", inet_ntoa(client.sin_addr), client.sin_port);
            closesocket(s);
            break;
        }
        printf("CLIENT[%s:%d]: %s\n", inet_ntoa(client.sin_addr), client.sin_port, msg);
        free(msg);
        msg = (char *)calloc(LIMIT, sizeof(char));
        printf("Enter your message to [%s:%d]:", inet_ntoa(client.sin_addr), client.sin_port);
        fgets(msg, LIMIT, stdin);
        c = sizeof(client);
        if (msg[0] == 'q' && msg[1] == '\n')
        { // This means that SERVER is quitting early.
            printf("Closing chat\n");
            sendto(s, msg, strlen(msg), 0, (struct sockaddr *)&client, c);
            closesocket(s);
            break;
        }
        sendto(s, msg, strlen(msg), 0, (struct sockaddr *)&client, c);
    }
    closesocket(s);
    shutdown(s, SD_BOTH);
    WSACleanup();
}
