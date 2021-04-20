#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include "events.h"
#include "messageHandler.h"

#define PORT 10006
#define SERVER_IP_ADRESS "192.168.0.53"
#define MAX_SIZE 200

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
    char message[MAX_SIZE];
	while (1) {
		bzero(message, MAX_SIZE);
		if((recv(clientSocket, message, MAX_SIZE, 0)) < 0) {
			printf("Error: Cannot read message sent to client!\n");
		}
		else if (message[0] == '\0')
            printf("Error: Cannot read message sent to client!\n");
		else
			printf("Client: Received message %s\n", message);
            eventMessageHandler(message);

        usleep(100000);
    }
    return 0;
}

void sendMessageClient(char *message) {
    if (clientSocket < 0) {
        printf("Erro: Cannot send message!\n");
    }
    else {
        int sendMessage = 0;
        int unsigned sizeMessage = strlen(message);

        sendMessage = send(clientSocket, message, sizeMessage, 0);
        if (!sendMessage)
            printf("Erro: Cannot send message to socket!\n");
    }
}