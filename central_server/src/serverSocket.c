#include <stdio.h>
#include <sys/socket.h>
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

void sendMessageToClient() {
	char buffer[16];
	int receivedBytes;

	if((receivedBytes = recv(clientSocket, buffer, 16, 0)) < 0)
		printf("Error: Cannot read received bytes\n");

	while (receivedBytes > 0) {
		if(send(clientSocket, buffer, receivedBytes, 0) != receivedBytes)
			printf("Error: Cannot send message to client!\n");
		
		if((receivedBytes = recv(clientSocket, buffer, 16, 0)) < 0)
			printf("Error: Cannot read message sent to client!\n");
	}
}

int initSocketServer() {
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
		return 0;
	}
	else {
        return 1;
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

void connectClient() {
	clientConnect = sizeof(clientAdress);
	clientSocket = accept(_serverSocket,(struct sockaddr *) &clientAdress, &clientConnect);
	if(clientSocket < 0)
		printf("Error: Cannot connect with Client!\n");

	printf("Success: Client enabled - %s\n", inet_ntoa(clientAdress.sin_addr));
}

void connectWithClientServer() {
	while(1) {
		connectClient();
		sendMessageToClient();
		close(clientSocket);
	}
}