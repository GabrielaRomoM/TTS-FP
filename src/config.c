#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "config.h"

// Carga los valores desde el archivo tts.conf
int load_config(Config *config) {
    FILE *file = fopen("tts.conf", "r");
    if (!file) return -1;

    // Lee línea por línea y almacena de acuerdo a la clave
    char key[32], value[256];
    while (fscanf(file, "%31[^=]=%255[^\n]\n", key, value) != EOF) {
        if (strcmp(key, "path") == 0)
            strncpy(config->path, value, 255);
        else if (strcmp(key, "language") == 0)
            strncpy(config->language, value, 9);
        else if (strcmp(key, "speed") == 0)
            config->speed = atoi(value);
    }

    fclose(file);
    return 0;
}
