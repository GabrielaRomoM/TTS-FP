#ifndef CONV_TTS_H
#define CONV_TTS_H

#include <sys/types.h>

// Inicia la reproducción de una línea con idioma y velocidad dados
void speak_line(const char *text, const char *lang, int speed);
// Verifica si el subproceso de lectura sigue activo
int is_speaking(void);
// Detiene el subproceso de lectura en curso
void stop_speech(void);
// ID del subproceso de lectura (espeak)
extern pid_t espeak_pid;

#endif
