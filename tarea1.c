#include "tdas/list.h"
#include "tdas/extra.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define BAJO 0
#define MEDIO 1
#define ALTO 2

typedef struct {                //estructura para definir un ticket
  int ID;                       
  char descriProblema[100];     
  int prioridad;                
  time_t hora;                  
} ticketPersona;

ticketPersona* crearTicket(int id, const char *descripcion){  //creamos un nuevo ticket
  ticketPersona *newTicket = (ticketPersona*)malloc(sizeof(ticketPersona)); //reserva de memoria dinamica para el ticket

  if(newTicket == NULL){
    return NULL;
  }

  newTicket->ID = id; //asignamos id al nuevo ticket
  strcpy(newTicket->descriProblema,descripcion); //copiamos la descripcion problema al nuevo ticket
  newTicket->prioridad = BAJO; //se establece para todos los tickets nuevos prioridad bajo
  newTicket->hora = time(NULL); //se almacena la hora actual que se creo ticket

  return newTicket;
}

void ordenarTickets(List *pacientes, ticketPersona *ticket){
  List *listaTemp = list_create();
  ticketPersona *paciente = list_first(pacientes);
  int comprobar = 0;
  while(paciente != NULL){ //recorremos lista para encontrar ticket con mayor prioridad
    if(!comprobar &&
      (ticket->prioridad > paciente->prioridad) ||
      (ticket->prioridad == paciente->prioridad && ticket->hora < paciente->hora)){
      list_pushBack(listaTemp,ticket);   //si ticket tiene prioridad mas alta que actual, lo elegimos, 
      comprobar = 1;
    }  
    list_pushBack(listaTemp,paciente);
    paciente = list_next(pacientes);//siguiente de la lista
  }
  if(!comprobar){
    list_pushBack(listaTemp,ticket);
  }
  list_clean(pacientes);
  paciente = list_first(listaTemp);
  while(paciente != NULL){
    list_pushBack(pacientes,paciente);
    paciente = list_next(listaTemp);
  }
  list_clean(listaTemp);
}

void registrarTicket(List *pacientes) {
  int id;
  char descripcion[100];
  printf("--Registrar nuevo ticket-- \n");

  printf("Ingrese ID ticket: "); 
  if(scanf("%d",&id) != 1){  //se verifica que el id ingresado sea un numero
    printf("AVISO: ID invalido, ingrese un numero.\n"); //en caso contrario se muestra esto
    while(getchar() != '\n'); //se limpia buffer entrada
    return;
  }
  getchar(); //salto de linea del buffer se consume

  ticketPersona *paciente = list_first(pacientes); //tomamos primer valor de la lista
  while(paciente != NULL){  //verificamos si el id ya fue ingresado anteriormente
    if(paciente->ID == id){ 
      printf("AVISO: Ya existe ID\n");
      return;
    }
    paciente = list_next(pacientes); //pasamos al siguiente
  }

  printf("Ingrese descripcion problema: "); //se ingresa la descripcion
  scanf("%99[^\n]",descripcion);//leemos hasta salto de linea, hasta 99 caracteres

  ticketPersona *newTicket = crearTicket(id,descripcion);//se crea ticket con los datos entregados
  if(newTicket != NULL){
    ordenarTickets(pacientes,newTicket); //lo agregamos a la lista
  }
}

void hacerMinuscula(char *texto){ //hacemos minuscula el texto que nos entreguen, en este caso la prioridad
  for(int i = 0; texto[i]; i++){
    texto[i] = tolower(texto[i]);
  }
}



void asignarTicket(List *pacientes){
  int id;
  char descripcion[100];

  printf("Ingrese ID ticket: "); //ingresamos el id del ticket
  scanf("%d",&id);
  getchar();

  printf("Ingrese prioridad ticket(alto, medio o bajo): "); //ingresamos prioridad
  scanf("%s",descripcion);
  hacerMinuscula(descripcion); //hacemos toda la cadena en minuscula para no tener problemas con mayusculas

  ticketPersona *paciente = list_first(pacientes);//apuntamos al primer ticket
  while(paciente != NULL){ //si paciente es distinto a null avanzamos
    if(paciente->ID == id){ //recorremos lista hasta encontrar id del ticket ingresado
      if(strcmp(descripcion,"alto") == 0) { //comparamos cadena con prioridad, para determinarla con prioridad ingresada
        paciente->prioridad = ALTO;
      } else if (strcmp(descripcion,"medio") == 0){
          paciente->prioridad = MEDIO;
      } else if (strcmp(descripcion,"bajo") == 0){
        paciente->prioridad = BAJO;
      } else {
        printf("AVISO: No existe esa prioridad, intente de nuevo.\n"); //si se ingresa otro texto que no sea alto,medio
        return;
      }                                                         //bajo, se muestra un aviso
      ticketPersona *temp = paciente;
      list_popCurrent(pacientes);
      ordenarTickets(pacientes,temp);
      printf("Prioridad ingresada.\n");
      return;
    }
    paciente = list_next(pacientes); //pasamos al siguiente ticket
  }
  printf("AVISO: No se encontro ticket con ese ID.\n"); //EN caso de no encontrar id, se muestra error
}

void mostrarListaTicket(List *pacientes) {
  printf("Tickets en espera ordenados por prioridad: \n");
  //recorremos la lista para imprimir los tickets con prioridad alta
  ticketPersona *paciente = list_first(pacientes); //apuntamos a primer elemento lista
  while(paciente != NULL){
    printf("ID: %d\n",paciente->ID);
    printf("Descripcion: %s\n",paciente->descriProblema);
    printf("Prioridad: ");
      switch (paciente->prioridad){ //indicamos la prioridad segun escogida
        case ALTO:
          printf("Alto\n");
          break;
        case MEDIO:
          printf("Medio\n");
          break;
        case BAJO:
          printf("Bajo\n");
          break;
      }
      printf("------------\n");
      paciente = list_next(pacientes);//apuntamos al siguiente puntero
  }
}

