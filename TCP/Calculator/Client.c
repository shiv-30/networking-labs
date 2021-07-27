#include <stdio.h>
#include <winsock2.h>
#include <string.h>
#define LIMIT 100

int main(int argc, char *argv[])
{

    char *operator, * op1, *op2, *res, *input; //will just store a string.
    WSADATA wsa;                               // A datastructure that stores the Windows Socket Implementation
    SOCKET s;                                  // Oh well, sockets....
    struct sockaddr_in server, client;         // Will store addresses
    int c, receive_size, port;
    WSAStartup(MAKEWORD(2, 2), &wsa);
    s = socket(AF_INET, SOCK_STREAM, 0);
    printf("Enter the SERVER IP You want to get date time from:");
    input = (char *)calloc(16, sizeof(char));
    fgets(input, 15, stdin);
    server.sin_addr.s_addr = inet_addr(input);
    free(input);
    server.sin_family = AF_INET;
    printf("Enter the SERVER PORT You want to get date time from:");
    scanf("%d", &port);
    fflush(stdin);
    server.sin_port = htons(port);
    c = sizeof(struct sockaddr_in);
    if (connect(s, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR)
    {
        printf("ERROR Connecting to server, exiting.");
        return 1;
    }
    res = (char *)calloc(LIMIT, sizeof(char));
    operator=(char *) calloc(LIMIT, sizeof(char));
    op1 = (char *)calloc(LIMIT, sizeof(char));
    op2 = (char *)calloc(LIMIT, sizeof(char));
    printf("Enter the operator: ");
    fgets(operator, LIMIT, stdin);
    printf("Enter the first operand: ");
    fgets(op1, LIMIT, stdin);
    printf("Enter the second operand: ");
    fgets(op2, LIMIT, stdin);
    send(s, operator, 1, 0);
    send(s, op1, LIMIT, 0);
    send(s, op2, LIMIT, 0);
    receive_size = recv(s, res, LIMIT, 0);
    res[receive_size] = '\0';
    printf("Result: ");
    puts(res);
    shutdown(s, SD_BOTH);
    closesocket(s);
    WSACleanup();
}