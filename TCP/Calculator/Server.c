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
    char *operator, * op1, *op2, *res;        //will just store a string.
    WSADATA wsa;                              // A datastructure that stores the Windows Socket Implementation
    SOCKET s, temp_sock;                      // Oh well, sockets....
    struct sockaddr_in server, client, empty; // Will store addresses
    int c, receive_size, result;
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
        res = (char *)calloc(LIMIT, sizeof(char));
        operator=(char *) calloc(LIMIT, sizeof(char));
        op1 = (char *)calloc(LIMIT, sizeof(char));
        op2 = (char *)calloc(LIMIT, sizeof(char));
        temp_sock = accept(s, (struct sockaddr *)&client, &c);
        recv(temp_sock, operator, 1, 0);
        recv(temp_sock, op1, LIMIT, 0);
        recv(temp_sock, op2, LIMIT, 0);
        switch (operator[0])
        {
        case '+':
            result = atoi(op1) + atoi(op2);
            break;
        case '-':
            result = atoi(op1) - atoi(op2);
            break;
        case '*':
            result = atoi(op1) * atoi(op2);
            break;
        case '/':
            result = atoi(op1) / atoi(op2);
            break;
        case '%':
            result = atoi(op1) % atoi(op2);
            break;
        }
        itoa(result, res, 10);
        send(temp_sock, res, strlen(res), 0);
        closesocket(temp_sock);
    }
}
