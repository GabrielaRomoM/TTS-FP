#include <wiringPi.h>

// Define botones (usando wiringPi numbering)
#define BTN_PAUSE  4  // GPIO23
#define BTN_NEXT   5  // GPIO24
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
    pinMode(BTN_NEXT, INPUT);
    pinMode(BTN_STOP, INPUT);
    pullUpDnControl(BTN_PAUSE, PUD_UP);
    pullUpDnControl(BTN_NEXT, PUD_UP);
    pullUpDnControl(BTN_STOP, PUD_UP);

    int paused = 0;

    for (int i = 0; i < line_count; ++i) {
        while (1) {
            // Si está pausado, espera hasta reanudar
            if (paused) {
                if (digitalRead(BTN_PAUSE) == LOW) {
                    delay(200);
                    while (digitalRead(BTN_PAUSE) == LOW);  // espera suelta
                    paused = 0;
                    printf(">> Reanudado\n");
                }
                if (digitalRead(BTN_STOP) == LOW) {
                    printf(">> Reproducción detenida\n");
                    goto end;
                }
                delay(100);
                continue;
            }

            // Si no está pausado, verifica si se pausa
            if (digitalRead(BTN_PAUSE) == LOW) {
                delay(200);
                while (digitalRead(BTN_PAUSE) == LOW);
                paused = 1;
                printf(">> Pausado\n");
                continue;
            }

            // Verifica si se detiene
            if (digitalRead(BTN_STOP) == LOW) {
                printf(">> Reproducción detenida\n");
                goto end;
            }

            // Verifica si se salta
            if (digitalRead(BTN_NEXT) == LOW) {
                delay(200);
                while (digitalRead(BTN_NEXT) == LOW);
                printf(">> Siguiente línea\n");
                break;  // salta a siguiente línea
            }

            // Reproduce la línea actual
            speak_line(text[i], config.language, config.speed);
            break;
        }
    }

end:
    free_text(text, line_count);
    return 0;
}
