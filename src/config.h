#ifndef CONFIG_H
#define CONFIG_H

// Estructura que contiene la configuración cargada
typedef struct {
    char path[256];
    char language[10];
    int speed;
} Config;

// Función que carga el archivo tts.conf
int load_config(Config *config);

#endif
