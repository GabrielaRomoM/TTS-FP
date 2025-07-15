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
        // Proceso hijo: ejecuta espeak
        char command[512];
        snprintf(command, sizeof(command), "espeak -v %s -s %d \"%s\"", lang, speed, text);
        execl("/bin/sh", "sh", "-c", command, NULL);
        _exit(1); // si execl falla
    }
}

int is_speaking(void) {
    if (espeak_pid <= 0) return 0;
    int status;
    pid_t result = waitpid(espeak_pid, &status, WNOHANG);
    return (result == 0); // 0: aún está en ejecución
}

void stop_speech(void) {
    if (espeak_pid > 0) {
        kill(espeak_pid, SIGKILL);
        waitpid(espeak_pid, NULL, 0); // evita procesos zombies
        espeak_pid = -1;
    }
}
