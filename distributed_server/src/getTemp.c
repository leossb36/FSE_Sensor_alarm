#include "bme280.h"
#include <stdio.h>
#define ADRESS_SENSOR 0x76

void get_temperature() {
    int temperature, pressure, humidity;

    bme280Init(ADRESS_SENSOR);
    bme280ReadValues(&temperature, &pressure, &humidity);

    // printf("TEMPERATURA: %.2f\nHUMIDADE: %.2f\n", (float)temperature/100, (float)humidity/836);
}