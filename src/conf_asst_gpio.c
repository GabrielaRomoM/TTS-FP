#include <stdio.h>
#include <wiringPi.h>
#include <string.h>
#include <unistd.h>
#include "conf_asst.h"

#define BTN_LANG 0     // GPIO17 -> wiringPi 0
#define BTN_SPEED 2    // GPIO27 -> wiringPi 2
#define BTN_OK 3       // GPIO22 -> wiringPi 3

const char* idiomas[] = {"mb-es2", "mb-en1"};
const char* idiomas_mostrar[] = {"Español", "Inglés"};
int speeds[] = {100, 125, 150, 175, 200};

void wait_for_button_press(int pin) {
    while (digitalRead(pin) == LOW)
        delay(10);
    while (digitalRead(pin) == HIGH)
        delay(10); // Esperar que se suelte
}

void run_config_assistant(void) {
    wiringPiSetup();

    pinMode(BTN_LANG, INPUT);
    pinMode(BTN_SPEED, INPUT);
    pinMode(BTN_OK, INPUT);

    pullUpDnControl(BTN_LANG, PUD_DOWN);
    pullUpDnControl(BTN_SPEED, PUD_DOWN);
    pullUpDnControl(BTN_OK, PUD_DOWN);

    char path[256];
    int idioma_idx = 0;
    int speed_idx = 0;

    printf("\n=== Asistente de configuración física ===\n");
    printf("Ingrese la ruta del archivo .txt: ");
    scanf(" %255[^\n]", path);

    printf("Usa los botones para cambiar opciones. Pulsa OK para confirmar.\n");

    while (1) {
        printf("\nIdioma: %s | Velocidad: %d\n", idiomas_mostrar[idioma_idx], speeds[speed_idx]);

        if (digitalRead(BTN_LANG)) {
            idioma_idx = (idioma_idx + 1) % 2;
            wait_for_button_press(BTN_LANG);
        }

        if (digitalRead(BTN_SPEED)) {
            speed_idx = (speed_idx + 1) % 5;
            wait_for_button_press(BTN_SPEED);
        }

        if (digitalRead(BTN_OK)) {
            wait_for_button_press(BTN_OK);
            break;
        }

        delay(100);
    }

    FILE *file = fopen("tts.conf", "w");
    if (file) {
        fprintf(file, "path=%s\nlanguage=%s\nspeed=%d\n", path, idiomas[idioma_idx], speeds[speed_idx]);
        fclose(file);
        printf("Configuración guardada exitosamente.\n");
    } else {
        perror("Error al guardar configuración");
    }
}
