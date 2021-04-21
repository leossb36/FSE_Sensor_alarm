#include "events.h"
#include <string.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

volatile float temperature, humidity;
volatile int sensors[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };

void updateTempNHum(char * payload) {
    char *event;

    event = strtok(payload, ":");
	temperature = atof(event);

	event = strtok(NULL, ":");
	humidity = atof(event);
}

void updateSensorData(char * payload) {
    char *event;
    int sensorIndex, sensorValue;

    event = strtok(payload, ":");
	sensorIndex = atoi(event);

	event = strtok(NULL, ":");
	sensorValue = atof(event);

    sensors[sensorIndex] = sensorValue;
}

void handlerMessageGpio(char * payload) {
    char *event;
	int sensorIndex, sensorState;

    event = strtok(payload, ":");
	sensorIndex = atoi(event);
    
	event = strtok(NULL, ":");
	sensorState = atoi(event);

	sensors[sensorIndex] = sensorState;
}

void eventMessageHandler(char *message) {
    char tempMessage[200], payload[200];
    char *event;

    bzero(payload, 200);
    bzero(tempMessage, 200);

    strncpy(tempMessage, message, strlen(message) + 1);
    event = strtok(tempMessage, ":");
    strncpy(payload, tempMessage + (strlen(event) + 1), strlen(tempMessage) - strlen(event));

    if (strcmp(event, SENSOR_STATES) == 0) {
        updateSensorData(payload);
    }
    if(strcmp(event, GET_GPIO_DEVICE_STATE) == 0) {
        handlerMessageGpio(payload);
    }
    if(strcmp(event, UPDATE_TEMP) == 0) {
        updateTempNHum(payload);
    }
}