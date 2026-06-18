#include "server.h"

/**
 * @brief This function sends a response with a given specifications and message
 * @param sock Socket to send to
 * @param clientAddr Address to send to
 * @param addrLen Length of the address
 * @param msg Message to send
 */
static void sendResponse(int sock, struct sockaddr_in *clientAddr, socklen_t addrLen, const char *msg) {
    sendto(sock, msg, strlen(msg), 0, (struct sockaddr *)clientAddr, addrLen);
}

/**
 * @brief This function handles a client request based on its message
 */
static void handleClientRequest(int sock, struct sockaddr_in *clientAddr, socklen_t addrLen, const char *msg) {
    // ACK for now
    sendResponse(sock, clientAddr, addrLen, "ACK\n");
}

/**
 * @brief This function is the main function that handles client-server communication at the given port
 * @param port Port to start the server on
 * @returns `0` if the communication was successful
 */
int startUdpServer(int port) {
    // server config

    int serverSocket;
    struct sockaddr_in serverAddr, clientAddr;
    char buffer[1024];
    socklen_t addrLen = sizeof(clientAddr);

    serverSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (serverSocket < 0) {
        perror("Socket creation failed");
        return -1;
    }

    int opt = 1;
    setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddr.sin_port = htons(port);

    if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Bind failed");
        close(serverSocket);
        return -2;
    }

    // server is running from now on

    // main loop
    while (1) {
        memset(buffer, 0, sizeof(buffer));

        // await message from client
        ssize_t bytesReceived = recvfrom(serverSocket, buffer, sizeof(buffer) - 1, 0, (struct sockaddr *)&clientAddr, &addrLen);

        if (bytesReceived < 0) {
            perror("Receive failed");
            continue;
        }

        while (bytesReceived > 0 && (buffer[bytesReceived - 1] == '\n' || buffer[bytesReceived - 1] == '\r')) {
            buffer[--bytesReceived] = '\0';
        }

        // shutdown command
        if (strcmp(buffer, "EXIT") == 0) {
            sendResponse(serverSocket, &clientAddr, addrLen, "SERVER_SHUTDOWN_ACK\n");
            break; 
        }

        // ACK every other message for now
        handleClientRequest(serverSocket, &clientAddr, addrLen, buffer);
    }

    close(serverSocket);
    return 0;
}