#include <stdio.h>
#include <wiringPi.h>
#include "conf_asst.h"
#include "config.h"
#include "loader.h"
#include "conv_tts.h"

#define BTN_PAUSE  4   // GPIO23
#define BTN_NEXT   5   // GPIO24
#define BTN_STOP   6   // GPIO25

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

    // Configurar botones de control
    wiringPiSetup();
    pinMode(BTN_PAUSE, INPUT);
    pinMode(BTN_NEXT, INPUT);
    pinMode(BTN_STOP, INPUT);
    pullUpDnControl(BTN_PAUSE, PUD_UP);
    pullUpDnControl(BTN_NEXT, PUD_UP);
    pullUpDnControl(BTN_STOP, PUD_UP);

    int paused = 0;

    for (int i = 0; i < line_count; ++i) {
        while (1) {
            // Verificar si se presionó STOP
            if (digitalRead(BTN_STOP) == LOW) {
                printf("\n⛔ Lectura detenida.\n");
                goto end_reading;
            }

            // Verificar si se presionó PAUSE
            if (digitalRead(BTN_PAUSE) == LOW) {
                paused = !paused;
                printf(paused ? "\n⏸️ Pausado\n" : "\n▶️ Reanudado\n");
                while (digitalRead(BTN_PAUSE) == LOW); // esperar soltar
                delay(200);
            }

            // Si está en pausa, esperar
            if (paused) {
                delay(100);
                continue;
            }

            // Verificar si se presionó SIGUIENTE
            if (digitalRead(BTN_NEXT) == LOW) {
                printf("\n⏭ Saltando línea...\n");
                while (digitalRead(BTN_NEXT) == LOW);
                delay(200);
                break;
            }

            // Reproducir línea
            speak_line(text[i], config.language, config.speed);
            break;
        }
    }

end_reading:
    free_text(text, line_count);
    return 0;
}
