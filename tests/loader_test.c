#include <stdio.h>
#include "../src/loader.h"
#include "../src/config.h"

int main() {
    Config cfg;
    if (load_config(&cfg) != 0) {
        printf("❌ No se pudo cargar configuración\n");
        return 1;
    }

    int count = 0;
    char **lines = load_text(cfg.path, &count);
    if (!lines || count == 0) {
        printf("❌ Error: archivo vacío o no válido (%s)\n", cfg.path);
        return 1;
    }

    for (int i = 0; i < count; ++i)
        printf("Línea %d: %s", i + 1, lines[i]);

    free_text(lines, count);
    printf("✅ loader_test passed\n");
    return 0;
}
