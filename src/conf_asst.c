#include <stdio.h>
#include <wiringPi.h>
#include <string.h>
#include <stdlib.h>
#include "conf_asst.h"

#define BTN1 0  // GPIO17 
#define BTN2 2  // GPIO27 
#define BTN3 3  // GPIO22 

const char* idiomas[] = {"mb-es2", "mb-en1"};
const char* idiomas_mostrar[] = {"Español", "Inglés"};
int speeds[] = {100, 125, 150, 175, 200};

int wait_for_button_press() {
    while (1) {
        if (digitalRead(BTN1) == LOW) {
            delay(50);
            while (digitalRead(BTN1) == LOW);
            return BTN1;
        }
        if (digitalRead(BTN2) == LOW) {
            delay(50);
            while (digitalRead(BTN2) == LOW);
            return BTN2;
        }
        if (digitalRead(BTN3) == LOW) {
            delay(50);
            while (digitalRead(BTN3) == LOW);
            return BTN3;
        }
        delay(10);
    }
}

void run_config_assistant(void) {
    wiringPiSetup();

    pinMode(BTN1, INPUT);
    pinMode(BTN2, INPUT);
    pinMode(BTN3, INPUT);
    pullUpDnControl(BTN1, PUD_UP);
    pullUpDnControl(BTN2, PUD_UP);
    pullUpDnControl(BTN3, PUD_UP);

    char path[256];
    int idioma_idx = 0;
    int speed_idx = 0;

    printf("\n====== Selección de archivo de texto ======\n");

    // Bucle para solicitar archivo válido y no vacío
    while (1) {
        printf("Ingrese el nombre o ruta del archivo .txt: ");
        scanf(" %255[^\n]", path);

        FILE *test = fopen(path, "r");
        if (!test) {
            printf("El archivo no existe o no se puede abrir. Intente nuevamente.\n");
            continue;
        }

        // Verificar si está vacío
        int c = fgetc(test);
        if (c == EOF) {
            printf("El archivo está vacío. Intente con otro archivo.\n");
            fclose(test);
            continue;
        }

        // Archivo válido y no vacío
        fclose(test);
        break;
    }

    while (1) {
        system("clear");
        printf("\n=== Configuración para la reproducción ===\n");
        printf("Archivo: %s\n", path);
        printf("Idioma: %s\n", idiomas_mostrar[idioma_idx]);
        printf("Velocidad: %d\n", speeds[speed_idx]);
        printf("Presiona el BTN3 para guardar configuración.\n");

        int btn = wait_for_button_press();

        if (btn == BTN1) {
            idioma_idx = 1 - idioma_idx;
        } else if (btn == BTN2) {
            speed_idx = (speed_idx + 1) % 5;
        } else if (btn == BTN3) {
            break;
        }
    }

    FILE *file = fopen("tts.conf", "w");
    if (file) {
        fprintf(file, "path=%s\nlanguage=%s\nspeed=%d\n", path, idiomas[idioma_idx], speeds[speed_idx]);
        fclose(file);
        printf("\nConfiguración guardada.\n");
        printf("\nReproduciendo...")
    } else {
        perror("Error al guardar configuración");
    }
}
