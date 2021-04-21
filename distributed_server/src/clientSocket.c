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

int sock;
struct sockaddr_in serverAdress;
char *clientServerIp;
unsigned short clientServerPort;

void initSocketClient() {
    clientServerIp = SERVER_IP_ADRESS;
    clientServerPort = PORT;

    sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock < 0)
        printf("Erro: Cannot open client socket!\n");

    memset(&serverAdress, 0, sizeof(serverAdress)); // Zerando a estrutura de dados
    serverAdress.sin_family = AF_INET;
    serverAdress.sin_addr.s_addr = inet_addr(clientServerIp);
    serverAdress.sin_port = htons(clientServerPort);

    if (connect(sock, (struct sockaddr *)&serverAdress, sizeof(serverAdress)) < 0) {
        printf("Erro: Cannot connect client socket!\n");
        exit(0);
    }
}

void *clientSocketThread() {
    char message[MAX_SIZE];
	while (1) {
		bzero(message, sizeof(message));

        if((recv(sock, message, sizeof(message), 0)) < 0) {
			printf("Error: Cannot read message sent to client!\n");
		}
		else if (message[0] == '\0')
            printf("Error: the message is empty!\n");

		else {
			printf("Client: Received message %s\n", message);
            eventMessageHandler(message);
        }
        usleep(100000);
    }
}

void sendMessageToServer(char *message) {
    if (sock < 0) {
        printf("Erro: Cannot send message!\n");
    }
    else {
        int response = send(sock, message, strlen(message), 0);
        if (!response)
            printf("Error: Cannot send message to server!\n");
    }
}

void closeClientSocket() {
    close(sock);
}