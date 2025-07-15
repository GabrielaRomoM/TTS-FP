#ifndef CONV_TTS_H
#define CONV_TTS_H

#include <sys/types.h>

void speak_line(const char *text, const char *lang, int speed);
int is_speaking(void);
void stop_speech(void);
extern pid_t espeak_pid;

#endif
