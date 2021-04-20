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

void eventMessageHandler(char *message) {
    char tempMessage[200], payload[200];
    char *event;

    bzero(payload, 200);
    bzero(tempMessage, 200);

    strncpy(tempMessage, message, strlen(message));
    event = strtok(tempMessage, ":");
    strncpy(payload, tempMessage + (strlen(event) + 1), strlen(tempMessage) - strlen(event));

    if (strcmp(event, SENSOR_STATES) == 0) {
        writeOnCSVFile(event, payload);
        updateSensorData(payload);
    }
    else if(strcmp(event, UPDATE_TEMP) == 0) {
        writeOnCSVFile(event, payload);
        updateTempNHum(payload);
    }
}