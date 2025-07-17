#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>
#include "conv_tts.h"

pid_t espeak_pid = -1;

// Inicia un subproceso para ejecutar espeak con los parámetros especificados
void speak_line(const char *text, const char *lang, int speed) {
    espeak_pid = fork(); // Crea un subproceso para la lectura
    if (espeak_pid == 0) { // Código ejecutado por el subproceso
        char speed_str[10];
        snprintf(speed_str, sizeof(speed_str), "%d", speed);
        execlp("espeak", "espeak", "-v", lang, "-s", speed_str, text, NULL);
        _exit(1);  // Si execlp falla (En caso de error al ejecutar espeak)
    }
}

// Verifica si el subproceso de lectura aún se esta ejecutando
int is_speaking(void) {
    if (espeak_pid <= 0) return 0;
    int status;
    pid_t result = waitpid(espeak_pid, &status, WNOHANG);
    return (result == 0); // Si el subproceso aún se está ejecutando
}

// Detiene el subproceso de lectura si está activo
void stop_speech(void) {
    if (espeak_pid > 0) {
        kill(espeak_pid, SIGKILL); // Finaliza el subproceso
        waitpid(espeak_pid, NULL, 0); // Limpia el estado del subproceso terminado
        espeak_pid = -1;
    }
}
