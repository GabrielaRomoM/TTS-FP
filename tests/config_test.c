#include <stdio.h>
#include <string.h>
#include <wiringPi.h>
#include "../src/config.h"
#include "../src/conf_asst.h"

int main() {
    // Ejecutar asistente para ingresar archivo y ajustar config usando botones
    run_config_assistant();

    Config cfg;
    if (load_config(&cfg) != 0) {
        printf("❌ Fallo al cargar configuración\n");
        return 1;
    }

    // Validaciones detalladas
    if (strcmp(cfg.language, "mb-es2") != 0 && strcmp(cfg.language, "mb-en1") != 0) {
        printf("❌ Idioma inválido: %s\n", cfg.language);
        return 1;
    }

    if (cfg.speed < 100 || cfg.speed > 200) {
        printf("❌ Velocidad fuera de rango: %d\n", cfg.speed);
        return 1;
    }

    FILE *f = fopen(cfg.path, "r");
    if (!f) {
        printf("❌ Archivo de texto no existe: %s\n", cfg.path);
        return 1;
    }
    fclose(f);

    printf("✅ config_test passed\nArchivo: %s\nIdioma: %s\nVelocidad: %d\n",
        cfg.path, cfg.language, cfg.speed);
    return 0;
}
