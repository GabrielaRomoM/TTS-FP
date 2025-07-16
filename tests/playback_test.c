#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <wiringPi.h>
#include "../src/conv_tts.h"

#define BTN_1 0  // GPIO17 - wiringPi 0

void esperar_suelta(int pin) {
    delay(200);
    while (digitalRead(pin) == LOW);
}

int main() {
    wiringPiSetup();
    pinMode(BTN_1, INPUT);
    pullUpDnControl(BTN_1, PUD_UP);

    printf("Presiona BTN1 para alternar pausa/reanudación\n");
    speak_line("Probando reproducción pausada y reanudada", "mb-es2", 150);

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

    printf("✅ playback_test passed (Total pausas: %d)\n", pausa_count);
    return 0;
}
