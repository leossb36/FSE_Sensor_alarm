#ifndef GPIO_H_
#define GPIO_H_

#define LAMPADA_COZINHA 0 // GPIO 17
#define LAMPADA_SALA 1 // GPIO 18
#define LAMPADA_QUARTO_01 2 // GPIO 27
#define LAMPADA_QUARTO_02 3 // GPIO 22
#define AR_CONDICIONADO_QUARTO_1 23 // GPIO 13
#define AR_CONDICIONADO_QUARTO_2 24 // GPIO 19

void handlerDevice(int PWM_pin, int intensity);
void handlerMessageGpio(char * payload);
void createDevice(int);

#endif