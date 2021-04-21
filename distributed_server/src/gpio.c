/*
  Control Intensity of LED using PWM on Raspberry pi
  http://www.electronicwings.com
 */

#include <wiringPi.h> /* include wiringPi library */
#include <stdio.h>
#include <softPwm.h>  /* include header file for software PWM */
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "gpio.h"
#include "clientSocket.h"
#include "events.h"

int sensors[] = {
	LAMPADA_COZINHA,
	LAMPADA_SALA,
	LAMPADA_QUARTO_01,
	LAMPADA_QUARTO_02,
	AR_CONDICIONADO_QUARTO_1,
	AR_CONDICIONADO_QUARTO_2
};

void handlerDevice(int PWM_pin, int intensity){
	softPwmWrite(PWM_pin, intensity);
	usleep(10000);
}

void createDevice(int PWM_pin) {
	pinMode(PWM_pin, OUTPUT);
	softPwmCreate(PWM_pin, 1,100);
}

void handlerMessageGpio(char * message) {
    char *event;
	char messageToServer[200];
	bzero(messageToServer, sizeof(messageToServer));

	int sensorIndex, sensorState;

    event = strtok(message, ":");
	sensorIndex = atoi(event);

	event = strtok(NULL, ":");
	sensorState = atoi(event);

	handlerDevice(sensors[sensorIndex], sensorState * 100);

	sprintf(messageToServer, "%s - %d - %d", GET_GPIO_DEVICE_STATE, sensorIndex, sensorState);
	sendMessageToServer(messageToServer);
}