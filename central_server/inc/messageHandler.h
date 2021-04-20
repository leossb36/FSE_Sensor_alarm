#ifndef _MESSAGE_HANDLER_H_
#define _MESSAGE_HANDLER_H_


extern volatile float temperature, humidity;
extern volatile int sensors[8];

void eventMessageHandler(char *message);

#endif