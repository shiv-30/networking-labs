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
    s = socket(AF_INET, SOCK_STREAM, 0);
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_family = AF_INET;
    server.sin_port = htons(atoi(argv[1]));
    bind(s, (struct sockaddr *)&server, sizeof(server));
    printf("Listening to port: %s\n", argv[1]);
    listen(s, 1);
    c = sizeof(struct sockaddr_in);
    temp_sock = accept(s, (struct sockaddr *)&client, &c);
    printf("[SERVER] Chat accepted from CLIENT [%s:%d]\n", inet_ntoa(client.sin_addr), client.sin_port);
    printf("Enter \'q\' to exit chat\n================\nEnter your message:");
    while (1)
    {
        msg = (char *)calloc(LIMIT, sizeof(char));
        fgets(msg, LIMIT, stdin);
        if (msg[0] == 'q' && msg[1] == '\n')
        { // This means that SERVER is quitting early.
            printf("Closing chat\n");
            send(temp_sock, msg, strlen(msg), 0);
            closesocket(temp_sock);
            break;
        }
        send(temp_sock, msg, strlen(msg), 0);
        free(msg);
        msg = (char *)calloc(LIMIT, sizeof(char));
        receive_size = recv(temp_sock, msg, LIMIT, 0);
        msg[receive_size] = '\0';
        if (msg[0] == 'q' && msg[1] == '\n')
        { // This means client is quitting early.
            printf("CLIENT has left the chat\n");
            closesocket(temp_sock);
            break;
        }
        printf("CLIENT: %s\n", msg);
        printf("Enter your message:");
    }
    shutdown(temp_sock, SD_BOTH);
    closesocket(temp_sock);
    closesocket(s);
    WSACleanup();
}
