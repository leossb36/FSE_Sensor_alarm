#include <stdio.h>
#include <sys/socket.h>
#include "serverSocket.h"
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define SERVER_IP_ADRESS "192.168.0.53"
#define SERVER_PORT "10006"

int _serverSocket;
int clientSocket;
struct sockaddr_in serverAdress;
struct sockaddr_in clientAdress;
unsigned short serverPort;
unsigned int clientConnect;


void initSocketServer() {
	serverPort = atoi(SERVER_PORT);
	createServerSocket();

	memset(&serverAdress, 0, sizeof(serverAdress));
	serverAdress.sin_family = AF_INET;
	serverAdress.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAdress.sin_port = htons(serverPort);

	bindServerPort();

	if(listen(_serverSocket, 10) < 0) {
		printf("Error: Cannot listen server socket!\n");
		close(_serverSocket);
	}
}

void createServerSocket() {
    printf("Trying create socket server...\n");
    _serverSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

    if(_serverSocket < 0) {
        printf("Erro: Cannot define Socket!\n");
        _serverSocket = -1;
    }
}

void bindServerPort() {
	int bindingPort = 0;
	bindingPort = bind(_serverSocket, (struct sockaddr *)
		&serverAdress, sizeof(serverAdress));

	if(bindingPort < 0)
		printf("Error: Cannot bind server port - %s\n", SERVER_PORT);
}

void *connectClient() {
	clientConnect = sizeof(clientAdress);
	if(listen(_serverSocket, 10) < 0) {
		printf("Error: Cannot listen server socket!\n");
		close(_serverSocket);
	}
	clientSocket = accept(_serverSocket,(struct sockaddr *) &clientAdress, &clientConnect);
	if(clientSocket < 0)
		printf("Error: Cannot connect with Client!\n");

	printf("Success: Client enabled - %s\n", inet_ntoa(clientAdress.sin_addr));

	handlerMessageReceived();

	return 0;
}

void handlerMessageReceived() {
	char message[200];
	int errorCount;
	while (1) {
		if (errorCount > 20) break;
		bzero(message, 100);
		if((recv(clientSocket, message, 16, 0)) < 0) {
			errorCount++;
			printf("Error: Cannot read message sent to client!\n");
		}
		else if (message[0] == '\0') errorCount++;

		else
			printf("Received message %s", message);
	}
	connectClient();
}

void sendMessageToClient(char *message) {
	if (clientSocket < 0)
		printf("Error: Cannot send message to client!\n");
	else
		send(clientSocket, message, strlen(message), 0);
}