void ProcesarSiguienteTicket(List *pacientes, List *pacientesAtendidos){
  ticketPersona *currentTicket = list_first(pacientes); //apuntamos a primero de la lista

  if(currentTicket != NULL){ //cuando tengamos el ticket actual se imprimiran sus datos
    printf("Ticket en ser atendido: ");
    printf("ID: %d\n",currentTicket->ID);
    printf("Descripcion: %s\n",currentTicket->descriProblema);
    printf("Prioridad: ");
      switch (currentTicket->prioridad){ //indicamos la prioridad segun escogida
        case ALTO:
          printf("Alto\n");
          break;
        case MEDIO:
          printf("Medio\n");
          break;
        case BAJO:
          printf("Bajo\n");
          break;
      }
    printf("Hora registrada: %s\n",ctime(&currentTicket->hora)); //mostramos hora como texto
    list_pushBack(pacientesAtendidos,currentTicket);//lo pasamos a otra lista(atendidos) antes eliminar
    list_popCurrent(pacientes); //lo eliminamos de la lista (lista espera)
  } else {
    printf("AVISO: No hay tickets para procesar.\n"); //si se eliminan todos los tickets o no hay se muestra aviso
  }
}

void BuscarticketporID(List *pacientes,List *pacientesAtendidos){
  int id;
  printf("Ingrese ID ticket: "); //ingresamos id
  scanf("%d",&id);
  getchar();
  //buscamos ticket en la primera lista (espera)
  ticketPersona *paciente = list_first(pacientes); //apuntamos al primero
  while(paciente != NULL){
    if(paciente->ID == id){ //comparamos si id ingresado coincide con id, si es cierto se imprime la informacion
      printf("Ticket:");    //del ticket
      printf("ID: %d\n",paciente->ID);
      printf("Descripcion: %s\n",paciente->descriProblema);
      printf("Prioridad: ");          //se asigna segun prioridad ingresada
      switch (paciente->prioridad){
        case ALTO:
          printf("Alto\n");
          break;
        case MEDIO:
          printf("Medio\n");
          break;
        case BAJO:
          printf("Bajo\n");
          break;
      }
      printf("Hora registrada: %s\n",ctime(&(paciente->hora)));
      return;
    }
    paciente = list_next(pacientes); //pasamos al siguiente
  }
  //ya que se han eliminado en lista de espera los atendidos, se busca en la lista de atendidos
  paciente = list_first(pacientesAtendidos);
  while(paciente != NULL){
    if(paciente->ID == id){  //comparamos si id ingresado coincide con id, si es cierto se imprime la informacion
      printf("ID: %d\n",paciente->ID);
      printf("Descripcion: %s\n",paciente->descriProblema);
      printf("Prioridad: ");
      switch (paciente->prioridad){ //se asigna segun prioridad ingresada
        case ALTO: 
          printf("Alto\n");
          break;
        case MEDIO:
          printf("Medio\n");
          break;
        case BAJO:
          printf("Bajo\n");
          break;
      }
      printf("Hora registrada: %s\n",ctime(&(paciente->hora)));
      return;
    }
    paciente = list_next(pacientesAtendidos); //pasamos al siguiente
  }

  printf("AVISO: No se encontro ese ID.\n"); //si no se encuentra se avisa
}
// Menú principal para mostrar 
void mostrarMenuPrincipal() {
  limpiarPantalla();
  puts("========================================");
  puts("  Sistema tickets de soporte tecnico");
  puts("========================================");
  //opciones que usario puede elegir
  puts("1) Registrar ticket");
  puts("2) Asignar prioridad a ticket");
  puts("3) Mostrar lista de espera");
  puts("4) Atender al siguiente ticket");
  puts("5) Mostrar tickets por ID");
  puts("6) Salir");
}

int main() {
  char opcion; //opcion ingresado por usario
  List *pacientes = list_create(); // lista para gestionar los tickets en espera
  List *pacientesAtendidos = list_create();// lista para gestionar los tickets ya atendidos 

  do {
    mostrarMenuPrincipal();
    printf("\nIngrese su opcion: ");
    scanf(" %c", &opcion); // Nota el espacio antes de %c para consumir el
                           // newline anterior

    switch (opcion) {
    case '1': //si opcion es 1 se registra ticket segun la funcion
      registrarTicket(pacientes);
      break;
    case '2': //si es dos se asigna la prioridad al ticket
      asignarTicket(pacientes);
      break;
    case '3': //si es 3 muestra los tickets por prioridad y hora
      mostrarListaTicket(pacientes);
      break;
    case '4'://si es 4 procesa a quien atender
      ProcesarSiguienteTicket(pacientes,pacientesAtendidos);
      break;
    case '5': //si es 5 busca el id del ticket ya sea atendido o no
      BuscarticketporID(pacientes,pacientesAtendidos);
      break;
    case '6': //salimos del sistema
      puts("Saliendo del sistema de gestión hospitalaria...");
      break;
    default:
      puts("Opción no válida. Por favor, intente de nuevo.");
    }
    presioneTeclaParaContinuar();//usario debe precionar tecla para terminar


  } while (opcion != '6'); //repetimos hasta tener un 6 (indica salida)

  // Liberar recursos, si es necesario
  list_clean(pacientes);
  list_clean(pacientesAtendidos);

  return 0; //terminamos :D
}
