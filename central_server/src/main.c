#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <pthread.h>
#include "csv.h"
#include "serverSocket.h"
#include "menu.h"
#include <curses.h>

pthread_t socketThread;

// void cancelExecution() {
// }

void setUp() {
    initSocketServer();
}

int main(int argc, char **argv) {

    // signal(SIGINT, cancelExecution);
    setUp();

    pthread_create(&socketThread, NULL, &connectClient, NULL);

    pthread_detach(socketThread);

    while(1) {
        sendMessageToClient("UPDATE_TEMP");
        sleep(1);
    }

    return 0;
}