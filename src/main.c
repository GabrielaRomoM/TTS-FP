#include <stdio.h>
#include "conf_asst.h"
#include "config.h"
#include "loader.h"
#include "conv_tts.h"

int main() {
    Config config;

    if (load_config(&config) != 0) {
        printf("No se pudo cargar tts.conf. Ejecutando asistente...\n");
        run_config_assistant();
        if (load_config(&config) != 0) {
            printf("Error crítico al leer la configuración.\n");
            return 1;
        }
    }

    int line_count = 0;
    char **text = load_text(config.path, &line_count);
    if (!text || line_count == 0) {
        printf("Error: archivo vacío o no válido.\n");
        return 1;
    }

    for (int i = 0; i < line_count; ++i) {
        speak_line(text[i], config.language, config.speed);
    }

    free_text(text, line_count);
    return 0;
}
