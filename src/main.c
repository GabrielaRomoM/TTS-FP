#include <wiringPi.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include "conf_asst.h"
#include "config.h"
#include "loader.h"
#include "conv_tts.h"

extern pid_t espeak_pid;
extern int is_speaking(void);
extern void stop_speech(void);

// Pines físicos según tu asignación
#define BTN_1 0  // GPIO17 - wiringPi 0
#define BTN_2 2  // GPIO27 - wiringPi 2
#define BTN_3 3  // GPIO22 - wiringPi 3

void esperar_suelta(int pin) {
    delay(200);
    while (digitalRead(pin) == LOW);
}

int main() {
    Config config;

    if (load_config(&config) != 0) {
        printf("Ejecutando asistente...\n");
        run_config_assistant();
        if (load_config(&config) != 0) {
            printf("Error crítico al leer la configuración.\n");
            return 1;
        }
    }

    wiringPiSetup();
    pinMode(BTN_1, INPUT);
    pinMode(BTN_2, INPUT);
    pinMode(BTN_3, INPUT);
    pullUpDnControl(BTN_1, PUD_UP);
    pullUpDnControl(BTN_2, PUD_UP);
    pullUpDnControl(BTN_3, PUD_UP);

    int repetir = 0;

    do {
        int paused = 0;
        int line_count = 0;
        char **text = load_text(config.path, &line_count);
        if (!text || line_count == 0) {
            printf("Error: archivo vacío o no válido.\n");
            return 1;
        }

        for (int i = 0; i < line_count; ++i) {
            speak_line(text[i], config.language, config.speed);
            while (is_speaking()) {
                if (digitalRead(BTN_2) == LOW) {  // Detener
                    stop_speech();
                    esperar_suelta(BTN_2);  // << CORRECCIÓN AQUÍ
                    printf(">> Reproducción detenida\n");
                    goto fin_reproduccion;
                }

                if (digitalRead(BTN_1) == LOW) {  // Pausar / Reanudar
                    esperar_suelta(BTN_1);
                    paused = !paused;
                    if (paused) {
                        printf(">> Pausado\n");
                        kill(espeak_pid, SIGSTOP);
                    } else {
                        printf(">> Reanudado\n");
                        kill(espeak_pid, SIGCONT);
                    }
                }

                delay(100);
            }
        }

    fin_reproduccion:
        free_text(text, line_count);

        printf("\n============== FIN DE REPRODUCCIÓN ==============\n");
        printf("BTN_1: Repetir\n");
        printf("BTN_2: Nuevo archivo\n");
        printf("BTN_3: Salir\n");

        repetir = 0;

        while (1) {
            if (digitalRead(BTN_1) == LOW) {  // Repetir
                esperar_suelta(BTN_1);
                repetir = 1;
                break;
            }

            if (digitalRead(BTN_2) == LOW) {  // Nueva configuración
                esperar_suelta(BTN_2);
                run_config_assistant();
                if (load_config(&config) != 0) {
                    printf("Error al leer nueva configuración.\n");
                    return 1;
                }
                repetir = 1;
                break;
            }

            if (digitalRead(BTN_3) == LOW) {  // Salir del programa
                esperar_suelta(BTN_3);
                repetir = 0;
                break;
            }

            delay(100);
        }

    } while (repetir);

    printf("\n\nSaliendo...\n");
    return 0;
}
