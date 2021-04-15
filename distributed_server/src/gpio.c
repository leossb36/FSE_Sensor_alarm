/*
  Control Intensity of LED using PWM on Raspberry pi
  http://www.electronicwings.com
 */

#include <wiringPi.h> /* include wiringPi library */
#include <stdio.h>
#include <softPwm.h>  /* include header file for software PWM */
#include <unistd.h>
#include <gpio.h>

void handle_device(int PWM_pin, int intensity){
	softPwmWrite(PWM_pin, intensity);
	usleep(10000);
}

void config_devices(int PWM_pin) {
	pinMode(PWM_pin,OUTPUT);
	softPwmCreate(PWM_pin, 1,100);
}

void init_devices() {
	config_devices(LAMPADA_COZINHA);
	config_devices(LAMPADA_SALA);
	config_devices(LAMPADA_QUARTO_01);
	config_devices(LAMPADA_QUARTO_02);
	config_devices(AR_CONDICIONADO_QUARTO_01);
	config_devices(AR_CONDICIONADO_QUARTO_02);
}