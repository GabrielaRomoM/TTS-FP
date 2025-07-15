#include <wiringPi.h>
#include <stdio.h>
#include "conf_asst.h"
#include "config.h"
#include "loader.h"
#include "conv_tts.h"
#include <signal.h>
#include <unistd.h>

extern int is_speaking(void);
extern void stop_speech(void);

#define BTN_PAUSE   4   // GPIO23
#define BTN_STOP    5   // GPIO24
#define BTN_REPEAT  6   // GPIO25
#define BTN_RECONF  28   // GPIO20

extern pid_t espeak_pid;

int main() {
    Config config;

    if (load_config(&config) != 0) {
        printf("No se pudo cargar tts.conf. Ejecutando asistente...\n");
        run_config_assistant();
        if (load_config(&config) != 0) {
            printf("Error crítico al leer la configuración.\n");
            return 1;
        }
    }

    wiringPiSetup();
    pinMode(BTN_PAUSE, INPUT);
    pinMode(BTN_STOP, INPUT);
    pinMode(BTN_REPEAT, INPUT);
    pinMode(BTN_RECONF, INPUT);

    pullUpDnControl(BTN_PAUSE, PUD_UP);
    pullUpDnControl(BTN_STOP, PUD_UP);
    pullUpDnControl(BTN_REPEAT, PUD_UP);
    pullUpDnControl(BTN_RECONF, PUD_UP);

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
                if (digitalRead(BTN_STOP) == LOW) {
                    stop_speech();
                    printf(">> Reproducción detenida\n");
                    goto fin_reproduccion;
                }

                if (digitalRead(BTN_PAUSE) == LOW) {
                    delay(200);
                    while (digitalRead(BTN_PAUSE) == LOW);
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

        printf("\n=== FIN ===\n");
        printf("BTN_REPEAT (GPIO25) → Repetir\n");
        printf("BTN_RECONF (GPIO26) → Nueva configuración\n");

        repetir = 0;
        while (1) {
            if (digitalRead(BTN_REPEAT) == LOW) {
                delay(200);
                while (digitalRead(BTN_REPEAT) == LOW);
                repetir = 1;
                break;
            }

            if (digitalRead(BTN_RECONF) == LOW) {
                delay(200);
                while (digitalRead(BTN_RECONF) == LOW);
                run_config_assistant();
                if (load_config(&config) != 0) {
                    printf("Error al leer la nueva configuración.\n");
                    return 1;
                }
                repetir = 1;
                break;
            }

            delay(100);
        }

    } while (repetir);

    return 0;
}
