#include <stdio.h>
#include <winsock2.h>
#include <string.h>
#define LIMIT 100

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

    // MOST OF THE STUFF HERE IS SAME AS THE TCP, UNLESS SPECIFIED.
    char *msg;
    WSADATA wsa;
    SOCKET s;
    struct sockaddr_in server, client;
    int c, message_length;

    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    {
        printf("[SERVER] Failed. Error Code : %d\n", WSAGetLastError());
        return 1;
    }
    // Now, we use SOCK_DGRAM here as we are making UDP connection
    if ((s = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET)
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
    printf("[SERVER] Ready for connections.\n");
    // now, after bind, we do not listen in this one. as this is NOT a connection based socket.
    while (1)
    {

        c = sizeof(struct sockaddr_in);
        // c will have the size of the client address datastructure
        msg = (char *)calloc(LIMIT, sizeof(char));
        /// allocating fresh memory for the message
        // recvfrom is used to receive messages in non-connection based sockets.
        // recvfrom(socket server, char* bufferToStoreMessage, int lengthOfMessage,int flags, sockaddr whereClientDetailsWillBeStored, int sizeOfClientDataStruct)
        if ((message_length = recvfrom(s, msg, LIMIT, 0, (struct sockaddr *)&client, &c)) == SOCKET_ERROR)
        {
            printf("recvfrom() failed with error code : %d", WSAGetLastError());
            return 1;
        }

        printf("Received packet from %s:%d\n", inet_ntoa(client.sin_addr), client.sin_port);
        printf("Data: %s\n", msg);

        memset(msg, '\0', LIMIT);
        msg = "WELCOME TO UDP NEtwrks";
        message_length = strlen(msg);
        // now, we send something back to the client, because..
        // khali haate ferate nei
        // we used the sendto() function to send data in a udp based connection.
        // sendto(Socket server, char* bufferOfMessage, int MessageLength, int flags, sockaddr AddressOfClientToWhomWeAreSending, int sizeOfTheClientAddressDataStruct)
        if (sendto(s, msg, message_length, 0, (struct sockaddr *)&client, c) == SOCKET_ERROR)
        {
            printf("sendto() failed with error code : %d", WSAGetLastError());
            return 1;
        }
        free(msg);
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
