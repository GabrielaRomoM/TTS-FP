#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <wiringPi.h>
#include "../src/conv_tts.h"
#include "../src/config.h"
#include "../src/loader.h"

#define BTN_1 0  // GPIO17 - wiringPi 0

void esperar_suelta(int pin) {
    delay(200);
    while (digitalRead(pin) == LOW);
}

int main() {
    wiringPiSetup();
    pinMode(BTN_1, INPUT);
    pullUpDnControl(BTN_1, PUD_UP);

    Config cfg;
    if (load_config(&cfg) != 0) {
        printf("❌ No se pudo cargar configuración\n");
        return 1;
    }

    int count = 0;
    char **lines = load_text(cfg.path, &count);
    if (!lines || count == 0) {
        printf("❌ Archivo de texto inválido: %s\n", cfg.path);
        return 1;
    }

    printf("Presiona BTN1 para alternar pausa/reanudación\n");
    speak_line(lines[0], cfg.language, cfg.speed);

    int paused = 0;
    int pausa_count = 0;

    while (is_speaking()) {
        if (digitalRead(BTN_1) == LOW) {
            esperar_suelta(BTN_1);
            paused = !paused;
            if (paused) {
                kill(espeak_pid, SIGSTOP);
                pausa_count++;
                printf("\n>> Pausado (%d)\n", pausa_count);
            } else {
                kill(espeak_pid, SIGCONT);
                printf("\n>> Reanudado\n");
            }
        }
        usleep(100000);
    }

    free_text(lines, count);
    printf("✅ playback_test passed (Total pausas: %d)\n", pausa_count);
    return 0;
}
