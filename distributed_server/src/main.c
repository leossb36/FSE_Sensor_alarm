#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <pthread.h>
#include <curses.h>
#include <unistd.h>
#include <wiringPi.h>
#include "environment.h"
#include "gpio.h"
#include "handler.h"
#include "clientSocket.h"
#include "csv.h"

pthread_t socketThread, handlerThread;

void setUp() {
    wiringPiSetup();
    initBme();
    initDevices();
    createCSVFile();
    sendHandlersServer();
}

void cancelExecution() {
    printf("Stopping client server...");
    pthread_cancel(socketThread);
    exit(0);
}

int main(int argc, char **argv) {
    signal(SIGINT, cancelExecution);

    setUp();
    pthread_create(&socketThread, NULL, &clientSocketThread, NULL);
    pthread_detach(socketThread);

    pthread_create(&handlerThread, NULL, &deviceHandlerThread, NULL);
    pthread_detach(handlerThread);

    while(1) {
        sleep(1);
    }
    return 0;
}