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
Este bloque se encarga de leer el archivo de configuración generado por el asistente (`tts.conf`).

- `config.h`
  Define la estructura `Config` que contiene:
  - Ruta del archivo (por ejemplo: `texts/esuno.txt`)
  - Idioma (por ejemplo: `mb-es2`)
  - Velocidad de lectura 
- `config.c`
  Implementa la función `load_config()` para cargar el archivo de configuración `tts.conf` y llenar la estructura `Config`.


### **- Bloque conv_tts:**
Este bloque controla la reproducción de texto en voz utilizando el programa `espeak`.

- `conv_tts.h`
  - Declara las funciones `speak_line()`, `is_speaking()` y `stop_speech()`.
  - Declara la variable `espeak_pid` para controlar el subproceso que ejecuta `espeak`.

- `conv_tts.c`
  - Usa `fork()` y `execlp()` para llamar a `espeak` con los parámetros correspondientes.
  - Permite verificar si aún está hablando (`is_speaking()`).
  - Permite interrumpir la lectura en curso (`stop_speech()`), usando `SIGKILL`.

### **- Bloque loader:"
Este bloque carga el contenido del archivo `.txt` línea por línea en memoria para su posterior lectura en voz.

- `loader.h`
  Declara las funciones `load_text()` y `free_text()`.
- `loader.c`
  - Implementa la lectura del archivo línea por línea, almacenándolas en memoria dinámica con `load_text()`.
  - Libera la memoria utilizada tras la reproducción con la función `free_text()`.





