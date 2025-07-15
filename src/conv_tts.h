#ifndef CONV_TTS_H
#define CONV_TTS_H

void speak_line(const char *text, const char *lang, int speed);
void stop_speech(void);
int is_speaking(void);

#endif
