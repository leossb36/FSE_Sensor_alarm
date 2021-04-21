#ifndef CLIENT_SOCKET_H_
#define CLIENT_SOCKET_H_

void *clientSocketThread();
void sendMessageToServer(char *message);
void initSocketClient();
void closeClientSocket();

#endif