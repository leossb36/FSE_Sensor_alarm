#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include "events.h"

#define PORT 10006
#define SERVER_IP_ADRESS "192.168.0.53"

volatile int clientStatus = 0;

int clientSocket;
struct sockaddr_in serverAdress;
char *clientServerIp;
unsigned short clientServerPort;

void initSocketClient() {
    clientServerIp = SERVER_IP_ADRESS;
    clientServerPort = PORT;

    clientSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (clientSocket < 0)
        printf("Erro: Cannot create client socket!\n");

    memset(&serverAdress, 0, sizeof(serverAdress)); // Zerando a estrutura de dados
    serverAdress.sin_family = AF_INET;
    serverAdress.sin_addr.s_addr = inet_addr(clientServerIp);
    serverAdress.sin_port = htons(clientServerPort);

    if (connect(clientSocket, (struct sockaddr *)&serverAdress, sizeof(serverAdress)) < 0) {
        printf("Erro: Cannot connect client socket!\n");
        exit(0);
    }
}

void *clientSocketThread() {
    initSocketClient();
    return 0;
}

int validateMessageStructure(char *message) {
    char tempMessage[200], payload[200];
    char *event;

    strncpy(tempMessage, message, strlen(message) + 1);
    event = strtok(tempMessage, ":");
    strncpy(payload, tempMessage + strlen(event) + 1, strlen(tempMessage) - strlen(event));

    if (strcmp(event, EXIT_SERVER) == 0) {
        kill(getpid(), SIGINT);
        return 1;
    }
    else if(strcmp(event, UPDATE_TEMP) == 0 || strcmp(event, CHANGE_DEVICE) == 0)
        return 1;
    else {
        printf("Error: Expected event type of EVENT_HANDLER");
        return -1;
    }
}

void sendMessageClient(char *message) {
    if (clientSocket < 0) {
        printf("Erro: Cannot send message!\n");
    }
    else {
        int sendMessage = 0;
        int unsigned sizeMessage = strlen(message);
        int responseValidate = validateMessageStructure(message);

        if (responseValidate == 1)
            sendMessage = send(clientSocket, message, sizeMessage, 0);

        if (!sendMessage) {
            printf("Erro: Cannot send message to socket!\n");
        }
    }
}

void readMessageClient(char *message) {
    if (clientSocket < 0) {
        printf("Erro: Cannot read message from socket!\n");
    }
    else {
        int receivedBytes = 0;
        int totalReceivedBytes = 0;
        char buffer[16];

        while(totalReceivedBytes < strlen(message)) {
            receivedBytes = recv(clientSocket, buffer, 16-1, 0);
            if(receivedBytes <= 0)
                printf("Error: Didn't receive the total number of bytes\n");

            totalReceivedBytes += receivedBytes;
            buffer[receivedBytes] = '\0';
        }
    }
}