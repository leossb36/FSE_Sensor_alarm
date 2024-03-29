#include <stdio.h>
#include <time.h>
#include <unistd.h>
#define CSV_FILE "handler_events.csv"


void createCSVFile() {
    FILE *file = fopen(CSV_FILE, "r");

    if(file == NULL) {
        file = fopen(CSV_FILE, "w");
        fprintf(file, "temperatura; humidade\n");
    }
    fclose(file);
    sleep(1);
}

void writeOnCSVFile(float temp, float humidity) {
    FILE *file = fopen(CSV_FILE, "a");

    char timestamp[50];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(timestamp,"%02d-%02d-%d %02d:%02d:%02d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec);
    fprintf(file, "%s;%.2f;%.2f\n", timestamp, temp, humidity);

    fclose(file);
}