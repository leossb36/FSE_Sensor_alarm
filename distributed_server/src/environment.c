#include "bme280.h"
#include "events.h"
#include "clientSocket.h"
#include "csv.h"
#include <stdio.h>
#define ADRESS_SENSOR 0x76

int temperature, pressure, humidity;

void initBme() {
    int response = 0;
    response = bme280Init(ADRESS_SENSOR);
    if (response < 0)
        printf("Error: Cannot start i2c device!\n");
}

void handlerEnvData() {
    char message[250];
    float *temp, *hum;

    bme280ReadValues(&temperature, &pressure, &humidity);

    *temp = temperature/100;
    *hum = humidity/836;

    sprintf(message, "%s - %.2f - %.2f", UPDATE_TEMP, *temp, *hum);

    writeOnCSVFile(*temp, *hum);
    sendMessageClient(message);
}