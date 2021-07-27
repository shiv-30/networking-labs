#include <stdio.h>
#include <winsock2.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc < 2) //argv < 2 means no parameter
    {
        //The following 10 lines (line 13 to line 22) are used just to extract the
        // Executable file name, because on Windows, you otherwise get the full path too.
        char *name = argv[0]; //argv[0] has the file name along with the path.
        int idx = 0;          //idx will store the index of the
        char *newName;        //newName will store ONLY the executable name;
        for (int i = 0; i < strlen(name); i++)
            if (name[i] == '\\')
                idx = i;                                               //Getting the index of the last '\'. after the last '\' we have the executable file name
        newName = (char *)malloc(sizeof(char) * (strlen(name) - idx)); //allocating memory
        for (int i = idx + 1; i < strlen(name); i++)
            newName[i - idx - 1] = name[i]; //copying ONLY the executable file name
        newName[strlen(newName)] = '\0';    //putting a null character at the end to mark string end.
        printf("ERROR: Port not specified.\nUse the following format:\n\n./%s <port number>", newName);
        free(newName);
        return 1;
        //Exiting since port number was not given.

        //This entire IF block is just to handle if no port number is specified during execution
    }
    char *msg; //will just store a string.
    WSADATA wsa; // A datastructure that stores the Windows Socket Implementation
    SOCKET s, temp_sock;    // Oh well, sockets....
    struct sockaddr_in server, client;  // Will store addresses
    int c; // No idea kano aache... can be deleted
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    {
        printf("[SERVER] Failed. Error Code : %d\n", WSAGetLastError());
        return 1;
    }
    if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
    {
        printf("[SERVER] Could not create socket : %d\n", WSAGetLastError());
        return 1;
    }
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_family = AF_INET;
    server.sin_port = htons(atoi(argv[1]));
    if (bind(s, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR)
    {
        printf("[SERVER] Bind failed with error code : %d\n", WSAGetLastError());
        return 1;
    }
    printf("[SERVER] All checks passed, Socket created and bound.\n");
    listen(s, 2);
    printf("[SERVER] Ready for connections.\n");
    while (1)
    {
        c = sizeof(struct sockaddr_in);
        temp_sock = accept(s, (struct sockaddr *)&client, &c);
        if (temp_sock == INVALID_SOCKET)
        {
            printf("[SERVER] Accept failed with error code : %d\n", WSAGetLastError());
            continue;
        }

        printf("[SERVER] Connection accepted from Client [%s:%d]\n", inet_ntoa(client.sin_addr), client.sin_port);
        //Reply to client
        msg = "Welcome to BetterNetworkThanYourISP";
        send(temp_sock, msg, strlen(msg), 0);

        // getchar();
        shutdown(temp_sock, SD_BOTH);
        closesocket(temp_sock);
    }
    shutdown(s, SD_BOTH);
    closesocket(s);
    if (WSACleanup() == SOCKET_ERROR)
    {
        printf("Error in Windows Sockets DLL Cleanup!");
        return 1;
    }
    return 0;
}
