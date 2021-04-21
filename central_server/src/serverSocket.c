#include <stdio.h>
#include <sys/socket.h>
#include "serverSocket.h"
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "messageHandler.h"

#define SERVER_IP_ADRESS "192.168.0.53"
#define SERVER_PORT 10006
#define MAX_SIZE 200

int _serverSocket;
int clientSocket;
struct sockaddr_in serverAdress;
struct sockaddr_in clientAdress;
unsigned short serverPort;
unsigned int clientSize;
char clientMessage[200];


void initSocketServer() {
	memset(clientMessage, '\0', sizeof(clientMessage));
	createServerSocket();

	serverAdress.sin_family = AF_INET;
	serverAdress.sin_addr.s_addr = inet_addr(SERVER_IP_ADRESS);
	serverAdress.sin_port = htons(SERVER_PORT);

	bindServerPort();

	if(listen(_serverSocket, 10) < 0) {
		printf("Error: Cannot listen server socket!\n");
		exit(1);
	}
}

void createServerSocket() {
    printf("Trying create socket server...\n");
    _serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    if(_serverSocket < 0) {
        printf("Error: Cannot define Socket!\n");
        _serverSocket = -1;
    }
}

void bindServerPort() {
	int bindingPort = 0;
	bindingPort = bind(_serverSocket, (struct sockaddr *)&serverAdress, sizeof(serverAdress));

	if(bindingPort < 0) {
		printf("Error: Cannot bind server port - %d\n", SERVER_PORT);
		exit(1);
	}
}

void *connectClient() {
	clientSize = sizeof(clientAdress);
	
	if(listen(_serverSocket, 10) < 0) {
		printf("Error: Cannot listen server socket!\n");
		exit(1);
	}
	
	clientSocket = accept(_serverSocket,(struct sockaddr *) &clientAdress, &clientSize);
	
	if(clientSocket < 0) {
		printf("Error: Cannot connect with Client!\n");
		exit(1);
	}

	printf("Success: Client enabled - %s\n", inet_ntoa(clientAdress.sin_addr));

	handlerMessageReceived();

	return 0;
}

void handlerMessageReceived() {
	int errorCount;
	
	while (1) {
		bzero(clientMessage, sizeof(clientMessage));

		if (errorCount > 20) break;

		if((recv(clientSocket, clientMessage, sizeof(clientMessage), 0)) < 0) {
			printf("Error: Cannot read message sent to client!\n");
			errorCount++;
		}

		else if (clientMessage[0] == '\0') errorCount++;

		else {
			printf("Server: Received message %s\n", clientMessage);
			eventMessageHandler(clientMessage);
		}
	}
	printf("Server: waiting connection with client...\n");
	connectClient();
}

void sendMessageToClient(char *message) {
	if (clientSocket < 0)
		printf("Error: Cannot send message to client!\n");
	else
		send(clientSocket, message, strlen(message), 0);
}