# MiniShell - lsoto-do && gmacias-
El objetivo de este proyecto es que crees un shell sencillo. Sí, tu propio pequeño bash. Aprenderás un montón sobre procesos y file descriptors.

### Indice
* [Que es MiniShell?](#que-es-minishell)
* [Que utilizamos?](#que-utilizamos)
* [Como funciona?](#como-funciona)

### Que es MiniShell?

MiniShell es un proyecto del programa de formación de 42 que tiene como objetivo principal la creación de un shell básico, similar a Bash. A través de este proyecto, nos sumergimos en conceptos fundamentales de sistemas operativos, **manejo de procesos, y gestión de file descriptors**. La tarea consiste en desarrollar desde **cero** un intérprete de comandos que sea capaz de ejecutar comandos simples y combinar estos con operadores de redirección (< << > >> ) y tuberías( | ).

### Que utilizamos?
En nuestro **MiniShell** tenemos solo las siguentes funciones de librerias externas autorizadas:

| Función  | Descripción                                                                 |
|----------|-----------------------------------------------------------------------------|
| **readline** | Lee una línea de texto de la entrada estándar, ofreciendo funciones como edición y autocompletado.  |
| malloc   | Solicita un bloque de memoria del tamaño suministrado como parámetro.       |
| free     | Desasigna un bloque de memoria que se había asignado previamente mediante una llamada.  |
| write    | Hace que los bytes que indiques del buffer sean escritos en el file descriptor seleccionado.  |
| open     | Abre el archivo del sistema seleccionado.                                   |
| close    | Cierra el archivo del sistema seleccionado.                                 |
| read     | Lee el contenido del archivo del sistema seleccionado.                      |
| exit     | Finaliza inmediatamente el programa liberando la memoria dinámica asignada. |
| fork     | Crea un nuevo proceso duplicando el proceso actual.                         |
| waitpid  | Espera a que un proceso hijo específico termine su ejecución.               |
| pipe     | Crea un par de file descriptors para comunicación unidireccional entre procesos. |
| dup2     | Duplica un file descriptor, para redirigir la entrada/salida.               |
| getenv   | Obtiene el valor de una variable de entorno.                                |
| perror   | Imprime un mensaje de error a stderr que describe el último error encontrado. |
| kill     | Envía una señal a un proceso o grupo de procesos, para finalizarlo.         |


### Como funciona?

Para compilar el programa seguimos los siguientes pasos:

	git clone https://github.com/LuisEd2094/MiniShell
	cd MiniShell
	make
Luego ejecutamos el programa pasandole de parametro la ubicacion del archivo del mapa:

	./MiniShell

**Los procesos que sigue la aplicacion son las siguientes**

 - **Loop Principal:** Un bucle infinito que muestra el prompt, lee la entrada del usuario, y luego procesa y ejecuta comandos.
 - **Lectura de Entrada:** El shell utiliza readline para obtener la línea de comandos del usuario.
 - **Parsing:** La entrada se analiza para separar los comandos, argumentos, operadores , y redirecciones.
 - **Ejecución de Comandos:** Dependiendo de si el comando es un built-in o externo, se ejecuta directamente o se crea un proceso hijo para su ejecución usando fork y execve.

¡Y eso seria todo!¡Estas liso para utilizar tu nuevo y mejorado Bash!

# Quizás pueda interesarte!

### - Perfil de GitHub lsoto-do
[AQUÍ](https://github.com/LuisEd2094/)

### - Perfil de GitHub gmacias-
[AQUÍ](https://github.com/gjmacias)

# Contactos 📥

◦ Email lsoto-do-: lsoto-do@student.42barcelona.com

◦ Email gmacias-: gmacias-@student.42barcelona.com

[1]: https://www.42barcelona.com/ "42 BCN"
