#include <stdio.h>
#include <wiringPi.h>
#include <unistd.h>
#include <sys/time.h>
#include "gpio.h"
#include "handler.h"
#include "events.h"

int sensor_states[8] = { 0, 0, 0, 0, 0, 0, 0, 0};
char sensor_type[8][25] = {
    "SENSOR_PRESENCA_SALA",
    "SENSOR_PRESENCA_COZINHA",
    "SENSOR_PORTA_COZINHA",
    "SENSOR_JANELA_COZINHA",
    "SENSOR_PORTA_SALA",
    "SENSOR_JANELA_SALA",
    "SENSOR_JANELA_QUARTO_1",
    "SENSOR_JANELA_QUARTO_2",
};

static struct timeval last_changes[8];

struct timeval get_now() {
    struct timeval now;

    gettimeofday(&now, NULL);

    return now;
}

void writeMessageServer(int index, int value) {
    char message[250];
    sprintf(message, "%s - %d - %i", CHANGE_DEVICE, index, value);
}

void handlerSensor1() {
    unsigned long diff;
    struct timeval now = get_now();

    diff = (now.tv_sec + 1000000 + now.tv_usec) - (last_changes[0].tv_sec + 1000000 + last_changes[0].tv_usec);

    if (diff > IGNORE_CHANGE_BELOW_USEC) {
        if (sensor_states[0])
            printf("SENSOR_PRESENCA_SALA Falling\n");
        else
            printf("SENSOR_PRESENCA_SALA Rising\n");
        sensor_states[0] = !sensor_states[0];

    }
    last_changes[0] = now;
}

void handlerSensorDevice() {
    handlerSensorState(SENSOR_PRESENCA_SALA, sensor_type[0], sensor_states[0]);
    handlerSensorState(SENSOR_PRESENCA_COZINHA, sensor_type[1], sensor_states[1]);
    handlerSensorState(SENSOR_PORTA_COZINHA, sensor_type[2], sensor_states[2]);
    handlerSensorState(SENSOR_JANELA_COZINHA, sensor_type[3], sensor_states[3]);
    handlerSensorState(SENSOR_PORTA_SALA, sensor_type[4], sensor_states[4]);
    handlerSensorState(SENSOR_JANELA_SALA, sensor_type[5], sensor_states[5]);
    handlerSensorState(SENSOR_JANELA_QUARTO_1, sensor_type[6], sensor_states[6]);
    handlerSensorState(SENSOR_JANELA_QUARTO_2, sensor_type[7], sensor_states[7]);
}

void *deviceHandlerThread() {
    handlerSensorDevice();

    while(1) {
        sleep(1);
    }
}

