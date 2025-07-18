# Pruebas TTS-FP

Este documetno describe el procedimiento para validar el correcto funcionamiento de los distintos componentes del sistema TTS-FP (Texto a voz con botones físicos).

## 1. Configuración inicial

El archivo de configuración por defecto se encuentra en la raíz del proyecto:

```ini
tts.conf:
path=texts/esuno.txt
language=mb-es2
speed=150
```

## 2. Compilación

Desde la carpeta de pruebas, la compilación de todos los binarios de prueba se realiza con:

```bash
make all
```

Esto genera los ejecutables en la carpeta `bin/`:

- `config_test`
- `loader_test`
- `conv_tts_test`
- `playback_test`

## 3. Pruebas individuales

### `config_test`

Valida que el archivo `tts.conf` se pueda leer correctamente y que los valores estén dentro del rango permitido, con el siguiente comando:

```bash
./bin/config_test
```

**Resultados esperados:**

- Idioma en cualquiera de las dos configuraciones disponibles (`mb-es2` o `mb-en1`).
- Velocidad entre 100 y 200 palabras por minuto.
- El archivo de texto especificado debe existir.

### `loader_test`

Verifica que el archivo de texto especificado en la configuración se pueda abrir, contenga líneas no vacías y que puedan leerse caracteres especiales (acentos, emojis, etc).
Se utiliza el comando:

```bash
./bin/loader_test
```

**Resultados esperados:**

- Al menos una línea debe contener texto.
- Detección de caracteres especiales en las líneas.

### `conv_tts_test`

Prueba el funcionamiento de la función `speak_line` que lanza un subproceso con `espeak`, usando la primera línea del archivo de texto. Con:

```bash
./bin/conv_tts_test
```

**Resultados esperados:**

- Se reproduce audio mediante espeak.
- Se imprimen puntos mientras está hablando.

### `playback_test`

Prueba interactiva de pausa/reanudación usando un botón físico (`GPIO17` - Botón #1). El botón alterna entre pausar y reanudar la reproducción. Utilizando:

```bash
./bin/playback_test
```

**Resultados esperados:**

- Presionar el botón pausa el audio.
- Otra presión lo reanuda.

## 4. Limpieza del proyecto

Digitando el comando: 

```bash
make clean
```

Esta acción elimina el directorio `bin/` con todos los binarios generados.
