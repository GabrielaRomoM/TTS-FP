#include <stdio.h>
#include <string.h>
#include "../src/loader.h"
#include "../src/config.h"

int main() {
    Config cfg;
    if (load_config(&cfg) != 0) {
        printf("❌ No se pudo cargar configuración\n");
        return 1;
    }

    FILE *f = fopen(cfg.path, "r");
    if (!f) {
        printf("❌ Archivo no encontrado: %s\n", cfg.path);
        return 1;
    }
    fclose(f);

    int count = 0;
    char **lines = load_text(cfg.path, &count);
    if (!lines || count == 0) {
        printf("❌ Error: archivo vacío o no válido (%s)\n", cfg.path);
        return 1;
    }

    int non_empty = 0;
    for (int i = 0; i < count; ++i) {
        printf("Línea %d: %s", i + 1, lines[i]);
        if (strlen(lines[i]) > 1) non_empty++;
        if (strstr(lines[i], "á") || strstr(lines[i], "😀")) {
            printf("✅ Caracteres especiales detectados en línea %d\n", i + 1);
        }
    }

    if (non_empty == 0) {
        printf("❌ Todas las líneas están vacías\n");
        return 1;
    }

    free_text(lines, count);
    printf("✅ loader_test passed\n");
    return 0;
}
