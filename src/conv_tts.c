#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include "conv_tts.h"

pid_t espeak_pid = -1;

void speak_line(const char *text, const char *lang, int speed) {
    if (espeak_pid > 0) {
        waitpid(espeak_pid, NULL, 0);  // Espera al anterior si no ha terminado
    }

    espeak_pid = fork();
    if (espeak_pid == 0) {
        char command[512];
        snprintf(command, sizeof(command), "espeak -v %s -s %d \"%s\"", lang, speed, text);
        execl("/bin/sh", "sh", "-c", command, (char *)NULL);
        perror("execl falló");
        exit(1);
    }
}

int is_speaking(void) {
    if (espeak_pid <= 0) return 0;

    int status;
    pid_t result = waitpid(espeak_pid, &status, WNOHANG);
    return (result == 0);  // Sigue hablando si no ha terminado
}

void stop_speech(void) {
    if (espeak_pid > 0) {
        kill(espeak_pid, SIGKILL);
        waitpid(espeak_pid, NULL, 0);
        espeak_pid = -1;
    }
}
