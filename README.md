# Sistema de Lectura de Texto a Voz (TTS) - Proyecto Final

## Autores:
- Cristian Marcelo Quenguan Malte - C.C. 1004532387
- Gabriela Romo Mendoza - C.C. 1080691539

## Descripción General:
Sistema compacto y accesible de lectura de texto a voz (TTS) haciendo uso de una Raspberry Pi Zero, diseñado para convertir
archivos de texto en voz en tiempo real mediante `espeak`. Utiliza botones físicos conectados por GPIO para controlar la reproducción y
cuenta con una arquitectura modular que permite la carga dinámica de textos desde archivos locales y una interacción sencilla a través de la consola.

## Objetivos:
- Aplicar los conocimientos adquiridos durante el semestre relacionados con la configuración de sistemas embebidos en Raspberry Pi haciendo uso de Linux.
- Desarrollar un sistema de lectura de texto a voz (TTS) sobre una Raspberry Pi utilizando Linux, que permita convertir archivos de texto en audio de forma local
  mediante `espeak`, integrando control por botones físicos a través de GPIO y aplicando una arquitectura modular en lenguaje C que facilite su extensión, mantenimiento e interacción por consola.

## Estructura del proyecto:
### Hardware:
- Raspberry Pi Zero 2W
- Módulo UDA1334A I2S DAC
    - Chip UDA1334ATS: es un convertidor digital-analógico (DAC) estéreo I2S de baja potencia. Se utiliza para convertir señales de audio digitales en señales de audio analógicas, y es comúnmente utilizado       en sistemas de audio y aplicaciones integradas. Información técnica:
      [Datasheet UDA1334ATS](https://cdn-shop.adafruit.com/product-files/3678/UDA1334ATS.pdf)
      
- 3 Botones pulsadores de 4 pines
### Conexiones:

<img width="1168" height="899" alt="image" src="https://github.com/user-attachments/assets/289b1aa4-8430-4fe4-aac7-8efd559758b6" />


- MÓDULO UDA13334A I2S DAC

VIN → 5V

GND → GND

WSEL → GPIO19

DIN → GPIO21

BCLK → 18

- PULSADORES DE 4 PINES

Botón #1 → GPIO17

Botón #2 → GPIO27

Botón #3 → GPIO22

GND → GND (Se comparte la conexión para los tres botones)


### Implementación Física: 


<img width="486" height="561" alt="image" src="https://github.com/user-attachments/assets/1a8b0779-160f-4a57-bd70-83069137b761" />


### Software:
Este proyecto está diseñado para ejecutarse en Raspberry Pi (probado en Raspberry Pi Zero 2 W), usando botones físicos conectados a pines GPIO y sintetizador de voz eSpeak.
#### Paquetes de Instalación:
1. wiringPi

   Biblioteca para manejo de GPIO en C.
   Si no está instalada, puede instalarla desde la terminal usando:
   
   ```bash
   sudo apt update
   sudo apt install wiringpi
   ```

   También puede clonar e instalar manualmente:

   ```bash
   git clone https://github.com/WiringPi/WiringPi.git
   cd WiringPi
   ./build
   ```

2. espeak

   Motor TTS (Text-To-Speech) que permite leer texto en voz alta.

    ```bash
    sudo apt install espeak
    ```

   Para compilar el código fuente:

   ```bash
   sudo apt install build-essential
   ```
   
   ### 2.1 Funcionamiento de motor espeak
 
   Es un motor de texto a voz (TTS, Text-to-Speech) ligero y de código abierto que convierte texto escrito en habla sintetizada. Fue escrito originalmente en C y utiliza su propio enfoque de síntesis     
   basado en formantes. Los formantes son picos de energía en la voz humana que definen cómo suena una vocal o consonante. Espeak sintetiza la voz mediante el modelado de estos formantes, sin usar 
   grabaciones reales. Convirtiendo las palabras a fonemas: unidades sonoras básicas del lenguaje (por ejemplo, el sonido "a", "k", "s").

   - Estructura modular de código fuente en C:
     
     - `voice.c` y `speak_lib.c` → manejo de voz y configuración
     - `synthdata.c` → definiciones de fonemas y parámetros acústicos
     - `intonation.c` → reglas para acentos, pausas, énfasis
     - `phonemelist.h` → mapeo de fonemas a sonidos formantes
     
       Repositorio con toda la información del código fuente: [Repositorio oficial de espeak-ng en GitHub](https://github.com/espeak-ng/espeak-ng)

     - Ejemplo:

       1. Entrada de texto
          
          El usuario proporciona una cadena de texto:

          ```bash
          espeak "Hello world"
          ```

        2. Análisis lingüístico

           `Objetivo`: Convertir el texto escrito en una representación fonética (fonemas), usando reglas de pronunciación específicas del idioma.

           #### ¿Cómo lo hace?

           - Detecta el idioma (por defecto inglés o el que configures).
           - Divide el texto en palabras, frases y signos de puntuación.
           - Aplica reglas gramaticales y léxicas desde los archivos como:
          
             - `dictsource/` → Diccionario fonético
             - `rules/` → Reglas gramaticales y prosódicas
               Internamente traduce:
               
               ```bash
               "Hello" → /h/ /ə/ /l/ /oʊ/
               ```

          3. Fonemas → parámetros acústicos
      
             Cada fonema se convierte en una estructura con:

             - Duración
             - Tono (pitch)
             - Frecuencias formantes (F1, F2, F3…)
             - Amplitud
             - Transición con fonemas vecinos

               Un formante es un pico de energía en ciertas frecuencias de la voz humana, importante para distinguir vocales.

          4. Síntesis formántica (formant synthesis)

             eSpeak no reproduce grabaciones humanas, sino que sintetiza sonido usando un modelo matemático de la voz.

             - Cada fonema tiene una representación como suma de ondas senoidales (una por cada formante):
            
               ```bash
               output_sample = A1*sin(2πF1t) + A2*sin(2πF2t) + A3*sin(2πF3t)
               ```
             - Cambia en el tiempo para simular transiciones naturales (coarticulación).
             - Aplica modulación para ritmo, acento, emoción.
   
4. mbrola

   Es un motor de síntesis de voz que trabaja junto con otros programas como eSpeak para generar voces más naturales y menos robóticas que las voces por defecto.
   Para descargar e instalar manualmente mbrola compatible con Raspberry Pi OS se usa:

   ```bash
   sudo apt install ./mbrola_3.3+dfsg-4+deb11u1_armhf.deb
   ```

   Esto instalará mbrola en el sistema para descargar las diferentes voces.

   ```bash
   sudo apt install mbrola-es1 mbrola-es2 mbrola-es3 mbrola-us1 mbrola-us2 mbrola-us3
   ```

   Verificar que se instalaron:
   ```bash
   ls /usr/share/mbrola/
   ```
5. Habilitar I2S en la raspberry pi

   Abrir el archivo de configuración del sistema:

   ```bash
   sudo nano /boot/config.txt
   ```

   Agrega depués de estas líneas para habilitar el bus I2S y configurar el DAC:
   
   ```bash
   # Disable compensation for displays with overscan
   ```

   ```bash
   dtparam=i2s=on
   dtoverlay=hifiberry-dac
   ```

   Reiniciar la Raspberry Pi

   ```bash
   sudo reboot
   ```

   Verificar que I2S esté habilitado:

   ```bash
   aplay -l
   ```

   

- Clonar el repositorio:
  

```bash
git clone https://github.com/GabrielaRomoM/TTS-FP.git
```

<img width="814" height="180" alt="image" src="https://github.com/user-attachments/assets/04013d92-8d61-4203-a7a3-707d754ee456" />


## Ejecución:

El repositorio clonado con exito tiene la siguiente estructura:


<img width="538" height="769" alt="image" src="https://github.com/user-attachments/assets/f8708e53-9399-4d41-8f47-789361d909e1" />



La compilación del sistema se realiza mediante el Makefile de la siguiente forma:


```bash
make all
```


Obteniendo como estructura del sistema: 


<img width="537" height="787" alt="image" src="https://github.com/user-attachments/assets/5b7c90b2-817e-443d-830b-e43901b7abd1" />


El programa se ejecuta usando:

```bash
./bin/main
```

## Funciones:

1. El programa inicialmente mostrará una interfaz sencilla solicitando una ruta de texto. Dicha ruta de texto debe seguir el siguiente formato:
   
   ```bash
    texts/archivo.txt
   ```
   
   En caso de colocar una ruta invalida, se muestra el siguiente mensaje:
   
   
   <img width="622" height="67" alt="image" src="https://github.com/user-attachments/assets/9406059b-680b-46aa-9aeb-a0fe0e74264b" />

   
   La ruta se valida presionando el botón #3

   **NOTA:** Esta versión cuenta con una carpeta de textos (en formato `.txt`) que pueden ser utilizados para poner en funcionamiento el sistema,
   cuenta con dos textos en español (esuno.txt, esdos.txt), dos textos en inglés (enone.txt, entwo.txt), un texto con cáracteres especiales (especiales.txt)
   y un archivo vacio para ver como se comporta el sistema (vacio.txt).
   
   <img width="493" height="201" alt="image" src="https://github.com/user-attachments/assets/3b138360-ebfd-4a8a-b665-71fd80567cb5" />

3. Una vez se valida la ruta del texto, se permite configurar dos párametros (idioma y velocidad). Por defecto, estos dos párametros se van a registrar en:
   
   <img width="692" height="138" alt="image" src="https://github.com/user-attachments/assets/8908e684-6df1-47f4-98a9-72e6d76dd659" />

   
   - Se puede cambiar el idioma presionando el botón #1.
   - La velocidad cambia presionando el botón #2, hay 5 diferentes velocidades (100, 125, 150, 175, 200 palabras por minuto), lo que equivale a un rango
     de normal-x2 en terminos más coloquiales.
    
4. Se guardan los cambios realizados presionando el botón #3, y con esto, la reproducción del texto elegido:
   
   <img width="691" height="174" alt="image" src="https://github.com/user-attachments/assets/2f241b85-a5d5-49e4-a066-18d393943b9d" />

   
5. Cuando se está reproduciendo el texto, los botones integrados tienen otras funciones:
   
   **4.1. PAUSA:** Presionando el botón #1 se puede detener el texto en la línea en la que esta y así mismo reanudarlo en el mismo punto:
   
   <img width="682" height="219" alt="image" src="https://github.com/user-attachments/assets/7a6d96cd-e96f-4535-bd79-e8c93ba105a8" />

   
   **4.2. FINALIZAR REPRODUCCIÓN:** Presionando el botón #2 se puede detener la reproducción del texto por completo y darla por finalizada:
   
   <img width="696" height="252" alt="image" src="https://github.com/user-attachments/assets/0de9454c-e056-439e-a519-283fb36f2d68" />


   **4.3. NUEVO TEXTO:** Presionando el botón #2, se puede volver a la interfaz de ruta para ingresar un texto diferente:

   <img width="702" height="152" alt="image" src="https://github.com/user-attachments/assets/bbbfa68b-b3a8-4383-94fa-db20da016f22" />



6. Para salir de la ejecución se presiona el botón #3:
   
   <img width="708" height="120" alt="image" src="https://github.com/user-attachments/assets/a0060321-7fec-4676-8d9d-ab4c5a6aaa95" />

7. Para desinstalar el sistema y borrar el ejecutable creado con la compilación se digita el siguiente comando:

    ```bash
    make clean
   ```  


## Detalles:

- Las voces del sistema pueden sonar un poco robóticas debido al uso de `espeak` el cuál es un motor TTS sencillo que fue elegido por su facilidad de uso e
  instalación.
- La información relacionada al código y la estructura de cada uno de los módulos se encuentra en el `README.md` de la carpeta `src`.
- El proyecto cuenta con códigos de prueba o testeo para las diferentes funcionalidades. Nuevamente, la información relacionada a este apartado
  se puede encontrar en el `README.md` de la carpeta `test`.

## Matriz de Requerimientos:

![Matriz de Requerimientos](https://github.com/user-attachments/assets/bffd4cec-3126-4d18-a145-fd365aa696a5)
