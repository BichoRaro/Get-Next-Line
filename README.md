*Este proyecto ha sido creado como parte del currículo de 42 por <aykhan-i>.*

# Get Next Line

## 📌 Descripción
**Get Next Line** 
es un proyecto cuyo objetivo es implementar en C la función:

```c
char *get_next_line(int fd);
```

Esta función permite leer una línea completa desde un file descriptor (descriptor de archivo), devolviendo la línea leída en cada llamada hasta alcanzar el final del archivo (EOF) o producirse un error.

El proyecto introduce y refuerza conceptos fundamentales como:

* Uso de variables estáticas
* Gestión dinámica de memoria
* Lectura con read
* Manejo eficiente de buffers
* Prevención de memory leaks

La función debe devolver la línea incluyendo el carácter \n (si existe), excepto cuando se alcanza el final del archivo sin salto de línea final.

## ⚙️ Instrucciones

📂 Archivos obligatorios

* get_next_line.c
* get_next_line_utils.c
* get_next_line.h

🔨 Compilación

El proyecto debe compilarse con:

```c
cc -Wall -Werror -Wextra -D BUFFER_SIZE=42 *.c

```
Puedes modificar el tamaño del buffer en la compilación:

```
cc -Wall -Werror -Wextra -D BUFFER_SIZE=10 *.c
cc -Wall -Werror -Wextra -D BUFFER_SIZE=1000 *.c

```

Si no se define BUFFER_SIZE, se utiliza el valor por defecto definido en el header.

## 🧠 Explicación del algoritmo

La función sigue los siguientes pasos:

* 1. Variable estática

Se utiliza una variable estática para almacenar los datos leídos que aún no han sido procesados.

* 2. Lectura por bloques

Se usa ```read(fd, buffer, BUFFER_SIZE)``` para leer el archivo en fragmentos.

* 3. Acumulación de contenido

Cada lectura se concatena a la variable estática hasta encontrar un ```\n``` o alcanzar EOF.

* 4. Extracción de línea

Cuando se detecta un salto de línea: 
* Se extrae la línea completa.
* Se actualiza la variable estática con el contenido restante.

* 5. Gestión de memoria

* Se libera correctamente la memoria cuando ya no es necesaria.
* Se evita cualquier fuga de memoria (memory leak).

## 📚 Recursos

* Manual de malloc y free:

```
man 3 malloc
man 3 free
```

### 🧠 Conceptos clave

* Variables estáticas en C
* File descriptors en sistemas Unix
* Gestión de memoria dinámica en C



## ⚠️ Restricciones

* Funciones permitidas:
  1. read
  2. malloc
  3. free
* Prohibido:
  1. lseek
  2. Variables globales

## 🏁 Conclusión

## 🏁 Conclusión

El proyecto **get_next_line** representa un paso importante en la comprensión profunda del lenguaje C y del funcionamiento interno del sistema de archivos en Unix.

Más allá de implementar una función que lea líneas desde un descriptor de archivo, este proyecto obliga a entender conceptos fundamentales como:

- El uso correcto de variables estáticas
- La gestión precisa de memoria dinámica
- El comportamiento de la función `read`
- La eficiencia en la lectura por buffers
- La importancia de evitar memory leaks

Uno de los mayores aprendizajes de este proyecto es diseñar una función que mantenga estado entre llamadas sin utilizar variables globales, lo que fortalece la capacidad de estructurar código limpio y reutilizable.

Además, enfrentarse a distintos tamaños de `BUFFER_SIZE`, archivos vacíos, múltiples descriptores y casos límite ayuda a desarrollar una mentalidad más rigurosa y orientada a pruebas.

En definitiva, **get_next_line no es solo una función práctica**, sino un ejercicio clave para consolidar bases sólidas en programación de bajo nivel, control de memoria y diseño eficiente de algoritmos.
