#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>
#include "conv_tts.h"

pid_t espeak_pid = -1;

void speak_line(const char *text, const char *lang, int speed) {
    espeak_pid = fork();
    if (espeak_pid == 0) {
        char speed_str[10];
        snprintf(speed_str, sizeof(speed_str), "%d", speed);
        execlp("espeak", "espeak", "-v", lang, "-s", speed_str, text, NULL);
        _exit(1);  // Si execlp falla
    }
}

int is_speaking(void) {
    if (espeak_pid <= 0) return 0;
    int status;
    pid_t result = waitpid(espeak_pid, &status, WNOHANG);
    return (result == 0); // 0: aún se está ejecutando
}

void stop_speech(void) {
    if (espeak_pid > 0) {
        kill(espeak_pid, SIGKILL);
        waitpid(espeak_pid, NULL, 0); // evita zombies
        espeak_pid = -1;
    }
}
