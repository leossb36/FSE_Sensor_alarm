/*
  Control Intensity of LED using PWM on Raspberry pi
  http://www.electronicwings.com
 */

#include <wiringPi.h> /* include wiringPi library */
#include <stdio.h>
#include <softPwm.h>  /* include header file for software PWM */
#include <unistd.h>
#include <gpio.h>

void handlerDevice(int PWM_pin, int intensity){
	softPwmWrite(PWM_pin, intensity);
	usleep(10000);
}

void createDevice(int PWM_pin) {
	pinMode(PWM_pin,OUTPUT);
	softPwmCreate(PWM_pin, 1,100);
}

void initDevices() {
	createDevice(LAMPADA_COZINHA);
	createDevice(LAMPADA_SALA);
	createDevice(LAMPADA_QUARTO_01);
	createDevice(LAMPADA_QUARTO_02);
	createDevice(AR_CONDICIONADO_QUARTO_01);
	createDevice(AR_CONDICIONADO_QUARTO_02);
}