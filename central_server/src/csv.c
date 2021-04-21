#include <stdio.h>
#include <time.h>
#include <unistd.h>
#define CSV_FILE "socket_handler.csv"


void createCSVFile() {
    FILE *file = fopen(CSV_FILE, "r");

    if(file == NULL) {
        file = fopen(CSV_FILE, "w");
        fprintf(file, "Timestamp; Evento; Payload\n");
    }
    fclose(file);
    sleep(1);
}

void writeOnCSVFile(char *event, char *name, int state) {
    FILE *file = fopen(CSV_FILE, "a");

    char timestamp[50];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(timestamp,"%02d-%02d-%d %02d:%02d:%02d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec);
    fprintf(file, "%s;%s;%s;%d\n", timestamp, event, name, state);

    fclose(file);
}