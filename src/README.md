# **Carpeta Source (src)**

Esta carpeta contiene el código fuente del sistema de lectura de texto a voz TTS (Text-To-Speech) implementado para Raspberry Pi
con linux, permite seleccionar un archivo `.txt`, configurarlo con un idioma y velocidad de lectura mediante botones físicos, y
reproducirlo en voz usando `espeak`.

Incluye los siguientes archivos fuente y de configuración:

- `conf_asst.c/h` - Asistente de configuración con botones para seleccionar archivo, idioma y velocidad.
- `config.c/h` - Carga de parámetros desde archivo de configuración `tts.conf`.
- `conv_tts.c/h` - Control del motor de síntesis de voz (`espeak`) incluyendo reproducción, pausa, y detención.
- `loader.c/h` - Carga y liberación del contenido del archivo de texto.
- `main.c` - Lógica principal del programa, interacción con botones físicos, ejecución del asistente y reproducción TTS.

## Funcionalidad de cada bloque:

### **- Bloque conf_asst:**
Este bloque contiene el asistente de configuración que permite al usuario seleccionar un archivo `.txt` válido,
un idioma de lectura y una velocidad utilizando tres botones físicos.

- `conf_asst.h`
  Declara la función principal del asistente: `run_config_assistant()`.
- `conf_asst.c`
   - Configura los bótones físicos (`GPIO17`,`GPIO27`,`GPIO22`) usando `wiringPi`.
   - Solicita la ruta del archivo `.txt` al usuario y válida su existencia.
   - Permite seleccionar el idioma (`Español` o `Inglés`) y la velocidad de lectura (`100-200` wpm) usando los botones.
   - Guarda las preferencias en un archivo de configuración (`tts.conf`).

### **- Bloque config:**
