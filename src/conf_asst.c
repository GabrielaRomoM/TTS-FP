#include <stdio.h>
#include <wiringPi.h>
#include <string.h>
#include "conf_asst_gpio.h"
#include <stdlib.h>

#define BTN_LANG  0   // GPIO17
#define BTN_SPEED 2   // GPIO27
#define BTN_OK    3   // GPIO22

const char* idiomas[] = {"mb-es2", "mb-en1"};
const char* idiomas_mostrar[] = {"Español", "Inglés"};
int speeds[] = {100, 125, 150, 175, 200};

int wait_for_button_press() {
    while (1) {
        if (digitalRead(BTN_LANG) == LOW) {
            delay(50);
            while (digitalRead(BTN_LANG) == LOW);
            return BTN_LANG;
        }
        if (digitalRead(BTN_SPEED) == LOW) {
            delay(50);
            while (digitalRead(BTN_SPEED) == LOW);
            return BTN_SPEED;
        }
        if (digitalRead(BTN_OK) == LOW) {
            delay(50);
            while (digitalRead(BTN_OK) == LOW);
            return BTN_OK;
        }
        delay(10);
    }
}

void run_config_assistant(void) {
    wiringPiSetup();

    pinMode(BTN_LANG, INPUT);
    pinMode(BTN_SPEED, INPUT);
    pinMode(BTN_OK, INPUT);

    pullUpDnControl(BTN_LANG, PUD_UP);
    pullUpDnControl(BTN_SPEED, PUD_UP);
    pullUpDnControl(BTN_OK, PUD_UP);

    char path[256];
    int idioma_idx = 0;
    int speed_idx = 0;

    printf("\n=== Asistente de configuración ===\n");
    printf("Ingrese el nombre o ruta del archivo .txt: ");
    scanf(" %255[^\n]", path);

    printf("Usa los botones para cambiar opciones. OK para confirmar.\n");

    while (1) {
        system("clear");
        printf("\n=== Asistente de configuración ===\n");
        printf("Archivo: %s\n", path);
        printf("Idioma: %s", idiomas_mostrar[idioma_idx]);
	printf("\nVelocidad: %d\n", speeds[speed_idx]); 
	printf("Presiona Ok para guardar la configuración.\n");

        int btn = wait_for_button_press();

        if (btn == BTN_LANG) {
            idioma_idx = 1 - idioma_idx;  // alternar 0 <-> 1
        } else if (btn == BTN_SPEED) {
            speed_idx = (speed_idx + 1) % 5;
        } else if (btn == BTN_OK) {
            break;
        }
    }

    FILE *file = fopen("tts.conf", "w");
    if (file) {
        fprintf(file, "path=%s\nlanguage=%s\nspeed=%d\n", path, idiomas[idioma_idx], speeds[speed_idx]);
        fclose(file);
        printf("\nConfiguración guardada exitosamente.\n");
    } else {
        perror("Error al guardar configuración");
    }
}
