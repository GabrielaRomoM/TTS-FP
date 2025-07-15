#include <wiringPi.h>
#include <stdio.h>
#include "conf_asst.h"
#include "config.h"
#include "loader.h"
#include "conv_tts.h"

#define BTN_PAUSE  4  // GPIO23
#define BTN_STOP   6  // GPIO25

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

    int line_count = 0;
    char **text = load_text(config.path, &line_count);
    if (!text || line_count == 0) {
        printf("Error: archivo vacío o no válido.\n");
        return 1;
    }

    // Configura botones
    wiringPiSetup();
    pinMode(BTN_PAUSE, INPUT);
    pinMode(BTN_STOP, INPUT);
    pullUpDnControl(BTN_PAUSE, PUD_UP);
    pullUpDnControl(BTN_STOP, PUD_UP);

    int paused = 0;

    for (int i = 0; i < line_count; ++i) {
        speak_line(text[i], config.language, config.speed);

        while (is_speaking()) {
            if (digitalRead(BTN_STOP) == LOW) {
                stop_speech();
                printf(">> Reproducción detenida\n");
                goto end;
            }

            if (digitalRead(BTN_PAUSE) == LOW) {
                delay(200); // anti-rebote
                while (digitalRead(BTN_PAUSE) == LOW);
                paused = !paused;

                if (paused) {
                    printf(">> Pausado\n");
                    kill(espeak_pid, SIGSTOP); // Pausar proceso
                } else {
                    printf(">> Reanudado\n");
                    kill(espeak_pid, SIGCONT); // Reanudar proceso
                }
            }

            delay(100);
        }
    }

end:
    free_text(text, line_count);
    return 0;
}
