#include <stdio.h>
#include <winsock2.h>
#define LIMIT 1024

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
    char *msg;
    WSADATA wsa;
    SOCKET s;
    struct sockaddr_in server;
    int c, rsize;
    char servermsg[LIMIT];
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    {
        printf("[CLIENT] Failed. Error Code : %d\n", WSAGetLastError());
        return 1;
    }
    if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
    {
        printf("[CLIENT] Could not create socket : %d\n", WSAGetLastError());
        return 1;
    }
    printf("[CLIENT] All checks passed, Socket created.\n");
    server.sin_addr.s_addr = inet_addr("192.168.0.2");
    server.sin_family = AF_INET;
    server.sin_port = htons(atoi(argv[1]));
    if (connect(s, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR)
    {
        printf("[CLIENT] Connection failed with error code : %d\n", WSAGetLastError());
        return 1;
    }
    printf("[CLIENT] Connected... awaiting message\n");
    if ((rsize = recv(s, servermsg, LIMIT, 0)) == SOCKET_ERROR)
    {
        printf("[CLIENT] Receiving failed with error code : %d\n", WSAGetLastError());
        return 1;
    }

    puts("[CLIENT] Reply received\n");
    shutdown(s, SD_BOTH);
    closesocket(s);
    //Add a NULL terminating character to make it a proper string before printing
    servermsg[rsize] = '\0';
    puts(servermsg);

    if (WSACleanup() == SOCKET_ERROR)
    {
        printf("Error in Windows Sockets DLL Cleanup!");
        return 1;
    }
    return 0;
}
