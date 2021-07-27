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
    char *inp;
    char *op;
    int i, counter = 0;
    inp = (char *)malloc(LIMIT * sizeof(char));
    printf("Enter the binary data: ");
    fgets(inp, LIMIT, stdin);
    int point = 0;
    int length = strlen(inp);
    op = (char *)malloc((length + 2) * sizeof(char));
    printf("Enter the binary data with the parity bit: ");
    fgets(op, LIMIT, stdin);
    msg = (char *)malloc(LIMIT * sizeof(char));
    /*while (inp[point] != '\n')
    {
        op[point] = inp[point];
        if (inp[point] == '1')
            counter++;
        point++;
    }
    if (counter % 2 == 0)
        op[point++] = '0';
    else
        op[point++] = '1';*/
    send(s, inp, strlen(inp), 0);
    send(s, op, strlen(op), 0);
    receive_size = recv(s, msg, LIMIT, 0);
    msg[receive_size] = '\0';
    puts(msg);
    shutdown(s, SD_BOTH);
    closesocket(s);
    WSACleanup();
}