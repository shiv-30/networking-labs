#include <stdio.h>
#include <winsock2.h>
#include <string.h>
#define LIMIT 100

int main(int argc, char *argv[])
{

    char *msg, *input;                 //will just store a string.
    WSADATA wsa;                       // A datastructure that stores the Windows Socket Implementation
    SOCKET s;                          // Oh well, sockets....
    struct sockaddr_in server, client; // Will store addresses
    int c, receive_size, port;
    WSAStartup(MAKEWORD(2, 2), &wsa);
    s = socket(AF_INET, SOCK_DGRAM, 0);
    printf("Enter the SERVER IP You want to chat to:");
    input = (char *)calloc(16, sizeof(char));
    fgets(input, 15, stdin);
    server.sin_addr.s_addr = inet_addr(input);
    free(input);
    server.sin_family = AF_INET;
    printf("Enter the SERVER PORT You want to chat to:");
    scanf("%d", &port);
    fflush(stdin);
    server.sin_port = htons(port);
    printf("[CLIENT] Chat started with SERVER [%s:%d]\n", inet_ntoa(server.sin_addr), server.sin_port);
    printf("Enter \'q\' to exit chat\n================\nEnter your message:");
    while (1)
    {
        c = sizeof(server);
        msg = (char *)calloc(LIMIT, sizeof(char));
        fgets(msg, LIMIT, stdin);
        if (msg[0] == 'q' && msg[1] == '\n')
        { // This means that client is quitting early.
            printf("Closing chat");
            sendto(s, msg, strlen(msg), 0, (struct sockaddr *)&server, c);
            closesocket(s);
            break;
        }
        sendto(s, msg, strlen(msg), 0, (struct sockaddr *)&server, c);
        free(msg);
        msg = (char *)calloc(LIMIT, sizeof(char));
        c = sizeof(struct sockaddr_in);
        receive_size = recvfrom(s, msg, LIMIT, 0, (struct sockaddr *)&server, &c);
        msg[receive_size] = '\0';
        if (msg[0] == 'q' && msg[1] == '\n')
        { // This means server is quitting early.
            printf("SERVER[%s:%d] has left the chat\n", inet_ntoa(server.sin_addr), server.sin_port);
            closesocket(s);
            break;
        }
        printf("SERVER[%s:%d]: %s\n", inet_ntoa(server.sin_addr), server.sin_port, msg);
        printf("Enter your message to [%s:%d]:", inet_ntoa(server.sin_addr), server.sin_port);
    }
    shutdown(s, SD_BOTH);
    closesocket(s);
    WSACleanup();
}