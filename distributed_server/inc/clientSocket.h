#ifndef CLIENT_SOCKET_H_
#define CLIENT_SOCKET_H_

void *clientSocketThread();
void sendMessageClient(char *message);
void readMessageClient(char *message);
void initSocketClient();

#endif