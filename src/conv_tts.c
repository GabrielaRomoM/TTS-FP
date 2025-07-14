#include <stdio.h>
#include <stdlib.h>
#include "conv_tts.h"

void speak_line(const char *text, const char *lang, int speed) {
    char command[512];
    snprintf(command, sizeof(command), "espeak -v %s -s %d \"%s\"", lang, speed, text);
    system(command);
}
