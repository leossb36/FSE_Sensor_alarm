#ifndef SERVER_SOCKET_H
#define SERVER_SOCKET_H

int initSocketServer();
void handlerMessageReceived();
void *connectClient();
void getTemperature();

#endif