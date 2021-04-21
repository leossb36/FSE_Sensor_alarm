#include <stdio.h>
#include <wiringPi.h>
#include <unistd.h>
#include <sys/time.h>
#include "gpio.h"
#include "handler.h"
#include "events.h"
#include "clientSocket.h"

int sensor_states[8] = { 0, 0, 0, 0, 0, 0, 0, 0};
int sensor_type[8] = {
    SENSOR_PRESENCA_SALA,
    SENSOR_PRESENCA_COZINHA,
    SENSOR_PORTA_COZINHA,
    SENSOR_JANELA_COZINHA,
    SENSOR_PORTA_SALA,
    SENSOR_JANELA_SALA,
    SENSOR_JANELA_QUARTO_1,
    SENSOR_JANELA_QUARTO_2,
};

static struct timeval last_changes[8];

struct timeval get_now() {
    struct timeval now;

    gettimeofday(&now, NULL);

    return now;
}

void writeMessageServer(int index, int value) {
    char message[200];
    sprintf(message, "%s - %d - %i", CHANGE_DEVICE, index, value);
}

void handlerSensor1() {
    struct timeval now = get_now();

    unsigned long diff;
    diff = (now.tv_sec + 1000000 + now.tv_usec) - (last_changes[0].tv_sec + 1000000 + last_changes[0].tv_usec);

    if (diff > IGNORE_CHANGE_BELOW_USEC) {
        if (sensor_states[0])
            printf("SENSOR_PRESENCA_SALA Falling\n");
        else
            printf("SENSOR_PRESENCA_SALA Rising\n");
        sensor_states[0] = !sensor_states[0];
        writeMessageServer(0, sensor_states[0]);
    }
    last_changes[0] = now;
}
void handlerSensor2() {
    struct timeval now = get_now();

    unsigned long diff;
    diff = (now.tv_sec + 1000000 + now.tv_usec) - (last_changes[0].tv_sec + 1000000 + last_changes[1].tv_usec);

    if (diff > IGNORE_CHANGE_BELOW_USEC) {
        if (sensor_states[1])
            printf("SENSOR_PRESENCA_COZINHA Falling\n");
        else
            printf("SENSOR_PRESENCA_COZINHA Rising\n");
        sensor_states[1] = !sensor_states[1];
        writeMessageServer(1, sensor_states[1]);
    }
    last_changes[1] = now;
}
void handlerSensor3() {
    struct timeval now = get_now();

    unsigned long diff;
    diff = (now.tv_sec + 1000000 + now.tv_usec) - (last_changes[0].tv_sec + 1000000 + last_changes[2].tv_usec);

    if (diff > IGNORE_CHANGE_BELOW_USEC) {
        if (sensor_states[2])
            printf("SENSOR_PORTA_COZINHA Falling\n");
        else
            printf("SENSOR_PORTA_COZINHA Rising\n");
        sensor_states[2] = !sensor_states[2];
        writeMessageServer(2, sensor_states[2]);
    }
    last_changes[2] = now;
}
void handlerSensor4() {
    struct timeval now = get_now();

    unsigned long diff;
    diff = (now.tv_sec + 1000000 + now.tv_usec) - (last_changes[0].tv_sec + 1000000 + last_changes[3].tv_usec);

    if (diff > IGNORE_CHANGE_BELOW_USEC) {
        if (sensor_states[3])
            printf("SENSOR_JANELA_COZINHA Falling\n");
        else
            printf("SENSOR_JANELA_COZINHA Rising\n");
        sensor_states[3] = !sensor_states[3];
        writeMessageServer(3, sensor_states[3]);
    }
    last_changes[3] = now;
}
void handlerSensor5() {
    struct timeval now = get_now();

    unsigned long diff;
    diff = (now.tv_sec + 1000000 + now.tv_usec) - (last_changes[0].tv_sec + 1000000 + last_changes[4].tv_usec);

    if (diff > IGNORE_CHANGE_BELOW_USEC) {
        if (sensor_states[4])
            printf("SENSOR_PORTA_SALA Falling\n");
        else
            printf("SENSOR_PORTA_SALA Rising\n");
        sensor_states[4] = !sensor_states[4];
        writeMessageServer(4, sensor_states[4]);
    }
    last_changes[4] = now;
}
void handlerSensor6() {
    struct timeval now = get_now();

    unsigned long diff;
    diff = (now.tv_sec + 1000000 + now.tv_usec) - (last_changes[0].tv_sec + 1000000 + last_changes[5].tv_usec);

    if (diff > IGNORE_CHANGE_BELOW_USEC) {
        if (sensor_states[5])
            printf("SENSOR_JANELA_SALA Falling\n");
        else
            printf("SENSOR_JANELA_SALA Rising\n");
        sensor_states[5] = !sensor_states[5];
        writeMessageServer(5, sensor_states[5]);
    }
    last_changes[5] = now;
}
void handlerSensor7() {
    struct timeval now = get_now();

    unsigned long diff;
    diff = (now.tv_sec + 1000000 + now.tv_usec) - (last_changes[0].tv_sec + 1000000 + last_changes[6].tv_usec);

    if (diff > IGNORE_CHANGE_BELOW_USEC) {
        if (sensor_states[6])
            printf("SENSOR_JANELA_QUARTO_1 Falling\n");
        else
            printf("SENSOR_JANELA_QUARTO_1 Rising\n");
        sensor_states[6] = !sensor_states[6];
        writeMessageServer(6, sensor_states[6]);
    }
    last_changes[6] = now;
}
void handlerSensor8() {
    struct timeval now = get_now();

    unsigned long diff;
    diff = (now.tv_sec + 1000000 + now.tv_usec) - (last_changes[0].tv_sec + 1000000 + last_changes[7].tv_usec);

    if (diff > IGNORE_CHANGE_BELOW_USEC) {
        if (sensor_states[7])
            printf("SENSOR_JANELA_QUARTO_2 Falling\n");
        else
            printf("SENSOR_JANELA_QUARTO_2 Rising\n");
        sensor_states[7] = !sensor_states[7];
        writeMessageServer(7, sensor_states[7]);
    }
    last_changes[7] = now;
}

void (*handlers[8])() = { handlerSensor1, handlerSensor2, handlerSensor3, handlerSensor4,
                            handlerSensor5, handlerSensor6, handlerSensor7, handlerSensor8 };

void *deviceHandlerThread() {
    for (int i = 0; i < 8; i++)
        pinMode(sensor_type[i], OUTPUT);

    for (int i = 0; i < 8; i++)
        gettimeofday(&last_changes[i], NULL);

    for (int i = 0; i < 8; i++)
        wiringPiISR(sensor_type[i], INT_EDGE_BOTH, handlers[i]);

    for (int i = 0; i < 8; i++)
        sensor_states[i] = digitalRead(sensor_type[i]);

    while(1) {
        sleep(1);
    }
}

void sendHandlersServer() {
    char message[200];

    for (int i = 0; i < 8; i++)
        sensor_states[i] = digitalRead(sensor_type[i]);

    sprintf(message, "%s - %d - %d - %d - %d - %d - %d - %d - %d",
            SENSOR_STATES, sensor_states[0], sensor_states[1], sensor_states[2], sensor_states[3],
            sensor_states[4], sensor_states[5], sensor_states[6], sensor_states[7]);
    sendMessageToServer(message);
}

