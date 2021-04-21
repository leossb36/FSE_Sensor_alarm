#include "menu.h"
#include "messageHandler.h"
#include "serverSocket.h"
#include "events.h"
#include "csv.h"
#include <curses.h>
#include <unistd.h>

char options[6][30] = { 
    "Lampada Cozinha", 
    "Lampada Sala", 
    "Lampada quarto 1", 
    "Lampada quarto 2",
    "Ar condicionado 1",
    "Ar condicionado 2"
};

char status[2][13] = { "Desconectado", "Conectado" };
char sensorState[3][32] = { "Aguardando", "Ocioso", "Detectando" };


void updateSensorPresence(int sensorIndex, int sensorState) {
    char message[200];

    sprintf(message, "%s - %d - %d", GET_GPIO_DEVICE_STATE, sensorIndex, sensorState);
    sendMessageToClient(message);
    writeOnCSVFile(GET_GPIO_DEVICE_STATE, options[sensorIndex], sensorState);
}

void *menuExecution() {
    int box_size_x, box_size_y, commands_box_size = 3, key = ERR;

    box_size_x = box_size_y = 30;

    initscr();
    noecho();
    nodelay(stdscr, TRUE);
    curs_set(FALSE);
    keypad(stdscr, TRUE);

    // set up initial windows
    getmaxyx(stdscr, box_size_y, box_size_x);

    WINDOW *data_box = newwin((box_size_y - commands_box_size) -4, (box_size_x/2)-1, 0, 0);
    WINDOW *command_box = newwin((box_size_y - commands_box_size) -4, (box_size_x/2)-1, 0, (box_size_x/2));

    box(data_box, 0, 0);
    box(command_box, 0, 0);

    while(1) {
        wrefresh(stdscr);
        wrefresh(data_box);
        wrefresh(command_box);

        for(int i = 0; i < 6; i++) {
            if (sensors[i])
                wattron(command_box, A_REVERSE);
            mvwprintw(command_box, i + 1, 2, "[%d] - %s", i + 1, options[i]);
            wattroff(command_box, A_REVERSE);
        }

        key = getch();

        switch (key) {
            case '1':
                updateSensorPresence(0, 1 - sensors[0]);
                break;
            case '2':
                updateSensorPresence(1, 1 - sensors[1]);
                break;
            case '3':
                updateSensorPresence(2, 1 - sensors[2]);
                break;
            case '4':
                updateSensorPresence(3, 1 - sensors[3]);
                break;
            case '5':
                updateSensorPresence(4, 1 - sensors[4]);
                break;
            case '6':
                updateSensorPresence(5, 1 - sensors[5]);
                break;
            default:
                break;
        }

        mvwprintw(command_box, 0, 2, "Menu");
        mvwprintw(data_box, 0, 2, "Sensores");
        mvwprintw(data_box, 1, 2, "Servidor distribuido: ---------- %s", (!connection) ? "Desconectado" : "Conectado");
        mvwprintw(data_box, 2, 2, "Temperatura: ----------------------------- %.2f ºC", temperature);
        mvwprintw(data_box, 3, 2, "Umidade: --------------------------------- %.2f \%", humidity);
        mvwprintw(data_box, 4, 2, "Sensor de presenca Sala ------------------ %s", sensorState[sensors[0]]);
        mvwprintw(data_box, 5, 2, "Sensor de presenca Cozinha --------------- %s", sensorState[sensors[1]]);
        mvwprintw(data_box, 6, 2, "Sensor de abertura porta Cozinha --------- %s", sensorState[sensors[2]]);
        mvwprintw(data_box, 7, 2, "Sensor de abertura janela Cozinha -------- %s", sensorState[sensors[3]]);
        mvwprintw(data_box, 8, 2, "Sensor de abertura porta Sala ------------ %s", sensorState[sensors[4]]);
        mvwprintw(data_box, 9, 2, "Sensor de abertura janela Sala ----------- %s", sensorState[sensors[5]]);
        mvwprintw(data_box, 10, 2, "Sensor de abertura janela quarto 1 ------- %s", sensorState[sensors[6]]);
        mvwprintw(data_box, 11, 2, "Sensor de abertura janela quarto 2 ------- %s", sensorState[sensors[7]]);
    }
}