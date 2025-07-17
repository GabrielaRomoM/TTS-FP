# **Carpeta bin/**

Esta carpeta contiene los archivos ejecutables generados tras compilar las pruebas del proyecto. Cada binario permite validar una funcionalidad específica del sistema.

## Contenido de la carpeta:

- `config_test`
  - Ejecutable que verifica que el archivo de configuración `tts.conf` sea válido.
  - Revisa el idioma, la velocidad y la existencia del archivo de texto indicado.

  ```bash
  ./config_test
  ```

- `loader_test`
  - Carga el archivo de texto indicado en la configuración y verifica que pueda ser leído correctamente.
  - Detecta si contiene caracteres especiales (acentos, emojis, etc.).

  ```bash
  ./loader_test
  ```

- `conv_tts_test`
  - Inicia la conversión de texto a voz mediante `espeak`, usando la primera línea del texto.
  - La función lanza un subproceso que se monitorea hasta que finaliza la reproducción.

  ```bash
  ./conv_tts_test
  ```

- `playback_test`
  - Prueba la capacidad de pausar y reanudar la lectura de voz mediante un botón físico conectado al GPIO.

  ```bash
  ./playback_test
  ```

**NOTAS:**
- Todos los ejecutables dependen del archivo `tts.conf` ubicado en la raíz del proyecto.
- No olvidar la compilación con `make all` antes de ejecutar cualquier prueba.
