Descripción: 
Se administra en una empresa los tickets de soporte técnico, que representan una solicitud de ayuda ingresado por un usuario. Los tickets contienen ID único, descripción problema, nivel prioridad(alto, medio o bajo) y hora registro. Este sistema organiza el orden de prioridad y hora para atender los tickets más urgentes. Se podrá registrar nuevos tickets, modificar prioridad, mostrar lista de espera y procesar los tickets atendidos.

Programa:
El Sistema de gestión de tickets de soporte técnico se ha realizado en lenguaje C y se puede ejecutar en Visual Studio Code con extensión C/C++. Para trabajar con sistema se deberán seguir los siguientes pasos:

Requisitos previos:
•	Haber descargado Visual Studio Code.
•	Tener el compilador C/C++, haber descargado el MinGW para Windows o el entorno WSL.
•	Tener la extensión C/C++ en Visual Studio Code.

Compilar y ejecutar
•	Se debe descargar esta carpeta y se descomprime el archivo .zip.
•	En Visual Studio Code se va a, file y se escoge open folder, luego selecciona la carpeta descomprimida.
•	Se debe abrir el archivo tarea1.c para visualizar código. 
•	Se abre su terminal y se debe compilar el programa con siguiente comando:
                  gcc tdas/*.c tarea1.c -Wno-unused-result -o tarea1
•	Ya compilado, para ejecutar el código se debe escribir en terminal:
                  ./tarea1
*en caso de que no funcione el temminal, verificamos que estemos en la subcarpeta correcta con:
                  cd .\Tarea1-fzs-master

opciones que funcionan correctamente:

Registrar ticket: Registra los datos del ticket, evitando que haya ID duplicados, ya que comprobamos si esta(ID) antes de agregar.
Asignar prioridad: Por ID se asigna al ticket su prioridad, ya sea alto, medio o bajo. Se podrá escribir mayúscula o minúsculas y lo ordenamos segun prioridad.
Mostrar lista espera: Muestra los tickets ingresados de forma ordenada por prioridad y hora ingresada (primero los de prioridad alta que primero llegaron y al final los de baja).
Atender siguiente ticket: Selecciona el ticket en ser atendido según prioridad y hora de llegada, para luego eliminarlo de la lista de espera y atender al siguiente. Al paciente eliminado, se le agregará a una nueva lista de tickets ya atendidos.
Buscar ticket por ID: Busca los tickets por ID de manera correcta en la lista de espera o los que ya fueron atendidos.
ordenar tickets: Recorre todos los tickets y lor ordena segun prioridad y hora, esto nos permite tener una funcion en especifica para ordenar los tickets y no hacerlos en otra funcion. Logra que los tickets esten siempre ordenados

Problemas conocidos:

Tiene una interfaz visual muy monótona/básica, se podría hacer una interfaz más grafica para que sea más colorido, intuitivo y fácil de entender para el usuario.

A mejorar:
Al mostrar la lista de espera se podría agregar que numero de la lista es cada ticket para ser atendido (ejemplo: es el n° 4 de la lista).
Se podría especificar en buscar ID ticket, si se quiere buscar un ticket ya atendido o que esté en la lista de espera. Como también indicar si fue atendido o no.



ejemplo mostrando como interactuar con la aplicación.
El programa comienza preguntando que opción desea realizar:

1. En el caso que se desee registrar un ticket, se elige la opción 1. Se ingresa respectivo ID y descripción. El programa asignara automáticamente prioridad bajo y guardara la hora en ser registrado. Luego se presionar la tecla 6, la cual indica salir. 
•	Ingrese su opcion: 1
•	Registrar nuevo ticket
•	Ingrese ID ticket: 1
•	Ingrese descripcion problema: dolor cabeza
•	Presione una tecla para continuar...

2. Luego registramos la prioridad del ticket ingresando la opción 2, debemos ingresar ID ticket y escribir la prioridad asignada.
•	Ingrese su opcion: 2
•	Ingrese ID ticket: 1
•	Ingrese prioridad ticket: alto

3. Para revisar la lista de espera con todos los tickets se deberá ingresar la opción 3, la cual mostrará por orden de prioridad y hora de llegada de los tickets, con su ID, descripción del problema y prioridad.
•	Ingrese su opcion: 3

4. Se llamará al ticket según prioridad y hora de llegada en la lista, se mostrará ID, descripción, prioridad y hora registrada. Luego se eliminara de la lista de espera y se agregara a la lista de ya atendidos.
•	Ingrese su opcion: 4
•	Ticket en ser atendido: ID: 1
•	Descripción: dolor cabeza
•	Prioridad: alto
•	Hora registrada: día hora año

5) Para buscar el ID se ingresa la opción 5, indicando su respectivo ID, lo cual se mostrará junto a descripción, prioridad y hora.
•	Ingrese su opcion: 5
•	Ingrese ID ticket: 1
•	ID: 1
•	Descripcion: dolor cabeza
•	Prioridad: Alto
•	Hora registrada: día hora año

