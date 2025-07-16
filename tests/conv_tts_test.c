#include <stdio.h>
#include <unistd.h>
#include "../src/config.h"
#include "../src/conv_tts.h"

int main() {
    Config cfg;
    if (load_config(&cfg) != 0) {
        printf("❌ No se pudo cargar configuración\n");
        return 1;
    }

    printf("Probando speak_line() con archivo: %s\n", cfg.path);
    speak_line("Esto es una prueba de voz con configuración cargada", cfg.language, cfg.speed);

    while (is_speaking()) {
        printf(".");
        fflush(stdout);
        usleep(300000);
    }

    printf("\n✅ conv_tts_test passed\n");
    return 0;
}
