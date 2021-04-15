#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <pthread.h>
#include <curses.h>
#include <unistd.h>
#include <wiringPi.h>
#include "getTemp.h"
#include "gpio.h"
#include "interrupcoes.h"

pthread_t tid;

void setUp() {
    wiringPiSetup();
    init_devices();
}

int main(int argc, char **argv) {
    setUp();

    handle_device(LAMPADA_COZINHA, 1);
    // signal(SIGINT, cancelProcess);

    pthread_create(&tid, NULL, &init_interruption, NULL);

    pthread_detach(tid);

    while(1) {
        sleep(1);
    }

    return 0;
}