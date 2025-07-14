#include <stdio.h>
#include <string.h>
#include "conf_asst.h"

void run_config_assistant(void) {
    char path[256];
    char idioma_usuario[16];
    char voz[10];
    int speed;

    printf("\n=== Asistente de configuración ===\n");
    printf("Ruta del archivo de texto (.txt): ");
    scanf(" %255[^\n]", path);

    printf("Idioma [español / ingles]: ");
    scanf(" %15s", idioma_usuario);

    if (strcmp(idioma_usuario, "español") == 0 || strcmp(idioma_usuario, "Español") == 0)
        strcpy(voz, "mb-es2");
    else if (strcmp(idioma_usuario, "ingles") == 0 || strcmp(idioma_usuario, "Ingles") == 0)
        strcpy(voz, "mb-en1");
    else {
        printf("Idioma no reconocido. Se usará 'mb-es2' por defecto.\n");
        strcpy(voz, "mb-es2");
    }

    do {
        printf("Velocidad de lectura (80-300): ");
        scanf("%d", &speed);
        if (speed < 80 || speed > 300)
            printf("elocidad fuera de rango. Intente de nuevo.\n");
    } while (speed < 80 || speed > 300);

    FILE *file = fopen("tts.conf", "w");
    if (file) {
        fprintf(file, "path=%s\nlanguage=%s\nspeed=%d\n", path, voz, speed);
        fclose(file);
        printf("\nConfiguración guardada exitosamente.\n");
    } else {
        perror("Error al guardar la configuración");
    }
}
