#include "events.h"
#include "environment.h"
#include <string.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int eventMessageHandler(char *message) {
    char tempMessage[200], payload[200];
    char *event;

    strncpy(tempMessage, message, strlen(message) + 1);
    event = strtok(tempMessage, ":");
    strncpy(payload, tempMessage + strlen(event) + 1, strlen(tempMessage) - strlen(event));
    if (strcmp(event, EXIT_SERVER) == 0)
        kill(getpid(), SIGINT);
    else if(strcmp(event, UPDATE_TEMP) == 0)
        handlerEnvData();
    else {
        printf("Error: Expected event type of EVENT_HANDLER\n");
    }
}