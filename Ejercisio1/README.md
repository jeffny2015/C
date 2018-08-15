Tarea 1 SO

Jeffrey Alfaro Fonseca 20155069856

# Programa
Programa hecho en C para linux y sigue las epecificaciones del archivo "Tarea1.pdf", compuesto por main.c y main.h, no se modulariza, el programa comienza ejecutandose
con el makefile, abre una terminal en la direción de la carpeta donde se encuentra el archivo "makefile":


```sh
$ ./tarea prueba1 ejemplo.tex
```
El archvo crea un ejecutable "tarea", para ejecutarlo uno le tiene que pasar dos argumentos de entrada
el primer argumento es el nombre del archivo .text que con tiene el formato de la tabla de procesos y el
segundo argumento el nombre del .tex que quiere generar :

./tarea [nombre.txt] [nombre.tex]

```sh
$ ./tarea prueba1 ejemplo.tex
```
El programa le dira que esta listo el archivo:

Escribiendo archivo ..........
Archivo Escrito

Salida

El programa genera un archivo ".tex" que le quiso dar en este 
caso en lo que se ingresa en el ejemplo:

ejemplo.tex

#### Notas

No se verfica si el formato del .txt viene según la forma que indica el archivo de la Tarea1.pdf, entonces si no viene
según el formato, entonces el programa se cae.

Los archivos prueba1 y prueba2 sirven como ejemplos del primer argumento a la hora de ejecutarlo
