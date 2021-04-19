#include "bme280.h"
#include <stdio.h>
#define ADRESS_SENSOR 0x76

int temperature, pressure, humidity;

int getEnvironmentData() {
    int response = 0;
    response = bme280Init(ADRESS_SENSOR);
    if (response < 0) {
        printf("Error: Cannot start i2c device!\n");
        return -1;
    }

    response = 0;
    response = bme280ReadValues(&temperature, &pressure, &humidity);
    if (response < 0) {
        printf("Error: Cannot read values!\n");
        return -1;
    }

    return 1;
}

void handlerEnvData() {
    float temp, hum;

    int response = 0;
    response = getEnvironmentData();
    if (response < 0) {
        printf("Error: Cannot update Temperature & humidity!\n");
    }
    else {
        temp = temperature/100;
        hum = humidity/836;

        printf("T: %.2f - H: %.2f\n", temp, hum);
    }
}