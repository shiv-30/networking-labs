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
    char *msg;                         //will just store a string.
    WSADATA wsa;                       // A datastructure that stores the Windows Socket Implementation
    SOCKET s, temp_sock;               // Oh well, sockets....
    struct sockaddr_in server, client; // Will store addresses
    int c;                             // stores size later on in the code

    // WSAStartup(word version, wsadata datastructure)
    // Returns 0 when ran successfully, otherwise error.
    // Last errors in WSA can be seen using WSAGetLastError()
    // MAKEWORD(2,2) is a system call that will create a word with 2 as it's higher integer and 2 as it's lower integer too
    // Basically, MAKEWORD(2,2) specifies version 2.2
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) // Need to start up WSA before working with it.
    {
        printf("[SERVER] Failed. Error Code : %d\n", WSAGetLastError());
        return 1;
    }
    // Once WSA is up, We can create the sockets.
    // INVALID_SOCKET is a field, defined in Winsock2.h
    // We can use this to check for invalid sockets.
    // SOCK_STREAM means TCP connection.
    // socket(int AddressFamily, int type, int protocol)
    // we use 0 as protocol, as we do not wish to specify a protocol
    if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
    {
        printf("[SERVER] Could not create socket : %d\n", WSAGetLastError());
        return 1;
    }
    // Proceeding to assign address to a sockaddr_in datastructure for the server side.
    server.sin_addr.s_addr = INADDR_ANY;
    // INADDR_ANY basicall means it'll work on all available addresses, i.e. localhost, LAN assigned IP, all will work
    server.sin_family = AF_INET;
    // AF_INET = IPv4 address family.
    server.sin_port = htons(atoi(argv[1]));
    // htons is defined in winsock2.h
    // htons converts a host byte order to a network byte order.
    // the atoi returns a number from the argv[1] string.
    // the htons converts that number to the network byte order for the sockaddr_in
    // Now, we bind the socket to the address.
    // Why do we do this?
    // Well, if we do not bind, the server will have a port, but the port will change everytime we run the code...
    // Now, since this is a server, we do not want a changing port, instead, we want a fixed port to listen to..
    // this is why we bind the server to this port to fix it at this port only.
    if (bind(s, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR)
    {
        // again, SOCKET_ERROR is defined in winsock2.h
        // it can be used to check for socket errors
        printf("[SERVER] Bind failed with error code : %d\n", WSAGetLastError());
        return 1;
    }
    printf("[SERVER] All checks passed, Socket created and bound.\n");
    // now, we will listen to the server...
    // listen(socket, number of connections)
    listen(s, 2);
    printf("[SERVER] Ready for connections.\n");
    while (1)
    {
        c = sizeof(struct sockaddr_in);
        // c will be the int to store the size of the client address datastrucutre.
        temp_sock = accept(s, (struct sockaddr *)&client, &c);
        // since this is a TCP based client, it needs to accept a connection before working with it.
        // accepting does that handshake and creates a communication channel between the client and the server.
        // accept(socket server, sockaddr clientaddress, int placeToStoreClientAddressDataSize)

        // From this point onwards, temp_sock will be the socket connected between the client and the server... not s

        if (temp_sock == INVALID_SOCKET)
        {
            // error handling
            printf("[SERVER] Accept failed with error code : %d\n", WSAGetLastError());
            continue;
        }

        printf("[SERVER] Connection accepted from Client [%s:%d]\n", inet_ntoa(client.sin_addr), client.sin_port);
        // inet_ntoa just converts a address of the structure in_addr to normal string
        // just to display which client we got connection from.
        //Reply to client
        msg = "Welcome to BetterNetworkThanYourISP";
        send(temp_sock, msg, strlen(msg), 0);
        // Just sending a message to the client...
        // closing the temp_sock socket, as it has served it's purpose.
        shutdown(temp_sock, SD_BOTH);
        closesocket(temp_sock);
    }
    // Once we're done with the server socket, we shut this down too.
    // Since the above part is a infinite loop, the execution doesn't reach here
    // but it's always a good practice to shutdown and close a socket after use
    // as that releases the resources locked by the socket.
    shutdown(s, SD_BOTH);
    closesocket(s);
    if (WSACleanup() == SOCKET_ERROR)
    {
        // WSACleanup will cleanup WSA, and close any sockets if the remain open by chance.
        printf("Error in Windows Sockets DLL Cleanup!");
        return 1;
    }
    return 0;
}
