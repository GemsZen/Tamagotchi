#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct {
    char name[20];
    int happiness;
    int hunger;
} Tamagotchi;

void initialize(Tamagotchi* tamagotchi, const char* name) {
    strcpy(tamagotchi->name, name);
    tamagotchi->happiness = 50;
    tamagotchi->hunger = 50;
}

void feed(Tamagotchi* tamagotchi) {
    tamagotchi->hunger -= 10;
    if (tamagotchi->hunger < 0) {
        tamagotchi->hunger = 0;
    }
    printf("%s foi alimentado!\n", tamagotchi->name);
}

void pet(Tamagotchi* tamagotchi) {
    tamagotchi->happiness += 10;
    if (tamagotchi->happiness > 100) {
        tamagotchi->happiness = 100;
    }
    printf("%s teve seu pelo alisado!\n", tamagotchi->name);
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
    printf("%s foi passear!\n", tamagotchi->name);
}

void changeEmoji(Tamagotchi* tamagotchi) {
    printf("%s mudou de emoji!\n", tamagotchi->name);
}

void checkStatus(Tamagotchi* tamagotchi) {
    printf("Fome: %d/100 - Felicidade: %d/100\n", tamagotchi->hunger, tamagotchi->happiness);
    if (tamagotchi->hunger >= 100) {
        printf("%s morreu de fome. Game over!\n", tamagotchi->name);
        exit(0);
    } else if (tamagotchi->happiness >= 100) {
        printf("%s está extremamente feliz. Parabéns!\n", tamagotchi->name);
        exit(0);
    }
}

void start(Tamagotchi* tamagotchi) {
    while (true) {
        tamagotchi->happiness -= 10;
        tamagotchi->hunger += 10;
        if (tamagotchi->happiness < 0) {
            tamagotchi->happiness = 0;
        }
        if (tamagotchi->hunger > 100) {
            tamagotchi->hunger = 100;
        }
        printf("Tempo passando...\n");
        checkStatus(tamagotchi);
        sleep(10);
    }
}

int main() {
    Tamagotchi tamagotchi;
    char name[20];

    printf("Digite o nome do seu Tamagotchi: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';

    initialize(&tamagotchi, name);

    printf("Um novo Tamagotchi chamado %s foi criado!\n", tamagotchi.name);
    checkStatus(&tamagotchi);

    printf("Comandos disponíveis:\n");
    printf("- feed: Alimentar o Tamagotchi\n");
    printf("- pet: alisar o pelo Tamagotchi\n");
    printf("- walk: Levar o Tamagotchi para passear\n");
    printf("- change: Mudar o emoji do Tamagotchi\n");
    printf("- exit: Encerrar o programa\n");

    while (true) {
        char command[10];
        printf("Digite um comando: ");
        fgets(command, sizeof(command), stdin);
        command[strcspn(command, "\n")] = '\0';

        if (strcmp(command, "feed") == 0) {
            feed(&tamagotchi);
        } else if (strcmp(command, "pet") == 0) {
            pet(&tamagotchi);
        } else if (strcmp(command, "walk") == 0) {
            walk(&tamagotchi);
        } else if (strcmp(command, "change") == 0) {
            changeEmoji(&tamagotchi);
        } else if (strcmp(command, "exit") == 0) {
            break;
        } else {
            printf("Comando inválido.\n");
        }
    }

    return 0;
}

