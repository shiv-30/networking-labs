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
    int c, message_length;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    {
        printf("[CLIENT] Failed. Error Code : %d\n", WSAGetLastError());
        return 1;
    }
    if ((s = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET)
    {
        printf("[CLIENT] Could not create socket : %d\n", WSAGetLastError());
        return 1;
    }
    printf("[CLIENT] All checks passed, Socket created.\n");
    server.sin_addr.s_addr = inet_addr("192.168.0.2");
    server.sin_family = AF_INET;
    server.sin_port = htons(atoi(argv[1]));
    printf("[CLIENT] Connected... awaiting message\n");

    msg = "HelloWorld";
    message_length = strlen(msg);
    c = sizeof(struct sockaddr_in);
    if (sendto(s, msg, message_length, 0, (struct sockaddr *)&server, c) == SOCKET_ERROR)
    {
        printf("sendto() failed with error code : %d", WSAGetLastError());
        return 1;
    }
    free(msg);
    // just freeing the message space and allocating new space as memset was causing troubles.

    msg = (char *)calloc(LIMIT, sizeof(char));

    if ((message_length = recvfrom(s, msg, LIMIT, 0, (struct sockaddr *)&server, &c)) == SOCKET_ERROR)
    {
        printf("recvfrom() failed with error code : %d", WSAGetLastError());
        return 1;
    }
    shutdown(s, SD_BOTH);
    closesocket(s);
    //Add a NULL terminating character to make it a proper string before printing
    msg[message_length] = '\0';
    puts(msg);

    if (WSACleanup() == SOCKET_ERROR)
    {
        printf("Error in Windows Sockets DLL Cleanup!");
        return 1;
    }
    return 0;
}
