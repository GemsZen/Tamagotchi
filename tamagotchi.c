#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#ifdef _WIN32
#include <conio.h>
#else
#include <sys/select.h>
#include <termios.h>
#include <stropts.h>
#include <sys/ioctl.h>

int kbhit() {
    struct timeval tv;
    fd_set fds;
    tv.tv_sec = 0;
    tv.tv_usec = 0;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds);
    select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv);
    return FD_ISSET(STDIN_FILENO, &fds);
}
#endif

typedef struct {
    char name[20];
    int happiness;
    int hunger;
    char* asciiArt;
} Tamagotchi;

void initialize(Tamagotchi* tamagotchi, const char* name) {
    strcpy(tamagotchi->name, name);
    tamagotchi->happiness = 50;
    tamagotchi->hunger = 50;

    while (!kbhit()) {
        tamagotchi->asciiArt = "    /\\_/\\\n"
                               "   ( -.- )\n"
                               "    > ^ <";
        displayTamagotchi(tamagotchi);
        usleep(90000); // Pausa por 0.5 segundos
        tamagotchi->asciiArt = "    /\\_/\\\n"
                               "   ( o.o )\n"
                               "    > ^ <";
        displayTamagotchi(tamagotchi);
        sleep(3); // Pausa por 0.5 segundos
    }
}


void clearScreen() {
    printf("\033[H\033[J"); // C�digo ANSI para limpar a tela
}


void displayTamagotchi(Tamagotchi* tamagotchi) {
    clearScreen();
    printf("Nome: %s\n", tamagotchi->name);
    printf("Fome: %d/100 - Felicidade: %d/100\n", tamagotchi->hunger, tamagotchi->happiness);
    printf("Apar�ncia:\n%s\n", tamagotchi->asciiArt);
    printf("Comandos dispon�veis:\n");
    printf("- feed: Alimentar o %s\n", tamagotchi->name);
    printf("- pet: Dar carinho ao %s\n", tamagotchi->name);
    printf("- walk: Levar o %s para passear\n", tamagotchi->name);
    printf("- exit: Deixar %s descansar\n", tamagotchi->name);
}


void feed(Tamagotchi* tamagotchi) {
    tamagotchi->hunger -= 10;
    if (tamagotchi->hunger < 0) {
        tamagotchi->hunger = 0;
    }
    time_t startTime = time(NULL);
    while (time(NULL) - startTime < 10 && !kbhit()) {
        tamagotchi->asciiArt = "    /\\_/\\\n"
                               "   ( -.- )\n"
                               "    > w <";
        displayTamagotchi(tamagotchi);
        usleep(200000); // Pausa por 0.2 segundos
        tamagotchi->asciiArt = "    /\\_/\\\n"
                               "   ( -.- )\n"
                               "    > m <";
        displayTamagotchi(tamagotchi);
        usleep(200000); // Pausa por 0.2 segundos
    }

    displayTamagotchi(tamagotchi);
}

void pet(Tamagotchi* tamagotchi) {
    tamagotchi->happiness += 10;
    if (tamagotchi->happiness > 100) {
        tamagotchi->happiness = 100;
    }
    time_t startTime = time(NULL);
    while (time(NULL) - startTime < 5 && !kbhit()) {
        tamagotchi->asciiArt = "    /\\_/\\\n"
                               "    (^?^)\n"
                               "    > v <";
        displayTamagotchi(tamagotchi);
        usleep(100000); // Pausa por 0.1 segundos
        tamagotchi->asciiArt = "    /\\_/\\\n"
                               "    (^?^)\n"
                               "    > ^ <";
        displayTamagotchi(tamagotchi);
        usleep(100000); // Pausa por 0.1 segundos
    }

    displayTamagotchi(tamagotchi);
}

void walk(Tamagotchi* tamagotchi) {
    tamagotchi->happiness += 20;
    tamagotchi->hunger += 10;
    if (tamagotchi->happiness > 100) {
        tamagotchi->happiness = 100;
    }
    if (tamagotchi->hunger > 100) {
        tamagotchi->hunger = 100;
    }
    time_t startTime = time(NULL);
    while (time(NULL) - startTime < 10 && !kbhit()) {
        tamagotchi->asciiArt = "    /\\_/\\\n"
                               "   ( u.u )\n"
                               "    > D <";
        displayTamagotchi(tamagotchi);
        usleep(300000); // Pausa por 0.3 segundos
        tamagotchi->asciiArt = "    /\\_/\\\n"
                               "   ( o.o )\n"
                               "    > O <";      
                               
        displayTamagotchi(tamagotchi);
        usleep(300000); // Pausa por 0.3 segundos
    }

    displayTamagotchi(tamagotchi);
}

int main() {
    Tamagotchi tamagotchi;
    char name[20];

    printf("Digite o nome do seu Tamagotchi: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0'; // Remove o caractere de nova linha do final

    initialize(&tamagotchi, name);

    while (true) {
        clearScreen();
        displayTamagotchi(&tamagotchi);

        char command[10];
        printf("Digite um comando: ");
        fgets(command, sizeof(command), stdin);
        command[strcspn(command, "\n")] = '\0'; // Remove o caractere de nova linha do final

        if (strcmp(command, "feed") == 0) {
            feed(&tamagotchi);
            initialize(&tamagotchi, tamagotchi.name);
        } else if (strcmp(command, "pet") == 0) {
            pet(&tamagotchi);
            initialize(&tamagotchi, tamagotchi.name);
        } else if (strcmp(command, "walk") == 0) {
            walk(&tamagotchi);
            initialize(&tamagotchi, tamagotchi.name);
        } else if (strcmp(command, "exit") == 0) {
            break;
        } else {
            printf("Comando inv�lido.\n");
        }
    }

    return 0;
}


