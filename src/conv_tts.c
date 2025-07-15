#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>
#include "conv_tts.h"

pid_t espeak_pid = -1;

void speak_line(const char *text, const char *lang, int speed) {
    espeak_pid = fork();
    if (espeak_pid == 0) {
        // Proceso hijo
        char speed_str[10];
        snprintf(speed_str, sizeof(speed_str), "%d", speed);
        execlp("espeak", "espeak", "-v", lang, "-s", speed_str, text, NULL);
        // Si falla
        perror("execlp");
        exit(1);
    }
}

int is_speaking() {
    if (espeak_pid <= 0) return 0;
    int status;
    pid_t result = waitpid(espeak_pid, &status, WNOHANG);
    return result == 0; // aún está corriendo
}

void stop_speech() {
    if (espeak_pid > 0) {
        kill(espeak_pid, SIGKILL);
        waitpid(espeak_pid, NULL, 0);
        espeak_pid = -1;
    }
}
