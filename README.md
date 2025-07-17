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

<img width="486" height="561" alt="image" src="https://github.com/user-attachments/assets/1a8b0779-160f-4a57-bd70-83069137b761" />

### Software:
.
#### Paquetes de Instalación:

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



6. Para salir completamente del sistema y desinstalarlo se ejecuta el siguiente comando:
   
   <img width="708" height="120" alt="image" src="https://github.com/user-attachments/assets/a0060321-7fec-4676-8d9d-ab4c5a6aaa95" />


## Detalles:

- Las voces del sistema pueden sonar un poco robóticas debido al uso de `espeak` el cuál es un motor TTS sencillo que fue elegido por su facilidad de uso e
  instalación.
- La información relacionada al código y la estructura de cada uno de los módulos se encuentra en el `README.md` de la carpeta `src`.
- El proyecto cuenta con códigos de prueba o testeo para las diferentes funcionalidades. Nuevamente, la información relacionada a este apartado
  se puede encontrar en el `README.md` de la carpeta `test`.

## Matriz de Requerimientos:

![Matriz de Requerimientos](https://github.com/user-attachments/assets/e15c0edd-7d66-4937-bb2a-05a32c0ed0fe)

   
