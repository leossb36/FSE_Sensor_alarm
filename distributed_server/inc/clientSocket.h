#ifndef CLIENT_SOCKET_H
#define CLIENT_SOCKET_H

void *clientSocketThread();
void sendMessageClient(char *message);
void readMessageClient(char *message);

#endif