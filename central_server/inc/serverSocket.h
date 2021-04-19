#ifndef SERVER_SOCKET_H
#define SERVER_SOCKET_H

void initSocketServer();
void createServerSocket();
void bindServerPort();
void handlerMessageReceived();
void *connectClient();
void sendMessageToClient(char *message);

#endif