#include <stdio.h>
#include <unistd.h>
#include "../src/config.h"
#include "../src/conv_tts.h"
#include "../src/loader.h"

int main() {
    Config cfg;
    if (load_config(&cfg) != 0) {
        printf("❌ No se pudo cargar configuración\n");
        return 1;
    }

    int count = 0;
    char **lines = load_text(cfg.path, &count);
    if (!lines || count == 0) {
        printf("❌ Error al leer archivo de texto: %s\n", cfg.path);
        return 1;
    }

    printf("Probando speak_line() con primera línea del archivo: %s\n", cfg.path);
    speak_line(lines[0], cfg.language, cfg.speed);

    while (is_speaking()) {
        printf(".");
        fflush(stdout);
        usleep(300000);
    }

    free_text(lines, count);
    printf("\n✅ conv_tts_test passed\n");
    return 0;
}
