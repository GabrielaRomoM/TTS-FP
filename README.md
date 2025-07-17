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
- 3 Botones pulsadores de 4 pines
### Conexiones:
<img width="1168" height="899" alt="image" src="https://github.com/user-attachments/assets/289b1aa4-8430-4fe4-aac7-8efd559758b6" />


### Implementación Física: 
### Software:
.
#### Paquetes de Instalación:

- Clonar el repositorio:
  
.

## Ejecución:

El repositorio clonado con exito tiene la siguiente estructura:

.

La compilación del sistema se realiza mediante el Makefile de la siguiente forma:

.

Obteniendo como estructura del sistema: 

.

## Funciones:
1. El programa inicialmente mostrará una interfaz sencilla solicitando una ruta de texto. Dicha ruta de texto debe seguir el siguiente formato:
   
   .
   En caso de colocar una ruta invalida, se muestra el siguiente mensaje:
   
   .
   
   La ruta se valida presionando el botón #3

   **NOTA:** Esta versión cuenta con una carpeta de textos (en formato `.txt`) que pueden ser utilizados para poner en funcionamiento el sistema,
   cuenta con dos textos en español (esuno.txt, esdos.txt), dos textos en inglés (enone.txt, entwo.txt), un texto con cáracteres especiales (especiales.txt)
   y un archivo vacio para ver como se comporta el sistema (vacio.txt).

   - Extra: Si se quiere ver como se ha guardado el texto por líneas puedes ejecutar el siguiente comando `` y se verá lo siguiente:
     
     .
     
2. Una vez se valida la ruta del texto, se permite configurar dos párametros (idioma y velocidad). Por defecto, estos dos párametros se van a registrar en:
   
   .
   
   - Se puede cambiar el idioma presionando el botón #1.
   - La velocidad cambia presionando el botón #2, hay 5 diferentes velocidades (100, 125, 150, 175, 200 palabras por minuto), lo que equivale a un rango
     de normal-x2 en terminos más coloquiales.
    
3. Se guardan los cambios realizados presionando el botón #3, y con esto, la reproducción del texto elegido:
   
   .
   
4. Cuando se está reproduciendo el texto, los botones integrados tienen otras funciones:
   
   **4.1. PAUSA:** Presionando el botón #1 se puede detener el texto en la línea en la que esta y así mismo reanudarlo en el mismo punto:
   
   .
   
   **4.2. FINALIZAR REPRODUCCIÓN:** Presionando el botón #2 se puede detener la reproducción del texto por completo y darla por finalizada:
   
   .

   **4.3. NUEVO TEXTO:** Presionando el botón #3, se puede volver a la interfaz de ruta para ingresar un texto diferente:
   
   .

6. Para salir completamente del sistema y desinstalarlo se ejecuta el siguiente comando:
   
   .

## Detalles:

- Las voces del sistema pueden sonar un poco robóticas debido al uso de `espeak` el cuál es un motor TTS sencillo que fue elegido por su facilidad de uso e
  instalación.
- La información relacionada al código y la estructura de cada uno de los módulos se encuentra en el `README.md` de la carpeta `src`.
- El proyecto cuenta con códigos de prueba o testeo para las diferentes funcionalidades. Nuevamente, la información relacionada a este apartado
  se puede encontrar en el `README.md` de la carpeta `test`.

## Matriz de Requerimientos:

![Matriz de Requerimientos](https://github.com/user-attachments/assets/e15c0edd-7d66-4937-bb2a-05a32c0ed0fe)

   
