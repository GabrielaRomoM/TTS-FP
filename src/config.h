#ifndef CONFIG_H
#define CONFIG_H

typedef struct {
    char path[256];
    char language[10];
    int speed;
} Config;

int load_config(Config *config);

#endif
