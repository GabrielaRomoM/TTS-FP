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

    printf("✅ config_test passed\nArchivo: %s\nIdioma: %s\nVelocidad: %d\n",
        cfg.path, cfg.language, cfg.speed);
    return 0;
}
