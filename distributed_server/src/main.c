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
    initSocketClient();
    wiringPiSetup();
    initBme();

    createDevice(LAMPADA_COZINHA);
	createDevice(LAMPADA_SALA);
	createDevice(LAMPADA_QUARTO_01);
	createDevice(LAMPADA_QUARTO_02);
	createDevice(AR_CONDICIONADO_QUARTO_1);
	createDevice(AR_CONDICIONADO_QUARTO_2);

    createCSVFile();
    sendHandlersServer();
}

void cancelExecution() {
    printf("\nStopping client server...\n");
    closeClientSocket();
    pthread_cancel(handlerThread);
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