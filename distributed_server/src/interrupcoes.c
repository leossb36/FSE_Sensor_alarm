#include <stdio.h>
#include <wiringPi.h>
#include <unistd.h>

#define SENSOR_PRESENCA_SALA 6
int state = 0;

void handler_function() {
    if (state)
        printf("Sensor parando de ser detectado!");
    else
        printf("Sensor detectado!\n");

    state = !state;
}

void *init_interruption() {
    pinMode(SENSOR_PRESENCA_SALA, OUTPUT);
    wiringPiISR(SENSOR_PRESENCA_SALA, INT_EDGE_BOTH, &handler_function);
    state = digitalRead(SENSOR_PRESENCA_SALA);

    while(1) {
        sleep(1);
    }
} // ce ta certo todo mundo ta errado

